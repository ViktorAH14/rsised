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
