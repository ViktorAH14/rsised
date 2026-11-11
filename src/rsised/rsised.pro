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
QT += core gui svg xml printsupport core5compat
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++20

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
    ../../.github/ISSUE_TEMPLATE/bug_report.yml \
    ../../.github/ISSUE_TEMPLATE/build_issue.yml \
    ../../.github/ISSUE_TEMPLATE/config.yml \
    ../../.github/ISSUE_TEMPLATE/dependency_issue.yml \
    ../../.github/ISSUE_TEMPLATE/documentation_issue.yml \
    ../../.github/ISSUE_TEMPLATE/feature_request.yml \
    ../../.github/ISSUE_TEMPLATE/internal_task.yml \
    ../../.github/ISSUE_TEMPLATE/migration_issue.yml \
    ../../.github/ISSUE_TEMPLATE/performance_regression.yml \
    ../../.github/ISSUE_TEMPLATE/test_issue.yml \
    ../../.github/ISSUE_TEMPLATE/ui_layout_issue.yml \
    ../../.github/PULL_REQUEST_TEMPLATE/bug_fix.md \
    ../../.github/PULL_REQUEST_TEMPLATE/build_change.md \
    ../../.github/PULL_REQUEST_TEMPLATE/dependency_update.md \
    ../../.github/PULL_REQUEST_TEMPLATE/docs_update.md \
    ../../.github/PULL_REQUEST_TEMPLATE/feature.md \
    ../../.github/PULL_REQUEST_TEMPLATE/internal_task.md \
    ../../.github/PULL_REQUEST_TEMPLATE/migration.md \
    ../../.github/PULL_REQUEST_TEMPLATE/performance_fix.md \
    ../../.github/PULL_REQUEST_TEMPLATE/test_fix.md \
    ../../.github/PULL_REQUEST_TEMPLATE/ui_layout_change.md \
    ../../.github/pull_request_template.md \
    ../../CONTRIBUTING.md \
    ../../README_RU.md \
    ../../README.md

# [TRANSLATIONS]
TRANSLATIONS += \
    i18n/rsised_ru.ts
system(lrelease "$$_PRO_FILE_")
#tr.commands = lupdate "$$_PRO_FILE_" && lrelease "$$_PRO_FILE_"
PRE_TARGETDEPS += tr
QMAKE_EXTRA_TARGETS += tr

# [LIBRARY]
LIBS += -lshapes$${LIB_SUFFIX}

QMAKE_SUBSTITUTES += config.h.in

# [DEPLOY]
#CONFIG(app_bundle){
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
#}

#message($LD_LIBRARY_PATH)
