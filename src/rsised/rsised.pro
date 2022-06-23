QT       += core gui svg xml printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += KWidgetsAddons

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    diagramscene.cpp \
    main.cpp \
    mainwindow.cpp \
    rse_reader.cpp \
    rse_writer.cpp \
    svg_reader.cpp

HEADERS += \
    diagramscene.h \
    mainwindow.h \
    rse_reader.h \
    rse_writer.h \
    svg_reader.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
            i18n/rsised_ru.ts

system(lrelease "$$_PRO_FILE_")

tr.commands = lupdate "$$_PRO_FILE_" && lrelease "$$_PRO_FILE_"
            PRE_TARGETDEPS += tr
            QMAKE_EXTRA_TARGETS += tr

include( ../../common.pri )
include( ../../app.pri )

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    ../../doc/dev/shape_model.qmodel

LIBS += -lshapes$${LIB_SUFFIX}
