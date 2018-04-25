#######################################
# The directory for object files and libraries of object code
libdir = $(exec_prefix)/lib/mle/rehearsal

#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = LabelWidgetRole.la

#######################################
# Build information for each library

# Sources for LabelWidgetActor
LabelWidgetRole_la_SOURCES = \
    LabelWidgetRole.cpp

# Linker options libTestProgram
LabelWidgetRole_la_LDFLAGS =  -module

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
LabelWidgetRole_la_CPPFLAGS = -DMLE_REHEARSAL -DMLE_NOT_DLL \
    -I$(top_srcdir)/include \
    -I$(MLE_ROOT)/include

