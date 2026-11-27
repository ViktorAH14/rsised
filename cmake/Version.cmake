# Version derived from the last git tag + commit counter + branch
# (equivalent of version.pri)

set(_git_opts WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
              OUTPUT_STRIP_TRAILING_WHITESPACE)

# --- Last tag (the raw value is needed for rev-list, see below) ---
execute_process(COMMAND git describe --abbrev=0
    ${_git_opts} ERROR_QUIET RESULT_VARIABLE _res OUTPUT_VARIABLE GIT_TAG)
if(NOT _res EQUAL 0)
    message(WARNING "No git tag found - using fallback version 0.0.0")
    set(GIT_TAG "0.0.0")
endif()

# --- Commit counter: computed BEFORE tag transformations, while GIT_TAG
# --- is still a valid ref. After the s/-/./ replacements the string is no
# --- longer a valid ref and rev-list would fail (VER_BUILD silently = 0).
execute_process(COMMAND git rev-list "${GIT_TAG}..HEAD" --count
    ${_git_opts} ERROR_QUIET RESULT_VARIABLE _res OUTPUT_VARIABLE VER_BUILD)
if(NOT _res EQUAL 0)
    set(VER_BUILD 0)
endif()

# --- Version parsing (transformations kept 1:1 with version.pri) ---
set(GIT_VERSION "${GIT_TAG}")
string(REGEX REPLACE "^v" "" GIT_VERSION "${GIT_VERSION}")
# qmake equivalent: s/-/"." replaces only the first occurrence - reproduce it
string(REGEX REPLACE "^([^-]*)-" "\\1." GIT_VERSION "${GIT_VERSION}")

# Extract the leading numeric core (1..3 dot-separated components).
# Two- and even one-component tags (v0.1, v2) are valid: missing
# components are normalized to zero below.
string(REGEX MATCH "^([0-9]+)(\\.[0-9]+)?(\\.[0-9]+)?" _ver_core "${GIT_VERSION}")
if(_ver_core STREQUAL "")
    message(WARNING "Cannot parse version from tag '${GIT_TAG}' - falling back to 0.0.0")
    set(_ver_core "0.0.0")
endif()

string(REPLACE "." ";" _ver_list "${_ver_core}")
list(LENGTH _ver_list _ver_len)
list(GET _ver_list 0 VER_MAJ)
if(_ver_len GREATER 1)
    list(GET _ver_list 1 VER_MIN)
else()
    set(VER_MIN 0)
endif()
if(_ver_len GREATER 2)
    list(GET _ver_list 2 VER_PAT)
else()
    set(VER_PAT 0)
endif()

# --- Branch ---
execute_process(COMMAND git branch --show-current
    ${_git_opts} ERROR_QUIET RESULT_VARIABLE _res OUTPUT_VARIABLE BRANCH)
# Empty output with zero exit code means detached HEAD (tag checkout, CI)
if(NOT _res EQUAL 0 OR BRANCH STREQUAL "")
    set(BRANCH "unknown")
endif()

# A slash in the branch name breaks file names (tar, targetDir) - normalize
string(REGEX REPLACE "/" "_" BRANCH "${BRANCH}")

# --- Version format per branch (semantics 1:1 with version.pri) ---
set(VER_BRANCH "${BRANCH}")
string(REGEX REPLACE "^feat_[A-Za-z0-9_]+" "feature" VER_BRANCH "${VER_BRANCH}")
string(REGEX REPLACE "^fix_[A-Za-z0-9_]+" "fix" VER_BRANCH "${VER_BRANCH}")
string(REGEX REPLACE "^release_[0-9]+\\.[0-9]+\\.[0-9]+" "release" VER_BRANCH "${VER_BRANCH}")

if(VER_BRANCH STREQUAL "master")
    set(RSISED_VERSION_FULL "${VER_MAJ}.${VER_MIN}.${VER_PAT}")
elseif(VER_BRANCH STREQUAL "develop")
    set(RSISED_VERSION_FULL "${VER_MAJ}.${VER_MIN}.${VER_PAT}-b.${VER_BUILD}")
elseif(VER_BRANCH STREQUAL "release" OR VER_BRANCH STREQUAL "fix")
    set(RSISED_VERSION_FULL "${VER_MAJ}.${VER_MIN}.${VER_PAT}-r.${VER_BUILD}")
else()
    # Keep the branch name as is - otherwise different feature branches
    # would produce identical version strings
    set(RSISED_VERSION_FULL "${VER_MAJ}.${VER_MIN}.${VER_PAT}-a.${VER_BUILD}-${BRANCH}")
endif()

# Numeric version - for project() only; full string - for config.h
set(RSISED_VERSION_NUM "${VER_MAJ}.${VER_MIN}.${VER_PAT}")

# --- Date of the last commit ---
execute_process(COMMAND git log -n 1 --format=format:%ai
    ${_git_opts} ERROR_QUIET OUTPUT_VARIABLE RSISED_DATE)

message(STATUS "Version: ${RSISED_VERSION_FULL} (branch: ${BRANCH}, build: ${VER_BUILD})")
