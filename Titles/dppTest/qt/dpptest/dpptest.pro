QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dpptest
TEMPLATE = app

unix:!macx: LIBS += \
    /opt/MagicLantern/lib/mle/runtime/Mle2dImageActor.a \
    -L/opt/MagicLantern/lib -lqtstage -lqtset -lqtrole -lqtmref \
    -L/opt/MagicLantern/lib/mle/runtime -lmlert -lplayprint -lmlutil -lmlmath \
    -lpng

#INCLUDEPATH += $$PWD/../build/build-mleqtstage-Desktop_Qt_5_8_0_GCC_64bit-Debug
INCLUDEPATH += $$PWD/../include /opt/MagicLantern/include /usr/local/include
DEPENDPATH += $$PWD/../build/build-dpptest-Desktop_Qt_5_8_0_GCC_64bit-Debug/src

DEFINES += MLE_NOT_DLL

SOURCES += \
    main.cpp \
    title.cpp \
    callback.cpp \
    gen/mltables.cxx \
    gen/mlchunk.cxx

HEADERS += \
    mlPlatformData.h \
    callback.h \
    gen/actorid.h \
    gen/groupid.h \
    gen/sceneid.h \
    gen/mlchunk.h

win32 {
    copyfiles.commands += @echo NOW COPYING ADDITIONAL FILES &
    copyfiles.commands += cp -r ../$${TARGET}/wwlogo.png $${DESTDIR}/media/
    copyfiles.commands += cp -r ../$${TARGET}/gen/DppImageTest.dpp $${DESTDIR}/
}
unix {
    copyfiles.commands += mkdir -p ./media; cp ../../dpptest/wwlogo.png ./media;
    copyfiles.commands += cp ../../dpptest/gen/DppImageTest.dpp .
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

DISTFILES += \
    ../workprints/Mle2dSet.wpd \
    ../workprints/MleImageActor.wpd \
    ../workprints/MleImageRole.wpd \
    ../workprints/DppImageTest.dwp
