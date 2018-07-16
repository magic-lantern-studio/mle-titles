QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hellocube
TEMPLATE = app

unix:!macx: LIBS += \
    -L$$PWD/../build/build-hellocube-Desktop_Qt_5_8_0_GCC_64bit-Debug/src \
    -lqtstage -lqtset -lqtrole -lqtmref \
    -L/opt/MagicLantern/lib/mle/inventor -lmlert \
    -L/opt/MagicLantern/lib -lDWP -lmlutil -lmlmath \
    -lCoin -lpng

#INCLUDEPATH += $$PWD/../build/build-mleqtstage-Desktop_Qt_5_8_0_GCC_64bit-Debug
INCLUDEPATH += $$PWD/../include $$PWD/../src/roles $$PWD/../src/actors /opt/MagicLantern/include /usr/local/include
DEPENDPATH += $$PWD/../build/build-hellocube-Desktop_Qt_5_8_0_GCC_64bit-Debug/src

DEFINES += MLE_DIGITAL_WORKPRINT MLE_NOT_DLL

SOURCES += \
    main.cpp \
    title.cpp \
    callback.cpp \
    ../src/actors/CubeActor.cpp \
    ../src/roles/CubeRole.cpp

HEADERS += \
    mlPlatformData.h \
    callback.h \
    ../include/ShapeActor.h \
    ../include/ShapeRole.h \
    ../include/CubeActor.h \
    ../include/CubeRole.h

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
