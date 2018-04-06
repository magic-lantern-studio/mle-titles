#!/bin/sh

# Mastering tools don't currently create a missing "gen" directory of
# specified in the command line.
if [ ! -d "gen" ]; then
  # Create the "gen" directory if necessary.
  mkdir gen;
fi

# Generate Group chunks and meta-data.
gengroup -l -d gen linux:qt ../workprints/HelloWorld.dwp actorid.h groupid.h
# Generate Scene chunks and meta-data.
genscene -l -d gen linux:qt ../workprints/HelloWorld.dwp sceneid.h
# Generate Media Reference chunks and meta-data.
genmedia -l -d gen linux:qt ../workprints/HelloWorld.dwp HelloWorld.BOM
# Generate meta-data for title DPP usage.
gentables -d gen linux:qt ../workprints/HelloWorld.dwp
# Generate TCL script for Digital Playprint creation.
genppscript -d gen linux:qt ../workprints/HelloWorld.dwp HelloWorld.dpp HelloWorld.tcl mlchunk
# Generate Digital Platyprint.
gendpp -l -s gen -d gen linux:qt ../workprints/HelloWorld.dwp gen/HelloWorld.tcl
