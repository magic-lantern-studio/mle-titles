QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CubeStage
TEMPLATE = lib

DEFINES += CUBESTAGE_LIBRARY

CONFIG += c++11
#CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../../../include /opt/MagicLantern/include /usr/local/include

DEFINES += MLE_NOT_DLL MLE_DIGITAL_WORKPRINT MLE_QT

SOURCES += \
    CubeStage.cpp

HEADERS += \
    $$PWD/../../../include/CubeStage.h \
    $$PWD/../../../include/CubeStage_global.h

# Default rules for deployment.
unix {
    target.path = /opt/MagicLantern/lib/mle/qt/inventor
    headers.path = /opt/MagicLantern/include/mle/qt
    headers.files = $$HEADERS
    INSTALLS += target headers
}
#!isEmpty(target.path): INSTALLS += target
