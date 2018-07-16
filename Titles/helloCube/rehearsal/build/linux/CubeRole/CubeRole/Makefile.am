#######################################
# The directory for object files and libraries of object code
libdir = $(exec_prefix)/lib/mle/inventor

#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = CubeRole.la

#######################################
# Build information for each library

# Sources for CubeRole
CubeRole_la_SOURCES = $(top_srcdir)/../../../src/roles/CubeRole.cpp

# Linker options libTestProgram
CubeRole_la_LDFLAGS = -module

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
CubeRole_la_CPPFLAGS = -DMLE_DIGITAL_WORKPRINT -DMLE_NOT_DLL \
	-I$(top_srcdir)/include -I$(top_srcdir)/../../../include \
	-I$(MLE_ROOT)/include
