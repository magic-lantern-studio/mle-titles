bin_PROGRAMS=helloWorld

helloWorld_SOURCES = helloWorld.cpp title.cpp callback.cpp

helloWorld_LDADD = \
    $(MLE_ROOT)/lib/mle/rehearsal/MleIvStage.so \
    $(MLE_ROOT)/lib/mle/rehearsal/Mle3dSet.so \
    $(MLE_ROOT)/lib/mle/rehearsal/Mle2dSet.so \
    $(MLE_ROOT)/lib/mle/rehearsal/Mle3dRole.so \
    $(MLE_ROOT)/lib/mle/rehearsal/Mle2dRole.so \
    $(MLE_ROOT)/lib/mle/rehearsal/libivroles.so \
    $(MLE_ROOT)/lib/mle/rehearsal/Mle3dColorMapMediaRef.so \
    $(MLE_ROOT)/lib/mle/rehearsal/Mle3dTextureMapMediaRef.so \
    $(MLE_ROOT)/lib/mle/rehearsal/Mle3dModelMediaRef.so \
    $(MLE_ROOT)/lib/mle/rehearsal/libmlert.so \
    $(MLE_ROOT)/lib/mle/rehearsal/libmlloaders.so \
    $(MLE_ROOT)/lib/libDWP.so \
    $(MLE_ROOT)/lib/libmlutil.so \
    $(MLE_ROOT)/lib/libmlmath.so \
    -llog4cxx -lCoin -lSoXt -lX11 -lXm -lXt -ldl

helloWorld_LDFLAGS = -Wl,--no-as-needed

helloWorld_CPPFLAGS = \
	-DMLE_NOT_DLL \
	-DMLE_DIGITAL_WORKPRINT \
	-DMLE_REHEARSAL \
	-I$(top_srcdir)/../../../include \
	-I$(MLE_ROOT)/include
