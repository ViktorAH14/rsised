include( ../../common.pri )
include( ../../app.pri )
include(../../version.pri)

# [VARIABLE]
APPLICATION_NAME = rsised
TARGET = $${APPLICATION_NAME}
DESCRIPTION = Drawing up schemes for the arrangement of forces and means in case of fire
EMAIL = ermolovva@gmail.com
PUBLISHER = ErmolovVA

# [QT CONFIG]
QT += core gui svg xml printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += KWidgetsAddons
CONFIG += c++17

# [FILES]
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
    config.h.in \
    deploy.sh \
    cqt_linux_targz.json.in \
    install.sh.in \
    rsised-mime.xml.in \
    uninstall.sh.in \
    rsised.desktop.in \
    README.in \
    ../../doc/dev/shape_model.qmodel

# [TRANSLATIONS]
TRANSLATIONS += \
    i18n/rsised_ru.ts
#system(lrelease "$$_PRO_FILE_")
tr.commands = lupdate "$$_PRO_FILE_" && lrelease "$$_PRO_FILE_"
PRE_TARGETDEPS += tr
QMAKE_EXTRA_TARGETS += tr

# [LIBRARY]
LIBS += -lshapes$${LIB_SUFFIX}

QMAKE_SUBSTITUTES += config.h.in

# [DEPLOY]
CONFIG(app_bundle){
    equals(BUILD_FLAG, release) {
#       QT_DIR = $$[QT_HOST_BINS]
#       win32:QMAKE_BIN = $${QT_DIR}/qmake.exe
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
            DEPLOY_CONFIG = linux
            QMAKE_SUBSTITUTES += cqt_linux_targz.json.in
            QMAKE_SUBSTITUTES += install.sh.in
            QMAKE_SUBSTITUTES += uninstall.sh.in
            QMAKE_SUBSTITUTES += rsised.desktop.in
            QMAKE_SUBSTITUTES += rsised-mime.xml.in
            QMAKE_SUBSTITUTES += README.in
        }
    QMAKE_POST_LINK += ${PWD}/deploy.sh $${DEPLOY_CONFIG} $${VERSION} $${APPLICATION_NAME}
    }
}

#message($LD_LIBRARY_PATH)
