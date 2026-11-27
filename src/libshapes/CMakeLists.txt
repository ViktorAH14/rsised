qt_add_library(shapes STATIC
    abstractshape.cpp buildingshape.cpp curve.cpp ellipseshape.cpp
    equipmentshape.cpp pixmapshape.cpp polylineshape.cpp rectshape.cpp
    shaperesizer.cpp sizegripshape.cpp technicsshape.cpp textshape.cpp

    ../include/abstractshape.h    ../include/buildingshape.h
    ../include/curve.h            ../include/ellipseshape.h
    ../include/equipmentshape.h   ../include/pixmapshape.h
    ../include/polylineshape.h    ../include/rectshape.h
    ../include/shaperesizer.h     ../include/sizegripshape.h
    ../include/technicsshape.h    ../include/textshape.h
)

# "d" postfix in Debug builds (shapesd) - matches the qmake-era naming;
# consumers link the plain "shapes" target, CMake resolves the suffix itself
set_target_properties(shapes PROPERTIES DEBUG_POSTFIX "d")

# Headers expose QWidget-derived types, so Widgets must propagate to consumers
target_link_libraries(shapes PUBLIC Qt6::Widgets)

# Public headers
target_include_directories(shapes PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)

# --- TRANSLATIONS ---
# Translations belong to the library itself and live with it in i18n/.
# On Qt >= 6.7 the generated .qm file is automatically embedded into
# the target's resources - no separate .qrc and no .qm files in the
# source tree are needed.
# NOTE: auto-embedding requires Qt >= 6.7; if the project minimum is
# ever lowered below that, this must be replaced with an explicit
# qt_add_resources() step.
qt6_add_translations(shapes
    TS_FILES i18n/libshapes_ru.ts
)

