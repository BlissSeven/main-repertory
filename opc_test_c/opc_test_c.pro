TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    open62541/open62541.c

HEADERS += \
    open62541/open62541.h
