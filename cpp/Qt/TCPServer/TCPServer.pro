#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T09:42:19
#
#-------------------------------------------------

QT       += core network
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TARGET = TCPServer
TEMPLATE = app


SOURCES += main.cpp\
    serverobj.cpp \
    clientobj.cpp

HEADERS  += \
    serverobj.h \
    clientobj.h

