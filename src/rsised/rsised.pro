QT += core gui svg xml printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += KWidgetsAddons

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VERSION = 0.1.0
TARGET  = rsised_$${VERSION}

QMAKE_SUBSTITUTES += config.h.in

SOURCES += \
    diagramscene.cpp \
    main.cpp \
    mainwindow.cpp \
    rse_reader.cpp \
    rse_writer.cpp \
    svg_reader.cpp \
    wallsetting.cpp

HEADERS += \
    diagramscene.h \
    mainwindow.h \
    rse_reader.h \
    rse_writer.h \
    svg_reader.h \
    wallsetting.h

FORMS += \
    mainwindow.ui \
    wallsetting.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    ../../doc/dev/shape_model.qmodel \
    config.h.in

TRANSLATIONS += \
    i18n/rsised_ru.ts

#system(lrelease "$$_PRO_FILE_")

tr.commands = lupdate "$$_PRO_FILE_" && lrelease "$$_PRO_FILE_"
PRE_TARGETDEPS += tr
QMAKE_EXTRA_TARGETS += tr

include( ../../common.pri )
include( ../../app.pri )

LIBS += -lshapes$${LIB_SUFFIX}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

equals(BUILD_FLAG, release) {
#    QT_DIR = $$[QT_HOST_BINS]
#    win32:QMAKE_BIN = $${QT_DIR}/qmake.exe
    win32: contains(QT_ARCH, i386) {
            DEPLOY_CONFIG = win32
            #deploy.commands = cqtdeployer -bin $${DESTDIR}$${TARGET}.exe -qmake $${QMAKE_BIN} \
            #-targetDir $${PROJECT_ROOT_PATH}/distr/$${OS_SUFFIX} clear
        } else {
            DEPLOY_CONFIG = win64
            #deploy.commands = cqtdeployer -bin $${DESTDIR}$${TARGET}.exe -qmake $${QMAKE_BIN} \
            #-targetDir $${PROJECT_ROOT_PATH}/distr/$${OS_SUFFIX} \
            #-extraLibs zlib1,libssp-0,libpng16-16,libpcre2,libKF5WidgetsAddons,libintl-8,libiconv-2,libharfbuzz-0,libgraphite2,libglib-2.0-0,libfreetype-6,libbz2-1,libbrotlidec,libbrotlicommon \
            #clear
        }
    linux-g++:{
#        QMAKE_BIN = $${QT_DIR}/qmake
        DEPLOY_CONFIG = linux
        #deploy.commands = cqtdeployer -bin $${DESTDIR}$${TARGET} \
        #-targetDir $${PROJECT_ROOT_PATH}/distr/$${OS_SUFFIX} clear
    }
QMAKE_POST_LINK += /home/viktor/develop/Qt/RSiSed/deploy/deploy.sh $${DEPLOY_CONFIG}
}
#message($${TARGET})
