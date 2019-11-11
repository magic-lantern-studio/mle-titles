bin_PROGRAMS = helloCube

helloCube_SOURCES = helloCube.cpp title.cpp callback.cpp

helloCube_LDADD = \
    $(top_srcdir)/../CubeStage/CubeStage/.libs/CubeStage.so \
    $(top_srcdir)/../CubeSet/CubeSet/.libs/CubeSet.so \
	$(MLE_ROOT)/lib/mle/inventor/libmlert.so \
	$(MLE_ROOT)/lib/libDWP.so \
	$(MLE_ROOT)/lib/libmlutil.so \
	$(MLE_ROOT)/lib/libmlmath.so \
	-lCoin -lSoXt -lX11 -lXm -lXt -ldl

#-lCoin -lSoXt -lX11 -lXt -ldl

helloCube_LDFLAGS = -Wl,--no-as-needed

helloCube_CPPFLAGS = \
	-DMLE_NOT_DLL \
	-DMLE_DIGITAL_WORKPRINT \
	-I$(top_srcdir)/../../../include \
	-I$(MLE_ROOT)/include
