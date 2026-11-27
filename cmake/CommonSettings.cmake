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

# --- BUILD_FLAG ---
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
# Provide a dropdown in cmake-gui/ccmake; "Profile" is a project-specific
# configuration used for coverage builds (see the flags block below)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    Debug Release RelWithDebInfo MinSizeRel Profile)

string(TOLOWER "${CMAKE_BUILD_TYPE}" _build_lower)
if(_build_lower STREQUAL "debug")
    set(BUILD_FLAG debug)
elseif(_build_lower STREQUAL "profile" OR _build_lower STREQUAL "relwithdebinfo")
    set(BUILD_FLAG profile)
else()
    set(BUILD_FLAG release)
endif()
# Debug name suffix for the library is set per-target via DEBUG_POSTFIX
# (see src/libshapes/CMakeLists.txt) - no global LIB_SUFFIX is needed.

# --- Output paths (DESTDIR equivalents from lib.pri and app.pri) ---
set(LIBS_PATH   "${CMAKE_SOURCE_DIR}/lib.${OS_SUFFIX}")
set(INC_PATH    "${CMAKE_SOURCE_DIR}/include")
set(IMPORT_PATH "${CMAKE_SOURCE_DIR}/import")
set(BIN_PATH    "${CMAKE_SOURCE_DIR}/bin/${OS_SUFFIX}/${BUILD_FLAG}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIBS_PATH}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${LIBS_PATH}")
# Per-config subdirectories are not needed: bin/<os>/<config> already
# contains the configuration level

# -I on a non-existent directory is silently ignored by the compiler,
# so no existence check is needed: the build must not depend on whether
# these directories happen to exist on disk
include_directories("${INC_PATH}" "${IMPORT_PATH}")

# --- Language and Qt automation ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# --- RPATH: equivalent of -Wl,--rpath=$$ORIGIN/../../lib.<os>/ from app.pri ---
set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)

# --- Profile build with coverage (equivalent of force_debug_info) ---
set(CMAKE_CXX_FLAGS_PROFILE "-O2 -g --coverage" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "--coverage" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "--coverage" CACHE STRING "" FORCE)
