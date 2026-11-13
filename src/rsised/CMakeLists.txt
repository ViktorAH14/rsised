# Эквивалент rsised.pro (без секции [DEPLOY] — деплой выполняет CI/CD)

set(APPLICATION_NAME rsised)
set(EMAIL "ermolovva@gmail.com")
# VERSION и DATE приходят из cmake/Version.cmake через корневой CMakeLists.txt

qt_add_executable(rsised
    diagramscene.cpp main.cpp mainwindow.cpp rse_reader.cpp
    rse_writer.cpp svg_reader.cpp wallsetting.cpp

    diagramscene.h mainwindow.h rse_reader.h rse_writer.h
    svg_reader.h wallsetting.h

    # FORMS + RESOURCES: AUTOUIC и AUTORCC включены глобально
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

# --- QMAKE_SUBSTITUTES += config.h.in ---
# Шаблон написан под qmake ($$VAR): заменяем $$ на @ и подставляем.
# Один файл-источник обслуживает обе сборки; результат — в build-каталоге.
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" _cfg_tpl)
string(REPLACE "$$" "@" _cfg_tpl "${_cfg_tpl}")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/config.h.cmake.in" "${_cfg_tpl}")

configure_file(
    "${CMAKE_CURRENT_BINARY_DIR}/config.h.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"
)

# config.h генерируется в build-каталоге — добавляем его в поиск заголовков
target_include_directories(rsised PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

# --- TRANSLATIONS ---
qt6_add_translations(rsised TS_FILES i18n/rsised_ru.ts)

# --- Метаданные Windows (замена QMAKE_TARGET_PRODUCT/DESCRIPTION/COPYRIGHT) ---
if(WIN32)
    target_sources(rsised PRIVATE rsised.rc)
endif()
