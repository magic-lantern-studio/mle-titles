QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloCube
TEMPLATE = app

CONFIG(debug, debug|release) {
# debug build
unix:!macx: LIBS += \
    -L$$PWD/../stages/build-CubeStage-Desktop-Debug/src -lCubeStage \
    -L$$PWD/../sets/build-CubeSet-Desktop-Debug/src -lCubeSet \
    -L$$PWD/../roles/build-CubeRole-Desktop-Debug/src -lCubeRole \
    -L$$PWD/../actors/build-CubeActor-Desktop-Debug/src -lCubeActor \
    -L/opt/MagicLantern/lib/mle/inventor -lmlert -lmlloaders \
    -L/opt/MagicLantern/lib -lDWP -lmlutil -lmlmath \
    -lCoin -lSoQt

INCLUDEPATH += $$PWD/../include $$PWD/../../../include /opt/MagicLantern/include
DEPENDPATH += $$PWD/../build/build-CubeStage-Desktop-Debug/src
} else {
# release build
unix:!macx: LIBS += \
    -L$$PWD/../stages/build-CubeStage-Desktop-Release/src -lCubeStage \
    -L$$PWD/../sets/build-CubeSet-Desktop-Release/src -lCubeSet \
    -L$$PWD/../roles/build-CubeRole-Desktop-Release/src -lCubeRole \
    -L$$PWD/../actors/build-CubeActor-Desktop-Release/src -lCubeActor \
    -L/opt/MagicLantern/lib/mle/inventor -lmlert -lmloaders \
    -L/opt/MagicLantern/lib -lDWP -lmlutil -lmlmath \
    -lCoin -lSoQt

INCLUDEPATH += $$PWD/../include $$PWD/../../../include /opt/MagicLantern/include
DEPENDPATH += $$PWD/../build/build-CubeStage-Desktop-Release/src
}

unix {
    MLE_ROOT=/opt/MagicLantern
}
# Suppress the default RPATH
unix: QMAKE_LFLAGS_RPATH=
unix: QMAKE_LFLAGS += \
    "-Wl,-rpath,$${MLE_ROOT}/lib/mle/qt \
     -Wl,-rpath,$${MLE_ROOT}/lib/mle/qt/inventor \
     -Wl,-rpath,$${MLE_ROOT}/lib \
     -Wl,-rpath,/usr/lib/qt5/bin"
DEFINES += MLE_NOT_DLL MLE_DIGITAL_WORKPRINT MLE_QT

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
