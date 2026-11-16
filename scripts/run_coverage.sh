#!/bin/sh
set -u

log_info() { echo "[INFO] $*"; }
log_warn() { echo "[WARN] $*" >&2; }
log_err()  { echo "[ERROR] $*" >&2; }

# Каталог скрипта + ".." = корень проекта
# (скрипт лежит в scripts/, все пути вывода считаем от корня)
COV_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." 2>/dev/null && pwd)" || {
  log_err "Cannot resolve script directory"
  exit 1
}

# Каталог с объектниками и .gcda:
# - qmake-сборка (по умолчанию): <root>/obj
# - CMake-сборка: передавать через переменную,
#   например COV_SRC_DIR=build-cmake/linux-profile
SRC_DIR="${COV_SRC_DIR:-${COV_DIR}/obj}"

HTML_RESULTS="${COV_DIR}/coverage/html"
RAW_INFO="${COV_DIR}/coverage/coverage.info"
FILTERED_INFO="${COV_DIR}/coverage/coverage-filtered.info"

# Проверка зависимостей: мягко выходим, если их нет
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

# Если каталога с объектниками нет — это не авария для мягкого сценария
if [ ! -d "${SRC_DIR}" ]; then
  log_warn "Source objects directory not found: ${SRC_DIR}; nothing to collect"
  exit 0
fi

# Сбор покрытия
if ! lcov --rc geninfo_unexecuted_blocks=1 -d "${SRC_DIR}" -c -o "${RAW_INFO}"; then
  log_warn "lcov collection failed (possibly no .gcda data); nothing to report"
  exit 0
fi

# Проверка, что файл реально создан и не пуст
if [ ! -s "${RAW_INFO}" ]; then
  log_warn "Raw coverage file is missing or empty: ${RAW_INFO}"
  exit 0
fi

# Фильтрация
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

# Генерация HTML
if ! genhtml --ignore-errors inconsistent,unused -o "${HTML_RESULTS}" "${FILTERED_INFO}"; then
  log_warn "HTML report generation failed"
  exit 0
fi

# Сброс счётчиков: предупреждаем, но не считаем фатальной ошибкой
if ! lcov -d "${SRC_DIR}" -z; then
  log_warn "Failed to reset lcov counters in ${SRC_DIR}"
fi

log_info "Coverage report generated: ${HTML_RESULTS}/index.html"
exit 0
