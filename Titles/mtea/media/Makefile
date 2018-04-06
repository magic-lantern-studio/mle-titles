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
# Makefile for installing title media.
#
# $Id$
#
###########################################################################

ISM_DEPTH = ..
include $(ISM_DEPTH)/ismdefs

## Files in this directory

SOURCE_MEDIA = \
	teapot.dat \
	teapot.iv \
	$(NULL)

## Target specific files 

SHARE_TARGETS = \
	teapot.dat \
	$(NULL)

SGI_TARGETS = \
	$(SHARE_TARGETS) \
	mandrill.rgb \
	teapot.iv \
	$(NULL)

WIN32_TARGETS = \
	$(SHARE_TARGETS) \
	mandrill.pix \
	winshade.tab \
	$(NULL)

# Note that we don't build any media files by default.
# Only build based on rehearsal, sgi and win32 targets, 
# or when installing for rehearsal or sgi.

PLATFORM_TARGETS = $(SGI_TARGETS) $(WIN32_TARGETS)

# We're not actually building anything here, so there's
# nothing to delete.
LDIRT	= *.fwa *.fwm *.fwt *.fwg *.wav $(PC_INSTALL_LIST)

default all: targets

targets: $(SOURCE_MEDIA)

rehearsal sgi: $(SGI_TARGETS)

win32: $(WIN32_TARGETS)

install: targets rehearsal

install-media: targets rehearsal
	$(INSTALL) -d $(MLE_ROOT)/Titles/mtea/media
	$(INSTALL) $(SGI_TARGETS) $(WIN32_TARGETS) $(MLE_ROOT)/mtea/media

$(_FORCE):

include $(ISMRULES)
