This directory contains an example title for the Qt target. The title is "null"
for the Magic Lantern SDK targeting Qt applications. Essentially the null title
does nothing but may be used as the foundation for building other Qt Magic Lantern titles.

This file describes how to master the null title.

The directions assume that the environment variable, MLE_HOME, is set to the root
of the Magic Lantern project area. For example,

    MLE_HOME=~/projects/MagicLantern

Your path should include the directory "$MLE_HOME/bin".

==================================================================================================

To master the null title for the Qt platform, use the following steps.

1. Open a shell window and change the working directory to:
	cd $MLE_HOME/Titles/null/qt/null
        mkdir gen

   Note: currently there is bug in the mastering tools where the destination directory must already exist (i.e. gen) before code generation will work.

2. Generate the Actor Group chunks:
	gengroup -l -d gen linux:qt ../workprints/null.dwp actorid.h groupid.h

	This will generate the actorid.h, groupid.h, group1.chk and 2dSet.chk files in the 'gen'
	directory.

3. Generate the Scene chunks:
	genscene -l -d gen linux:qt ../workprints/null.dwp sceneid.h

	This will generate the sceneid.h and scene1.chk files in the 'gen' directory.

4. Generate the MediaRef chunks:
	genmedia -l -d gen linux:qt ../workprints/null.dwp null.BOM

	This will generate the null.BOM in the 'gen' directory.

5. Generate the Runtime tables:
	gentables -d gen linux:qt ../workprints/null.dwp

	This will generate the mltables.cxx file in the 'gen' directory.

6. Generate the DPP layout Python script:
	genppscript -d gen linux:qt ../workprints/null.dwp null.dpp null.py mlchunk 

	This will generate the null.py script in the 'gen' directory.

7. Generate the DPP:
	gendpp -l -s gen -d gen linux:qt ../workprints/null.dwp gen/null.py

	This will generate the mlchunk.h and mlchunk.cxx files in the 'gen' directory.
	It will also generate the null.dpp Digital Playprint file in the 'gen' directory.

8. Build the title with the generated source. The Qt project can be found in the
   $MLE_HOME/Titles/null/qt/null/null.pro file.
   
