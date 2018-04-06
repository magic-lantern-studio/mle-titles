QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloworld
TEMPLATE = app

unix:!macx: LIBS += \
    -L$$PWD/../build/build-helloworld-Desktop_Qt_5_8_0_GCC_64bit-Debug/src \
    -lqtstage -lqtset -lqtrole -lqtmref \
    -L/opt/MagicLantern/lib/mle/runtime -lmlert \
    -L/opt/MagicLantern/lib -lplayprint -lmlutil -lmlmath \
    -lpng

#INCLUDEPATH += $$PWD/../build/build-mleqtstage-Desktop_Qt_5_8_0_GCC_64bit-Debug
INCLUDEPATH += $$PWD/../include $$PWD/roles $$PWD/actors /opt/MagicLantern/include /usr/local/include
DEPENDPATH += $$PWD/../build/build-helloworld-Desktop_Qt_5_8_0_GCC_64bit-Debug/src

DEFINES += MLE_NOT_DLL

SOURCES += \
    main.cpp \
    title.cpp \
    callback.cpp \
    gen/mlchunk.cxx \
    gen/mltables.cxx \
    actors/LabelWidgetActor.cpp \
    roles/LabelWidgetRole.cpp

HEADERS += \
    mlPlatformData.h \
    callback.h \
    gen/actorid.h \
    gen/groupid.h \
    gen/mlchunk.h \
    gen/sceneid.h \
    actors/LabelWidgetActor.h \
    roles/LabelWidgetRole.h \
    WidgetRole.h \
    WidgetActor.h

win32 {
    copyfiles.commands += @echo NOW COPYING ADDITIONAL FILES &
    copyfiles.commands += cp -r ../$${TARGET}/gen/HelloWorld.dpp $${DESTDIR}/
}
unix {
     copyfiles.commands += cp ../../helloworld/gen/HelloWorld.dpp .
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

DISTFILES += \
    ../workprints/HelloWorld.dwp
