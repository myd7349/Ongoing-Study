#-------------------------------------------------
#
# Project created by QtCreator 2014-04-30T09:27:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IPAddrValidator
TEMPLATE = app

DEFINES += QTCREATOR_UTILS_STATIC_LIB

SOURCES += main.cpp\
        dialog.cpp \
    3rdparty/completinglineedit.cpp \
    3rdparty/execmenu.cpp \
    3rdparty/fancylineedit.cpp \
    3rdparty/historycompleter.cpp \
    3rdparty/hostosinfo.cpp \
    3rdparty/ipaddresslineedit.cpp \
    3rdparty/qtcassert.cpp \
    ipaddrctrl.cpp

HEADERS  += dialog.h \
    3rdparty/completinglineedit.h \
    3rdparty/execmenu.h \
    3rdparty/fancylineedit.h \
    3rdparty/historycompleter.h \
    3rdparty/hostosinfo.h \
    3rdparty/ipaddresslineedit.h \
    3rdparty/osspecificaspects.h \
    3rdparty/qtcassert.h \
    3rdparty/utils_global.h \
    ipaddrctrl.h
