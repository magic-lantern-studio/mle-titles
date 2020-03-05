QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloCube
TEMPLATE = app

CONFIG(debug, debug|release) {
# debug build
unix:!macx: LIBS += \
    -L$$PWD/../build/build-CubeStage-Desktop_Qt_4_8_7_GCC_64bit-Debug/src -lCubeStage \
    -L$$PWD/../../../sets/CubeSet/build/build-CubeSet-Desktop_Qt_4_8_7_GCC_64bit-Debug/src -lCubeSet \
    -L$$PWD/../../../roles/CubeRole/build/build-CubeRole-Desktop_Qt_4_8_7_GCC_64bit-Debug/src -lCubeRole \
    -L/opt/MagicLantern/lib/mle/qt -lmlert \
    -L/opt/MagicLantern/lib -lDWP -lmlutil -lmlmath \
    -lCoin -lSoQt

INCLUDEPATH += $$PWD/../include $$PWD/../../../include /opt/MagicLantern/include
DEPENDPATH += $$PWD/../build/build-CubeStage-Desktop_Qt_4_8_7_GCC_64bit-Debug/src
} else {
# release build
unix:!macx: LIBS += \
    -L$$PWD/../build/build-CubeStage-Desktop_Qt_4_8_7_GCC_64bit-Release/src -lCubeStage \
    -L$$PWD/../../../sets/CubeSet/build/build-CubeSet-Desktop_Qt_4_8_7_GCC_64bit-Release/src -lCubeSet \
    -L$$PWD/../../../roles/CubeRole/build/build-CubeRole-Desktop_Qt_4_8_7_GCC_64bit-Release/src -lCubeRole \
    -L/opt/MagicLantern/lib/mle/qt -lmlert \
    -L/opt/MagicLantern/lib -lDWP -lmlutil -lmlmath \
    -lCoin -lSoQt

INCLUDEPATH += $$PWD/../include $$PWD/../../../include /opt/MagicLantern/include
DEPENDPATH += $$PWD/../build/build-CubeStage-Desktop_Qt_4_8_7_GCC_64bit-Release/src
}

DEFINES += MLE_DIGITAL_WORKPRINT MLE_NOT_DLL

SOURCES += \
    callback.cpp \
    main.cpp \
    title.cpp

HEADERS += \
    callback.h \
    mlPlatformData.h

win32 {
    copyfiles.commands += @echo NOW COPYING ADDITIONAL FILES &
    copyfiles.commands += cp -r ../$${TARGET}/workprints/HelloWorld.dwp $${DESTDIR}/
}
unix {
     copyfiles.commands += cp $$PWD/../workprints/HelloCube.dwp .
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

DISTFILES += \
    $$PWD/../workprints/HelloCube.dwp
