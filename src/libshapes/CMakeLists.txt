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

# LIB_SUFFIX = d из common.pri: в Debug библиотека станет libshapesd
set_target_properties(shapes PROPERTIES DEBUG_POSTFIX "d")

# QT += widgets — PUBLIC: потребители наследуют модуль по цепочке
target_link_libraries(shapes PUBLIC Qt6::Widgets)

# Публичные заголовки — как в qmake
target_include_directories(shapes PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)

# TRANSLATIONS: ts-файл лежит в src/rsised/i18n
qt6_add_translations(shapes
    TS_FILES "${CMAKE_SOURCE_DIR}/src/rsised/i18n/libshapes_ru.ts"
)
