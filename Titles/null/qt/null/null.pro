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

unix {
    MLE_ROOT=/opt/MagicLantern
}
# Suppress the default RPATH
unix: QMAKE_LFLAGS_RPATH=
unix: QMAKE_LFLAGS += \
    "-Wl,-rpath,$${MLE_ROOT}/lib/mle/qt \
     -Wl,-rpath,$${MLE_ROOT}/lib/mle/runtime \
     -Wl,-rpath,$${MLE_ROOT}/lib \
     -Wl,-rpath,/usr/lib/qt5/bin"

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

# Default rules for deployment
unix {
    target.path = /opt/MagicLantern/bin
}
