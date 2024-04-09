bin_PROGRAMS = helloCube

helloCube_SOURCES = helloCube.cpp title.cpp callback.cpp

helloCube_LDADD = \
    $(top_srcdir)/../CubeStage/CubeStage/.libs/CubeStage.so \
    $(top_srcdir)/../CubeSet/CubeSet/.libs/CubeSet.so \
    $(top_srcdir)/../CubeRole/CubeRole/.libs/CubeRole.so \
    $(MLE_ROOT)/lib/mle/inventor/Mle3dColorMapMediaRef.so \
    $(MLE_ROOT)/lib/mle/inventor/Mle3dTextureMapMediaRef.so \
    $(MLE_ROOT)/lib/mle/inventor/Mle3dModelMediaRef.so \
    $(MLE_ROOT)/lib/mle/inventor/libmlert.so \
    $(MLE_ROOT)/lib/mle/inventor/libmlloaders.so \
    $(MLE_ROOT)/lib/libDWP.so \
    $(MLE_ROOT)/lib/libmlutil.so \
    $(MLE_ROOT)/lib/libmlmath.so \
    -lCoin -lSoXt -lX11 -lXm -lXt -ldl

helloCube_LDFLAGS = -Wl,--no-as-needed

helloCube_CPPFLAGS = \
	-DMLE_NOT_DLL \
	-DMLE_DIGITAL_WORKPRINT \
	-I$(top_srcdir)/../../../include \
	-I$(MLE_ROOT)/include

if HAVE_LOG4CXX
helloCube_CPPFLAGS += $(LOG4CXX_CFLAGS)
helloCube_LDFLAGS += -Wl,-rpath=/usr/local/lib
helloCube_LDADD += $(LOG4CXX_LIBS)
endif
