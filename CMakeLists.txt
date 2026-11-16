cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Version)                                  # до project()!

project(RSiSed VERSION ${RSISED_VERSION_NUM} LANGUAGES CXX)

# project() перезаписал VERSION числом — возвращаем полную строку,
# её ждёт config.h.in
set(VERSION "${RSISED_VERSION_FULL}")

include(CommonSettings)

find_package(Qt6 REQUIRED COMPONENTS
    Core Gui Widgets Svg Xml PrintSupport Core5Compat Test LinguistTools)

enable_testing()

add_subdirectory(src/libshapes)
add_subdirectory(src/rsised)

# Шесть тестовых каталогов из SUBDIRS
add_subdirectory(tests/auto/tst_libshapes/tst_abstractshape)
add_subdirectory(tests/auto/tst_libshapes/tst_rectshape)
add_subdirectory(tests/auto/tst_libshapes/tst_ellipseshape)
add_subdirectory(tests/auto/tst_libshapes/tst_buildingshape)
add_subdirectory(tests/auto/tst_libshapes/tst_technicsshape)
add_subdirectory(tests/auto/tst_libshapes/tst_equipmentshape)

# --- Doxygen: Doxyfile переносится как есть (без подстановок) ---
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_SOURCE_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        COMMENT "Generating Doxygen documentation to doc/dev/dox/en"
    )
endif()

# --- Покрытие: только в профильной сборке ---
# Тесты запускаются (появляются .gcda), затем собирается отчёт lcov/genhtml
if(BUILD_FLAG STREQUAL "profile" AND UNIX)
    add_custom_target(coverage
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        COMMAND ${CMAKE_COMMAND} -E env
                        COV_SRC_DIR=${CMAKE_BINARY_DIR}
                        "${CMAKE_SOURCE_DIR}/scripts/run_coverage.sh"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        DEPENDS tst_abstractshape tst_rectshape tst_ellipseshape
                tst_buildingshape tst_technicsshape tst_equipmentshape
        COMMENT "Running tests and generating coverage report"
    )
endif()
