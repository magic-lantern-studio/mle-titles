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

# Linker options libTestProgram
SpinnerActor_la_LDFLAGS = -module

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
SpinnerActor_la_CPPFLAGS = -DMLE_DIGITAL_WORKPRINT -DMLE_REHEARSAL -DMLE_NOT_DLL \
    -I$(top_srcdir)/include -I$(top_srcdir)/../../../src \
	-I$(MLE_ROOT)/include
