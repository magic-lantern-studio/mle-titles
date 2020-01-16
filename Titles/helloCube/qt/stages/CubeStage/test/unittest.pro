QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = unittest
TEMPLATE = app

CONFIG(debug, debug|release) {
# debug build
unix:!macx: LIBS += \
    -L$$PWD/../build/build-CubeStage-Desktop_Qt_4_8_7_GCC_64bit-Debug/src -lCubeStage \
    -L/opt/MagicLantern/lib/mle/runtime -lmlert \
    -L/opt/MagicLantern/lib -lmlutil -lplayprint -lmlmath \
    -lCoin -lSoQt

INCLUDEPATH += $$PWD/../include $$PWD/../../../include /opt/MagicLantern/include
DEPENDPATH += $$PWD/../build/build-CubeStage-Desktop_Qt_4_8_7_GCC_64bit-Debug/src
} else {
# release build
unix:!macx: LIBS += \
    -L$$PWD/../build/build-CubeStage-Desktop_Qt_4_8_7_GCC_64bit-Release/src -lCubeStage \
    -L/opt/MagicLantern/lib/mle/runtime -lmlert \
    -L/opt/MagicLantern/lib -lmlutil -lplayprint -lmlmath \
    -lCoin -lSoQt

INCLUDEPATH += $$PWD/../include $$PWD/../../../include /opt/MagicLantern/include
DEPENDPATH += $$PWD/../build/build-CubeStage-Desktop_Qt_4_8_7_GCC_64bit-Release/src
}

DEFINES += MLE_DIGITAL_PLAYPRINT MLE_NOT_DLL

SOURCES += \
    main.cpp \
    rtestubs.cpp
