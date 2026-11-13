# --- OS_SUFFIX (win32 / win64 / linux) ---
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(OS_SUFFIX win32)
    else()
        set(OS_SUFFIX win64)
    endif()
else()
    set(OS_SUFFIX linux)
endif()

# --- BUILD_FLAG / LIB_SUFFIX ---
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()
string(TOLOWER "${CMAKE_BUILD_TYPE}" _build_lower)
if(_build_lower STREQUAL "debug")
    set(BUILD_FLAG debug)
    set(LIB_SUFFIX d)
elseif(_build_lower STREQUAL "profile" OR _build_lower STREQUAL "relwithdebinfo")
    set(BUILD_FLAG profile)
    set(LIB_SUFFIX "")
else()
    set(BUILD_FLAG release)
    set(LIB_SUFFIX "")
endif()

# --- Пути вывода (DESTDIR из lib.pri и app.pri) ---
set(LIBS_PATH   "${CMAKE_SOURCE_DIR}/lib.${OS_SUFFIX}/")
set(INC_PATH    "${CMAKE_SOURCE_DIR}/include/")
set(IMPORT_PATH "${CMAKE_SOURCE_DIR}/import/")
set(BIN_PATH    "${CMAKE_SOURCE_DIR}/bin/${OS_SUFFIX}/${BUILD_FLAG}/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIBS_PATH}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${LIBS_PATH}")
# per-config подпапки не нужны: bin/<os>/<config> уже содержит уровень конфига
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${BIN_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${BIN_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BIN_PATH}")

if(EXISTS "${INC_PATH}")
    include_directories("${INC_PATH}")
endif()
if(EXISTS "${IMPORT_PATH}")
    include_directories("${IMPORT_PATH}")
endif()

# --- Язык и Qt-автоматика ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# --- RPATH: эквивалент -Wl,--rpath=$$ORIGIN/../../lib.<os>/ из app.pri ---
set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)

# --- Профильная сборка с покрытием (эквивалент force_debug_info) ---
set(CMAKE_CXX_FLAGS_PROFILE "-O2 -g --coverage" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "--coverage" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "--coverage" CACHE STRING "" FORCE)
