include( ../../common.pri )
include( ../../lib.pri )

QT += widgets

TARGET = shapes$${LIB_SUFFIX}
TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractshape.cpp \
    buildingshape.cpp \
    curve.cpp \
    deviceshape.cpp \
    ellipseshape.cpp \
    pixmapshape.cpp \
    polylineshape.cpp \
    rectshape.cpp \
    shaperesizer.cpp \
    sizegripshape.cpp \
    technicsshape.cpp \
    textshape.cpp

HEADERS += \
    ../include/abstractshape.h \
    ../include/buildingshape.h \
    ../include/curve.h \
    ../include/deviceshape.h \
    ../include/ellipseshape.h \
    ../include/pixmapshape.h \
    ../include/polylineshape.h \
    ../include/rectshape.h \
    ../include/shaperesizer.h \
    ../include/sizegripshape.h \
    ../include/technicsshape.h \
    ../include/textshape.h
    
TRANSLATIONS += \
    ../rsised/i18n/libshapes_ru.ts

system(lrelease "$$_PRO_FILE_")

tr.commands = lupdate "$$_PRO_FILE_" && lrelease "$$_PRO_FILE_"
PRE_TARGETDEPS += tr
QMAKE_EXTRA_TARGETS += tr

# Default rules for deployment.
#unix {
#    target.path = $$[QT_INSTALL_PLUGINS]/generic
#}
#!isEmpty(target.path): INSTALLS += target

win32 {
    QMAKE_TARGET_PRODUCT = libshapes
    QMAKE_TARGET_DESCRIPTION = Library for RSiSed
}

DISTFILES += \
    ../../doc/dev/buildingShape/buildingshape.qmodel
