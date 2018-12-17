TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    open62541/open62541.c \
    client_subscription_loop.c

HEADERS += \
    open62541/open62541.h \
    my_datatype.hpp
