bin_PROGRAMS = helloCube

helloCube_SOURCES = helloCube.cpp title.cpp

helloCube_LDADD = \
	$(MLE_ROOT)/lib/mle/rehearsal/libmlert.so \
	$(MLE_ROOT)/lib/libDWP.so \
	$(MLE_ROOT)/lib/libmlutil.so \
	$(MLE_ROOT)/lib/libmlmath.so \
	-lX11 -ldl

helloCube_CPPFLAGS = \
	-DMLE_NOT_DLL \
	-I$(MLE_ROOT)/include
