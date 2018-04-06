# -*- Makefile -*-
#
#  Copyright (C) 2000-2007  Wizzer Works
#
#  Wizzer Works makes available all content in this file ("Content").
#  Unless otherwise indicated below, the Content is provided to you
#  under the terms and conditions of the Common Public License Version 1.0
#  ("CPL"). A copy of the CPL is available at
#
#      http://opensource.org/licenses/cpl1.0.php
#
#  For purposes of the CPL, "Program" will mean the Content.
#
#  For information concerning this Makefile, contact Mark S. Millard,
#  of Wizzer Works at msm@wizzerworks.com.
#
#*************************************************************************
#
# Makefile - for making a particular version of an app, library,
# etc. under that version subdirectory.
#
#*************************************************************************

#
# Set which configuration this is...
#
CONFIGURATION = Win32Release

ISM_DEPTH = ../..
LEAF_DEPTH = ..

#
# Turn off dependency generation. Note that sbr2dep.exe is currently
# broken.
#
NODEPENDS = 1

LCXXDEFS = \
	-DMLE_NOT_DLL \
	-DML_MATH_DEBUG=0 \
	-DML_FIXED_POINT=0 \
	$(NULL)

LCXXOPTS = \
	-Gz -Zp4 -FD \
	$(NULL)

LRCOPTS = \
	-l 0x409 \
	$(NULL)

LLDOPTS = \
	-libpath:$(MLE_ROOT)/lib/runtime \
	-libpath:$(MLE_ROOT)/lib/brender \
	$(NULL)

LLDLIBS = \
	actors.lib \
	brroles.lib \
	brsets.lib \
	brmrefs.lib \
	brstage.lib \
	pcstage.lib \
	playprint.lib \
	mlmath.lib \
	mlert.lib \
	$(NULL)

#
# Set the style of debug information. Turn on incremental
# linking.
#
DEBUG_INFO = PDB
INCREMENTAL_LINK = 1

#
# The actual work of building is in the directory above, in a file
# called "leafdefs".
#
include $(LEAF_DEPTH)/leafdefs

#
# Set the warning level.
#
WARN_LEVEL = -W3

#
# Set the style of C runtime library.
#
LIBC_STYLE = -ML
LIBC_STYLE_DEFS =
