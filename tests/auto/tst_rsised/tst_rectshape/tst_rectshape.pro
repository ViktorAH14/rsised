QT += testlib widgets
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_rectshape.cpp

include( ../../../../common.pri )
include( ../../../../app.pri )
