set(APPLICATION_NAME rsised)
set(EMAIL "ermolovva@gmail.com")
# VERSION and DATE come from cmake/Version.cmake via the root CMakeLists.txt

qt_add_executable(rsised
    diagramscene.cpp main.cpp mainwindow.cpp rse_reader.cpp
    rse_writer.cpp svg_reader.cpp wallsetting.cpp

    diagramscene.h mainwindow.h rse_reader.h rse_writer.h
    svg_reader.h wallsetting.h

    # FORMS + RESOURCES: AUTOUIC and AUTORCC are included globally
    mainwindow.ui wallsetting.ui
    resource.qrc
)

# QT += core gui svg xml printsupport core5compat widgets
target_link_libraries(rsised PRIVATE
    shapes
    Qt6::Core
    Qt6::Gui
    Qt6::Svg
    Qt6::Xml
    Qt6::PrintSupport
    Qt6::Core5Compat
    Qt6::Widgets
)

# --- config.h ---
# The template uses CMake-style @VAR@ placeholders and is configured
# directly into the build directory.
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"
    @ONLY
)

# config.h is generated in the build directory — add it to the header search path.
target_include_directories(rsised PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

# --- TRANSLATIONS ---
# Only the application's own translations live here.
# Library (shapes) translations are handled by the shapes target itself
# and are loaded from its embedded resources at runtime.
# On Qt >= 6.7 the generated .qm file is automatically embedded
# into the target's resources (path "/i18n/rsised_ru.qm").
qt6_add_translations(rsised
    TS_FILES i18n/rsised_ru.ts
)

# --- Windows metadata (replacement for QMAKE_TARGET_PRODUCT/DESCRIPTION/COPYRIGHT) ---
if(WIN32)
    target_sources(rsised PRIVATE rsised.rc)
endif()
