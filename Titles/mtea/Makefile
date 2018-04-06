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
# Makefile - ISM top level
#
#*************************************************************************

ISM_DEPTH = .
include $(ISM_DEPTH)/ismdefs

#
# Pick up some more defs specific to top level Makefile
#
include $(TOPLEVELDEFS)

#
# Descend into subdirectories for COMMONTARGS.  Note that it descends
# into BUILDDIR as well.
#
SUBDIRS = \
	src \
	media \
	$(NULL)

all $(COMMONTARGS):
	$(SUBDIRS_MAKERULE)

#
# Rules that belong only in the top level makefile
#
include $(TOPLEVELRULES)

include $(ISMRULES)
