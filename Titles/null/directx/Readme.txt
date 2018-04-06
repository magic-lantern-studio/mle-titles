This directory contains an example title for the Microsoft DirectX target. The title is "null"
for the Magic Lantern SDK targeting DirectX 9 applications. Essentially the null title does
nothing but may be used as the foundation for building other DirectX 9 Magic Lantern titles.

This file describes how to master the null title.

The directions assume that the environment variable, MLE_HOME, is set to the root
of the Magic Lantern project area. For example,

    MLE_HOME=M:\projects\MagicLantern

Your path should include the directory "%MLE_HOME%\bin".

==================================================================================================

To master the null title for the DirectX platform, use the following steps.

1. Open a shell window and change the working directory to:
	cd %MLE_HOME%\Titles\null\directx\src

2. Generate the Actor Group chunks:
	gengroup -l -d dxs win32:directx ../workprints/null.dwp actorid.h groupid.h

	This will generate the actorid.h, groupid.h, group1.chk and 2dSet.chk files in the 'dxs'
	directory.

3. Generate the Scene chunks:
	genscene -l -d dxs win32:directx ../workprints/null.dwp sceneid.h

	This will generate the sceneid.h and scene1.chk files in the 'dxs' directory.

4. Generate the MediaRef chunks:
	genmedia -l -d dxs win32:directx ../workprints/null.dwp null.BOM

	This will generate the null.BOM in the 'dxs' directory.

5. Generate the Runtime tables:
	gentables -d dxs win32:directx ../workprints/null.dwp

	This will generate the mltables.cxx file in the 'dxs' directory.

6. Generate the DPP layout TCL script:
	genppscript -d dxs win32:directx ../workprints/null.dwp null.dpp null.tcl mlchunk 

	This will generate the null.tcl script in the 'dxs' directory.

7. Generate the DPP:
	gendpp -l -s dxs -d dxs win32:directx ../workprints/null.dwp dxs\\null.tcl

	This will generate the mlchunk.h and mlchunk.cxx files in the 'dxs' directory.
	It will also generate the null.dpp Digital Playprint file in the 'dxs' directory.

	Note: If tcl84.dll from another version of TCL is in your path (i.e. Cygwin's /usr/bin/tcl84.dll),
	then gendpp will throw an "Access Violation" exception. Make sure that tcl84.dll that is used
	to build gendpp is the one that occurs first in your path.

8. Build the title with the generated source. The Visual Studio project can be found in the
   %MLE_HOME%\Titles\null\directx\build\mscv10\null.sln file.
   
