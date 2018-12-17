TEMPLATE = app
#CONFIG += console c++11

QT  += network
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    open62541/open62541.c

HEADERS += \
    open62541/open62541.h \
    C:/Program Files (x86)/Windows Kits/10/Include/10.0.14393.0/um/socketapi.h\
    C:/Program Files (x86)/Windows Kits/10/Include/10.0.14393.0/um/WinSocket.h
INCLUDEPATH+= C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\um

win32: LIBS += -L$$PWD/open62541/ -lopen62541

INCLUDEPATH += $$PWD/open62541
DEPENDPATH += $$PWD/open62541

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/open62541/open62541.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/open62541/libopen62541.a
