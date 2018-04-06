This directory contains an example title for the Qt target. The title is
"helloworld" for the Magic Lantern SDK targeting Qt applications. Essentially
the helloworld title displays a text string identified in the HelloWorld.dwp
Digital Workprint.

This file describes how to master the helloworld title.

The directions assume that the environment variable, MLE_HOME, is set to the
root of the Magic Lantern project area. For example,

    MLE_HOME=~/projects/MagicLantern

Your path should include the directory "$MLE_HOME/bin".

================================================================================

To master the helloworld title for the Qt platform, use the following steps.

1. Open a shell window and change the working directory to:
	cd $MLE_HOME/Titles/helloworld/qt/helloworld
        mkdir gen

   Note: currently there is bug in the mastering tools where the destination directory must already exist (i.e. gen) before code generation will work.

2. Generate the Actor Group chunks:
	gengroup -l -d gen linux:qt ../workprints/HelloWorld.dwp actorid.h groupid.h

	This will generate the actorid.h, groupid.h, group1.chk and 2dSet.chk files in the 'gen'
	directory.

3. Generate the Scene chunks:
	genscene -l -d gen linux:qt ../workprints/HelloWorld.dwp sceneid.h

	This will generate the sceneid.h and scene1.chk files in the 'gen' directory.

4. Generate the MediaRef chunks:
	genmedia -l -d gen linux:qt ../workprints/HelloWorld.dwp HelloWorld.BOM

	This will generate the HelloWorld.BOM in the 'gen' directory.

5. Generate the Runtime tables:
	gentables -d gen linux:qt ../workprints/HelloWorld.dwp

	This will generate the mltables.cxx file in the 'gen' directory.

6. Generate the DPP layout TCL script:
	genppscript -d gen linux:qt ../workprints/HelloWorld.dwp HelloWorld.dpp HelloWorld.tcl mlchunk 

	This will generate the HelloWorld.tcl script in the 'gen' directory.

7. Generate the DPP:
	gendpp -l -s gen -d gen linux:qt ../workprints/HelloWorld.dwp gen/HelloWorld.tcl

	This will generate the mlchunk.h and mlchunk.cxx files in the 'gen' directory.
	It will also generate the HelloWorld.dpp Digital Playprint file in the 'gen' directory.

8. Build the title with the generated source. The Qt project can be found in the
   $MLE_HOME/Titles/helloworld/qt/helloworld/helloworld.pro file.
   
