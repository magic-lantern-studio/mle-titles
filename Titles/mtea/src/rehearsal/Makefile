#!smake

include $(ROOT)/usr/fw/make/fwcommondefs

## Change these flags to build with DEBUG, FW_FIXED_POINT=1 or FW_MATH_DEBUG=1
## If you change any of these flags, make sure to update DEBUGLIBDIR to 
## point to the right subdirectory of /usr/fw/lib for libraries compiled
## with the same flags. 

FWARITHDEFS	 = -DFW_FIXED_POINT=0 -DFW_MATH_DEBUG=0
DEBUGLIBDIR      = rehearsal

LC++DEFS = -DFW_REHEARSAL $(BRENDERDEFS)
LC++INCS = 
LLDLIBS = \
	-L$(ROOT)$(FW_INSTALL_DIR_BRENDER_REHEARSAL) \
	-L$(ROOT)$(FW_INSTALL_DIR_ACTORS_REHEARSAL) \
	-L$(ROOT)$(FW_INSTALL_DIR_PACKAGES_REHEARSAL) \
	-rpath $(FW_INSTALL_DIR_ACTORS_REHEARSAL) \
	$(NULL)

TARGETS    = SpinnerActor.so
WORKPRINTS = SpinnerActor.wpa SpinnerActor.wpd mtea.wp
SRC        = spinnera.cxx spinnera.h

default all: targets media

targets: $(TARGETS)

SpinnerActor.so: spinnera.o
	$(C++) $(LDDSOOPTS) $(LDFLAGS) -o $@ spinnera.o \
	    $(ROOT)$(FW_INSTALL_DIR_ACTORS_REHEARSAL)/Fw3dModelActor.so

media:
	(cd ../media; make rehearsal)


## Cause the title's targets and media to be built, then install
## them in the tree of shipped titles.
## Also cause the sources for this title to be installed into the
## tree of shipped sources.

install:targets install-media
	$(INSTALL_TITLE) -F $(FW_INSTALL_DIR_TITLES)/mtea/rehearsal \
		$(WORKPRINTS) $(TARGETS) 
	$(INSTALL_SRC_TITLE) -F $(FW_INSTALL_DIR_SRC)/titles/mtea/src \
		$(WORKPRINTS) $(SRC)
	$(INSTALL_SRC_TITLE) -F $(FW_INSTALL_DIR_SRC)/titles/mtea/src/rehearsal \
		-src Makefile.dist Makefile

install-media: media
	(cd ../media; make install-media)

sources:
	@echo $(SRC)

$(_FORCE):

include $(COMMONRULES)
