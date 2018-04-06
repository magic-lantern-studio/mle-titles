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
# Makefile - for making multiple versions of an app, library, etc.
#
#*************************************************************************

ISM_DEPTH = ../..
include $(ISM_DEPTH)/ismdefs

#
# Determine the mastering target.
#
ifndef MASTERTARG
MASTERTARG = C
endif

#
# Set which versions we are making.  There needs to be a subdirectory
# under here for each (for VERSIONS_MAKERULE to work).
#
VERSIONS = Debug Release

LDIRT = \
    actorid.h \
    groupid.h \
    sceneid.h \
    mlchunk.h \
    mlchunk.cxx \
    mltables.cxx \
    Scene1.chk \
    g0.chk \
    mandrill.chk \
    teaSet.chk \
    teapot.chk \
    winshade.chk \
    mtea.BOM \
    mtea.tcl \
    mtea.dpp \
    $(NULL)

all $(COMMONTARGS):
	$(VERSIONS_MAKERULE)

ifeq ($(MASTERTARG),C)

gengroup: ../mtea.dwp
	cd ..; gengroup -l -c -d win32 win32:brender mtea.dwp actorid.h groupid.h

genscene: ../mtea.dwp
	cd ..; genscene -l -c -d win32 win32:brender mtea.dwp sceneid.h

genmedia: ../mtea.dwp
	cd ..; genmedia -l -d win32 win32:brender mtea.dwp mtea.BOM

gentables: ../mtea.dwp
	cd ..; gentables -d win32 win32:brender mtea.dwp

genppscript: ../mtea.dwp
	cd ..; genppscript -d win32 win32:brender mtea.dwp mtea.dpp mtea.tcl mlchunk

gendpp: ../mtea.dwp
	cd ..; gendpp -l -s win32 -d win32 win32:brender mtea.dwp win32\\mtea.tcl

endif

ifeq ($(MASTERTARG),Java)

gengroup: ../mtea.dwp
	cd ..; gengroup -b -j com.wizzer.mtea -d win32 win32:brender mtea.dwp actorid.java groupid.java

genscene: ../mtea.dwp
	cd ..; genscene -b -j com.wizzer.mtea -d win32 win32:brender mtea.dwp sceneid.java

genmedia: ../mtea.dwp
	cd ..; genmedia -b -d win32 win32:brender mtea.dwp mtea.BOM

gentables: ../mtea.dwp
	cd ..; gentables -j com.wizzer.mtea -d win32 win32:brender mtea.dwp

genppscript: ../mtea.dwp
	cd ..; genppscript -d win32 win32:brender mtea.dwp mtea.dpp mtea.tcl mlchunk 

gendpp: ../mtea.dwp
	cd ..; gendpp -b -j com.wizzer.mtea -s win32 -d win32 win32:brender mtea.dwp win32\\mtea.tcl

endif

playprint: gengroup genscene genmedia gentables genppscript gendpp

NEED_THISPREF = 1

include $(ISMRULES)

$(THISPREF)clobber:

$(THISPREF)all: playprint
	$(CP) mtea.dpp ..