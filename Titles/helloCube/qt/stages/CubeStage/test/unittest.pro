QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = unittest
TEMPLATE = app

CONFIG(debug, debug|release) {
# debug build
unix:!macx: LIBS += \
    -L$$PWD/../../build-CubeStage-Desktop-Debug/src -lCubeStage \
    -L/opt/MagicLantern/lib/mle/inventor -lmlert -lmlloaders \
    -L/opt/MagicLantern/lib -lDWP -lmlutil -lmlmath \
    -lCoin -lSoQt

INCLUDEPATH += $$PWD/../include $$PWD/../../../include /opt/MagicLantern/include
DEPENDPATH += $$PWD/../build/build-CubeStage-Desktop-Debug/src
} else {
# release build
unix:!macx: LIBS += \
    -L$$PWD/../../build-CubeStage-Desktop-Release/src -lCubeStage \
    -L/opt/MagicLantern/lib/mle/inventor -lmlert -lmlloaders \
    -L/opt/MagicLantern/lib -lDWP -lmlutil -lmlmath \
    -lCoin -lSoQt

INCLUDEPATH += $$PWD/../include $$PWD/../../../include /opt/MagicLantern/include
DEPENDPATH += $$PWD/../build/build-CubeStage-Desktop-Release/src
}

DEFINES += MLE_NOT_DLL MLE_DIGITAL_WORKPRINT MLE_QT

SOURCES += \
    main.cpp

