QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imagetest
TEMPLATE = app

unix:!macx: LIBS += \
    /opt/MagicLantern/lib/mle/runtime/Mle2dImageActor.a \
    -L/opt/MagicLantern/lib -lqtstage -lqtset -lqtrole -lqtmref \
    -L/opt/MagicLantern/lib/mle/runtime -lmlert -lplayprint -lmlutil -lmlmath \
    -lpng

#INCLUDEPATH += $$PWD/../build/build-mleqtstage-Desktop_Qt_5_8_0_GCC_64bit-Debug
INCLUDEPATH += $$PWD/../include /opt/MagicLantern/include /usr/local/include
DEPENDPATH += $$PWD/../build/build-imagetest-Desktop_Qt_5_8_0_GCC_64bit-Debug/src

DEFINES += MLE_DIGITAL_PLAYPRINT MLE_NOT_DLL

SOURCES += \
    main.cpp \
    title.cpp \
    callback.cpp \
    rtestubs.cpp

HEADERS += \
    mlPlatformData.h \
    callback.h

win32 {
    copyfiles.commands += @echo NOW COPYING ADDITIONAL FILES &
    copyfiles.commands += cp -r ../$${TARGET}/wwlogo.png $${DESTDIR}/
}
unix {
     copyfiles.commands += cp ../../imagetest/wwlogo.png .
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
