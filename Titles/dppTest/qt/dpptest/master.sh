#!/bin/sh

# Mastering tools don't currently create a missing "gen" directory of
# specified in the command line.
if [ ! -d "gen" ]; then
  # Create the "gen" directory if necessary.
  mkdir gen;
fi

# Generate Group chunks and meta-data.
gengroup -l -d gen linux:qt ../workprints/DppImageTest.dwp actorid.h groupid.h
# Generate Scene chunks and meta-data.
genscene -l -d gen linux:qt ../workprints/DppImageTest.dwp sceneid.h
# Generate Media Reference chunks and meta-data.
genmedia -l -d gen linux:qt ../workprints/DppImageTest.dwp DppImageTest.BOM
# Generate meta-data for title DPP usage.
gentables -d gen linux:qt ../workprints/DppImageTest.dwp
# Generate TCL script for Digital Playprint creation.
genppscript -d gen linux:qt ../workprints/DppImageTest.dwp DppImageTest.dpp DppImageTest.tcl mlchunk
# Generate Digital Platyprint.
gendpp -l -s gen -d gen linux:qt ../workprints/DppImageTest.dwp gen/DppImageTest.tcl
