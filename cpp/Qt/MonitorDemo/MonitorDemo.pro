#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T10:32:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonitorDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# https://github.com/qt/qtbase/commit/d57a7c41712f8627a462d893329dc3f0dbb52d32
DEFINES += WINVER=0x0602 _WIN32_WINNT=0x0602


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        MultiMonitor.cpp

HEADERS += \
        mainwindow.h \
        MultiMonitor.h
