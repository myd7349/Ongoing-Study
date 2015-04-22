TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    struct_initialization.c

include(deployment.pri)
qtcAddDeployment()

