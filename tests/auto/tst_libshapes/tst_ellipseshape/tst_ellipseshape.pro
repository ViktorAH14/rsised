QT += testlib widgets
QT -= gui

CONFIG += qt warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_ellipseshape.cpp

include( ../../../../common.pri )
include( ../../../../app.pri )

LIBS += -lshapes$${LIB_SUFFIX}
