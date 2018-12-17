TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


DEFINES  -= UNICODE
DEFINES  += UMBCS
#设置当前工程为多字节字符集

SOURCES += \
    OPCClientDemo.cpp \
    opcda/OPCClient.cpp \
    opcda/OPCGroup.cpp \
    opcda/OPCHost.cpp \
    opcda/OPCItem.cpp \
    opcda/OPCItemData.cpp \
    opcda/OPCProperties.cpp \
    opcda/OPCServer.cpp \
    opcda/Transaction.cpp \
    opcda/opccomn_i.c \
    opcda/opcda_i.c \
    opcda/OpcEnum_i.c \
    my_opc_client.cpp \
    opcda/LocalSyncOPCCLient.cpp

HEADERS += \
    opcda/OPCClient.h \
    opcda/OPCClientToolKitDLL.h \
    opcda/opccomn.h \
    opcda/opcda.h \
    opcda/OpcEnum.h \
    opcda/OPCGroup.h \
    opcda/OPCHost.h \
    opcda/OPCItem.h \
    opcda/OPCItemData.h \
    opcda/OPCProperties.h \
    opcda/OPCServer.h \
    opcda/Transaction.h \
    opcda/LocalSyncOPCCLient.h

win32: LIBS += -L$$PWD/opcda/ -lOPCClientToolKit32D

INCLUDEPATH += $$PWD/opcda
DEPENDPATH += $$PWD/opcda

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/opcda/OPCClientToolKit32D.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/opcda/libOPCClientToolKit32D.a
