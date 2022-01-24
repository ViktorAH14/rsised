QT       += core gui svg xml printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += KWidgetsAddons

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buildingstruct.cpp \
    curve.cpp \
    device_shape.cpp \
    diagramscene.cpp \
    ellipse.cpp \
    item_resizer.cpp \
    main.cpp \
    mainwindow.cpp \
    pixmapitem.cpp \
    polyline.cpp \
    rectangle.cpp \
    rse_reader.cpp \
    rse_writer.cpp \
    sizegripitem.cpp \
    svg_reader.cpp \
    technics_shape.cpp \
    textitem.cpp

HEADERS += \
    buildingstruct.h \
    curve.h \
    device_shape.h \
    diagramscene.h \
    ellipse.h \
    item_resizer.h \
    mainwindow.h \
    pixmapitem.h \
    polyline.h \
    rectangle.h \
    rse_reader.h \
    rse_writer.h \
    sizegripitem.h \
    svg_reader.h \
    technics_shape.h \
    textitem.h

FORMS += \
    mainwindow.ui

include( ../../common.pri )
include( ../../app.pri )

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
