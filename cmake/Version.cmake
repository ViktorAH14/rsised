# Версия из git-тега + счётчик коммитов + ветка (эквивалент version.pri)

set(_git_opts WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
              OUTPUT_STRIP_TRAILING_WHITESPACE)

# --- Последний тег ---
execute_process(COMMAND git describe --abbrev=0
    ${_git_opts} ERROR_QUIET RESULT_VARIABLE _res OUTPUT_VARIABLE GIT_VERSION)
if(NOT _res EQUAL 0)
    message(WARNING "No git tag found — using fallback version 0.0.0")
    set(GIT_VERSION "0.0.0")
endif()

string(REGEX REPLACE "^v" "" GIT_VERSION "${GIT_VERSION}")
# qmake-эквивалент s/-/"." меняет только первое вхождение — воспроизводим
string(REGEX REPLACE "^([^-]*)-" "\\1." GIT_VERSION "${GIT_VERSION}")

string(REGEX REPLACE "^([0-9]+)\\..*" "\\1" VER_MAJ "${GIT_VERSION}")
string(REGEX REPLACE "^[0-9]+\\.([^.]+)(\\..*)?$" "\\1" VER_MIN "${GIT_VERSION}")
string(REGEX REPLACE "^[0-9]+\\.[^.]+\\.([^.]+)" "\\1" VER_PAT "${GIT_VERSION}")

# --- Счётчик коммитов с последнего тега ---
execute_process(COMMAND git rev-list "${GIT_VERSION}..HEAD" --count
    ${_git_opts} ERROR_QUIET RESULT_VARIABLE _res OUTPUT_VARIABLE VER_BUILD)
if(NOT _res EQUAL 0)
    set(VER_BUILD 0)
endif()

# --- Ветка ---
execute_process(COMMAND git branch --show-current
    ${_git_opts} ERROR_QUIET RESULT_VARIABLE _res OUTPUT_VARIABLE BRANCH)
if(NOT _res EQUAL 0)
    set(BRANCH "unknown")
endif()

# Слеш в имени ветки ломает имена файлов (tar, targetDir) — нормализуем
string(REGEX REPLACE "/" "_" BRANCH "${BRANCH}")

set(VER_BRANCH "${BRANCH}")
string(REGEX REPLACE "^feat_[A-Za-z0-9_]+" "feature" VER_BRANCH "${VER_BRANCH}")
string(REGEX REPLACE "^fix_[A-Za-z0-9_]+" "fix" VER_BRANCH "${VER_BRANCH}")
string(REGEX REPLACE "^release_[0-9]+\\.[0-9]+\\.[0-9]+" "release" VER_BRANCH "${VER_BRANCH}")

# --- Формат версии по ветке (семантика 1:1 с version.pri) ---
if(VER_BRANCH STREQUAL "master")
    set(RSISED_VERSION_FULL "${VER_MAJ}.${VER_MIN}.${VER_PAT}")
elseif(VER_BRANCH STREQUAL "develop")
    set(RSISED_VERSION_FULL "${VER_MAJ}.${VER_MIN}.${VER_PAT}-b.${VER_BUILD}")
elseif(VER_BRANCH STREQUAL "release" OR VER_BRANCH STREQUAL "fix")
    set(RSISED_VERSION_FULL "${VER_MAJ}.${VER_MIN}.${VER_PAT}-r.${VER_BUILD}")
else()
    set(RSISED_VERSION_FULL "${VER_MAJ}.${VER_MIN}.${VER_PAT}-a.${VER_BUILD}-${BRANCH}")
endif()

# Численная версия — только для project(); полная строка — для config.h
set(RSISED_VERSION_NUM "${VER_MAJ}.${VER_MIN}.${VER_PAT}")

# --- Дата последнего коммита ---
execute_process(COMMAND git log -n 1 --format=format:%ai
    ${_git_opts} ERROR_QUIET OUTPUT_VARIABLE RSISED_DATE)

message(STATUS "Version: ${RSISED_VERSION_FULL} (branch: ${BRANCH}, build: ${VER_BUILD})")
