QT += testlib
QT -= gui

include(../../../configuration.pri)

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_jsonmessagetest.cpp
