#-------------------------------------------------
#
# Project created by QtCreator 2018-11-14T18:44:51
#
#-------------------------------------------------

QT       += core gui
QT       += multimediawidgets
QT      += multimedia

INCLUDEPATH += E:\c++\code\QTcode\camera\include
INCLUDEPATH += E:\c++\code\QTcode\camera\Common

LIBS        += E:\c++\code\QTcode\camera\win32\debug\TIS_UDSHL11d.lib
LIBS        += E:\c++\code\QTcode\camera\win32\release\TIS_UDSHL11.lib

# LIBS        += E:\c++\code\QTcode\camera\x64\debug\TIS_UDSHL11d_x64.lib
# LIBS        += E:\c++\code\QTcode\camera\x64\release\TIS_UDSHL11_x64.lib


#DEFINES += QT_NO_DEBUG_OUTPUT
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTtest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mylabel.cpp \
    snap7/snap7.cpp

HEADERS += \
        mainwindow.h \
    mylabel.h \
    ../camera/include/AnalogChannelItem.h \
    ../camera/include/AviSink.h \
    ../camera/include/Codec.h \
    ../camera/include/DeBayerTransform.h \
    ../camera/include/dshow_header.h \
    ../camera/include/dstring.h \
    ../camera/include/dvector.h \
    ../camera/include/Error.h \
    ../camera/include/filterdll.h \
    ../camera/include/filterfactory.h \
    ../camera/include/FilterInfoObject.h \
    ../camera/include/filterloader.h \
    ../camera/include/FrameFilter.h \
    ../camera/include/FrameFilterBase.h \
    ../camera/include/FrameFilterImpl.h \
    ../camera/include/FrameGrabberSink.h \
    ../camera/include/FrameHandlerSink.h \
    ../camera/include/FrameType.h \
    ../camera/include/Grabber.h \
    ../camera/include/GrabberListener.h \
    ../camera/include/GrabberSinkType.h \
    ../camera/include/iframe_def.h \
    ../camera/include/int_interface_pre.h \
    ../camera/include/IVCDProperty.h \
    ../camera/include/IVCDProperty_inl.h \
    ../camera/include/IVCDPropertyInterfaces.h \
    ../camera/include/IVCDPropertyInterfaces_inl.h \
    ../camera/include/libbasedefs.h \
    ../camera/include/libutil_string.h \
    ../camera/include/MediaStreamContainer.h \
    ../camera/include/MediaStreamSink.h \
    ../camera/include/MemBuffer.h \
    ../camera/include/MemBufferCollection.h \
    ../camera/include/OverlayBitmap.h \
    ../camera/include/simplectypes.h \
    ../camera/include/smart_com.h \
    ../camera/include/smart_ptr.h \
    ../camera/include/tisudshl.h \
    ../camera/include/UDSHL_defs.h \
    ../camera/include/UDSHL_lnk.h \
    ../camera/include/VCDPropertyDef.h \
    ../camera/include/VCDPropertyID.h \
    ../camera/include/VCDPropertyIDTis.h \
    ../camera/include/VideoCaptureDeviceItem.h \
    ../camera/include/VideoFormatDesc.h \
    ../camera/include/VideoFormatItem.h \
    ../camera/include/VideoNormItem.h \
    snap7/snap7.h \
    snap7/note.hpp

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DEFINES +=  _USE_32BIT_TIME_T

win32: LIBS += -L$$PWD/Win32/ -lsnap7

INCLUDEPATH += $$PWD/Win32
DEPENDPATH += $$PWD/Win32
