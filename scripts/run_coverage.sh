#!/bin/sh
set -u

log_info() { echo "[INFO] $*"; }
log_warn() { echo "[WARN] $*" >&2; }
log_err()  { echo "[ERROR] $*" >&2; }

# Script directory + ".." = project root
# (the script is located in scripts/, all output paths are calculated from the root)
COV_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." 2>/dev/null && pwd)" || {
  log_err "Cannot resolve script directory"
  exit 1
}

# Directory with object files and .gcda:
# - qmake build (default): <root>/obj
# - CMake build: pass via variable,
#   for example COV_SRC_DIR=build-cmake/linux-profile
SRC_DIR="${COV_SRC_DIR:-${COV_DIR}/obj}"

HTML_RESULTS="${COV_DIR}/coverage/html"
RAW_INFO="${COV_DIR}/coverage/coverage.info"
FILTERED_INFO="${COV_DIR}/coverage/coverage-filtered.info"

# Dependency check: we exit gently if they are not present
if ! command -v lcov >/dev/null 2>&1; then
  log_warn "lcov is not installed or not in PATH; skipping coverage generation"
  exit 0
fi
if ! command -v genhtml >/dev/null 2>&1; then
  log_warn "genhtml is not installed or not in PATH; skipping HTML report generation"
  exit 0
fi

mkdir -p "${HTML_RESULTS}" || {
  log_err "Failed to create output directory: ${HTML_RESULTS}"
  exit 1
}

# If there is no catalog with object files, this is not an emergency for a soft scenario.
if [ ! -d "${SRC_DIR}" ]; then
  log_warn "Source objects directory not found: ${SRC_DIR}; nothing to collect"
  exit 0
fi

# Coverage collection
if ! lcov --rc geninfo_unexecuted_blocks=1 -d "${SRC_DIR}" -c -o "${RAW_INFO}"; then
  log_warn "lcov collection failed (possibly no .gcda data); nothing to report"
  exit 0
fi

# Check that the file has actually been created and is not empty
if [ ! -s "${RAW_INFO}" ]; then
  log_warn "Raw coverage file is missing or empty: ${RAW_INFO}"
  exit 0
fi

# Filtering
if ! lcov --ignore-errors inconsistent,unused -r "${RAW_INFO}" \
  "*Qt*.framework*" \
  "*.h" \
  "*/tests/*" \
  "*/test/*" \
  "/usr/*" \
  "*.moc" \
  "*moc_*.cpp" \
  "*/mocs_compilation.cpp" \
  "*/build*/*" \
  -o "${FILTERED_INFO}"
then
  log_warn "Coverage filtering failed; keeping raw report only"
  exit 0
fi

if [ ! -s "${FILTERED_INFO}" ]; then
  log_warn "Filtered coverage is empty; skipping HTML generation"
  exit 0
fi

HTML generation
if ! genhtml --ignore-errors inconsistent,unused -o "${HTML_RESULTS}" "${FILTERED_INFO}"; then
  log_warn "HTML report generation failed"
  exit 0
fi

# Resetting counters: we warn you, but we don’t consider it a fatal error.
if ! lcov -d "${SRC_DIR}" -z; then
  log_warn "Failed to reset lcov counters in ${SRC_DIR}"
fi

log_info "Coverage report generated: ${HTML_RESULTS}/index.html"
exit 0
