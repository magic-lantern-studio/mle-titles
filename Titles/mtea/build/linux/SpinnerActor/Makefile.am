#######################################
# The directory for object files and libraries of object code
libdir = $(exec_prefix)/lib/mle/rehearsal

#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = SpinnerActor.la

#######################################
# Build information for each library

# Sources for SpinnerActor
SpinnerActor_la_SOURCES = ../../../src/spinnera.cxx

# Linker options SpinnerActor
SpinnerActor_la_LDFLAGS = -module -version-info 1:0:0

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
SpinnerActor_la_CPPFLAGS = \
    -DMLE_DIGITAL_WORKPRINT \
    -DMLE_REHEARSAL \
    -DMLE_NOT_UTIL_DLL \
    -DMLE_NOT_MATH_DLL \
    -DMLE_NOT_DWP_DLL \
    -DMLE_NOT_RUNTIME_DLL \
    -DMLE_NOT_3DMODELCARRIER_DLL \
    -DMLE_NOT_3DCOLORMAPCARRIER_DLL \
    -DMLE_NOT_3DTEXTUREMAPCARRIER_DLL \
    -DMLE_NOT_3DTRANSFORMCARRIER_DLL \
    -DMLE_NOT_PROPERTY_DLL \
    -DMLE_NOT_SPINNERACTOR_DLL \
    -I$(top_srcdir)/include -I$(top_srcdir)/../../../src \
	-I$(MLE_ROOT)/include

if HAVE_LOG4CXX
#SpinnerActor_la_SOURCES += \
#    audio_random_portaudio.h \
#    audio_random_portaudio.cpp
	
SpinnerActor_la_CPPFLAGS += $(LOG4CXX_CFLAGS)

#SpinnerActor_la_LDFLAGS += $(LOG4CXX_LIBS)
endif