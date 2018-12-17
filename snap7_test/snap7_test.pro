TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    snap7/client.cpp \
    snap7/snap7.cpp \
    snap7/client.cpp \
    snap7/snap7.cpp

HEADERS += \
    snap7/snap7.h \
    snap7/snap7.h \
    snap7/result.hpp

#DISTFILES += \
#    Win32/snap7.lib \
#    Win32/snap7.dll

DEFINES +=  _USE_32BIT_TIME_T



win32: LIBS += -L$$PWD/Win32/ -lsnap7

INCLUDEPATH += $$PWD/Win32
DEPENDPATH += $$PWD/Win32
