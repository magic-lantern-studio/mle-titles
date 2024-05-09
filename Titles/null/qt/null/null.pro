QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = null
TEMPLATE = app

unix:!macx: LIBS += \
    -L$$PWD/../build/build-null-Desktop-Debug/src \
    -L/opt/MagicLantern/lib/mle/qt -lqtstage -lqtset \
    -L/opt/MagicLantern/lib/mle/runtime -lmlert -lmlloaders \
    -L/opt/MagicLantern/lib -lplayprint -lmlutil -lmlmath

#INCLUDEPATH += $$PWD/../build/build-mleqtstage-Desktop_Qt_5_8_0_GCC_64bit-Debug
INCLUDEPATH += $$PWD/../include /opt/MagicLantern/include /usr/local/include
DEPENDPATH += $$PWD/../../build-null-Desktop-Debug/src

DEFINES += MLE_DIGITAL_PLAYPRINT MLE_NOT_DLL

SOURCES += \
    main.cpp \
    title.cpp \
    callback.cpp \
    gen/mlchunk.cxx \
    gen/mltables.cxx

HEADERS += \
    mlPlatformData.h \
    callback.h \
    gen/actorid.h \
    gen/groupid.h \
    gen/sceneid.h \
    gen/mlchunk.h

win32 {
    copyfiles.commands += @echo NOW COPYING ADDITIONAL FILES &
    copyfiles.commands += cp -r ../$${TARGET}/gen/null.dpp $${DESTDIR}/
}
unix {
     copyfiles.commands += cp $$PWD/gen/null.dpp .
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
