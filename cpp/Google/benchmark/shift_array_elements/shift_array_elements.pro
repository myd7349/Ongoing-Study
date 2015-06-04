TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    shift_array_elements.cpp \

include(deployment.pri)
qtcAddDeployment()


