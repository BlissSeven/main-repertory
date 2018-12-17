QT += opcua widgets
CONFIG += c++11
DEPENDPATH += INCLUDEPATH
#INCLUDEPATH += \
#              $$PWD/../../../../src/plugins/opcua/open62541 \
INCLUDEPATH +=  D:\Qt\Qt5.11.2\5.11.2\msvc2015\qtopcua\src\plugins\opcua\open62541
SOURCES += main.cpp \
    mainwindow.cpp \
    opcuamodel.cpp \
    treeitem.cpp \
    common.cpp

#install
target.path = $$[QT_INSTALL_EXAMPLES]/opcua/opcuaviewer
INSTALLS += target

HEADERS += \
    mainwindow.h \
    opcuamodel.h \
    treeitem.h \
    common.h

RESOURCES += \
    opcuaviewer.qrc

