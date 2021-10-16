QT       += core gui svg xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += KWidgetsAddons

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    diagramscene.cpp \
    ellipse.cpp \
    ellipseresizer.cpp \
    main.cpp \
    mainwindow.cpp \
    polyline.cpp \
    polylineresizer.cpp \
    rectangle.cpp \
    rectangleresizer.cpp \
    rse_reader.cpp \
    rse_writer.cpp \
    sizegripitem.cpp \
    svg_reader.cpp

HEADERS += \
    diagramscene.h \
    ellipse.h \
    ellipseresizer.h \
    mainwindow.h \
    polyline.h \
    polylineresizer.h \
    rectangle.h \
    rectangleresizer.h \
    rse_reader.h \
    rse_writer.h \
    sizegripitem.h \
    svg_reader.h

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
