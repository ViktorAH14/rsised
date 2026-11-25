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

# LIB_SUFFIX = d
set_target_properties(shapes PROPERTIES DEBUG_POSTFIX "d")

# QT += widgets — PUBLI:
target_link_libraries(shapes PUBLIC Qt6::Widgets)

# Public headers
target_include_directories(shapes PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)

# --- TRANSLATIONS ---
# Translations belong to the library itself and live with it in i18n/.
# On Qt >= 6.7 the generated .qm files are automatically embedded
# into the target's resources (prefix "/i18n", path "/i18n/<name>.qm").
# No separate .qrc and no .qm files in the source tree are needed.
qt6_add_translations(shapes
    TS_FILES i18n/libshapes_ru.ts
)
