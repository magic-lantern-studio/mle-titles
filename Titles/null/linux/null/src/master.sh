#!/bin/sh

# Check that MLE_ROOT is set and path exists

# Check that MLE_WORKPRINTS is set and path exists

# Set PATH to include $MLE_ROOT/bin

# Mastering tools don't currently create a missing "gen" directory if
# specified in the command line.
if [ ! -d "gen" ]; then
  # Create the "gen" directory if necessary.
  mkdir gen;
fi

# Generate Group chunks and meta-data.
echo "Running gengroup ..."
gengroup -l -d gen linux ../workprints/null.dwp actorid.h groupid.h

# Generate Scene chunks and meta-data.
echo "Running genscene ..."
genscene -l -d gen linux ../workprints/null.dwp sceneid.h

# Generate Media Reference chunks and meta-data.
echo "Running genmedia ..."
genmedia -l -d gen linux ../workprints/null.dwp null.BOM

# Generate meta-data for title DPP usage.
echo "Running gentables ..."
gentables -d gen linux ../workprints/null.dwp

# Generate Python script for Digital Playprint creation.
echo "Running genppscript ..."
genppscript -d gen linux ../workprints/null.dwp null.dpp null.py mlchunk

# Generate Digital Playprint.
echo "Running gendpp ..."
gendpp -l -s gen -d gen linux ../workprints/null.dwp gen/null.py
