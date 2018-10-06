QT += testlib
QT -= gui

include(../../../configuration.pri)

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    tst_jsonmessagetest.cpp \
    $$APP_DIR/messages/RequestMessage.cpp \
    $$APP_DIR/messages/MotorSpeedRequest.cpp \
    $$APP_DIR/messages/DataRequest.cpp \
    $$APP_DIR/messages/ResetEncodersRequest.cpp \
    $$APP_DIR/messages/ResponseMessage.cpp \
    $$APP_DIR/messages/MotorResponse.cpp \
    $$APP_DIR/messages/EndstopResponse.cpp

INCLUDEPATH += \
    $$APP_DIR \
    $$APP_DIR/messages/

DEPENDPATH += \
    $$APP_DIR \
    $$APP_DIR/messages/

