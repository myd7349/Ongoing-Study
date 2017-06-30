TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    FileUtility.cpp

HEADERS += \
    DataSpan.hpp \
    IDataSource.h \
    IFileDataSource.h \
    FileDataSourceBase.hpp \
    SimpleFileDataSource.hpp \
    FileUtility.h

win32-msvc* {
    LIBS += shlwapi.lib
}

win32-g++ {
    LIBS += libshlwapi
}

# References:
# QSanguosha
