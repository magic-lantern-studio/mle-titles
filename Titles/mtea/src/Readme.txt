This file describes how to master the mtea title.

The directions assume that the environment variable, MLE_HOME, is set to the root
of the Magic Lantern project area. For example,

    MLE_HOME=M:\projects\MagicLantern

Your path should include the directory "%MLE_HOME%\bin".

==================================================================================================

To master the mtea title for the BRender platform, use the following steps.

1. Open a shell window and change the working directory to:
	cd %MLE_HOME%\Titles\mtea\src

2. Generate the Actor Group chunks:
	gengroup -l -d win32 win32:brender mtea.dwp actorid.h groupid.h

	This will generate the actorid.h, groupid.h, g0.chk and teaSet.chk files in the win32
	directory.

3. Generate the Scene chunks:
	genscene -l -d win32 win32:brender mtea.dwp sceneid.h

	This will generate the sceneid.h and Scene1.chk files in the win32 directory.

4. Generate the MediaRef chunks:
	genmedia -l -d win32 win32:brender mtea.dwp mtea.BOM

	This will generate the mtea.BOM, mandrill.chk, teapot.chk, and winshade.chk files in
	the win32 directory.

5. Generate the Runtime tables:
	gentables -d win32 win32:brender mtea.dwp

	This will generate the mltables.cxx file in the win32 directory.

6. Generate the DPP layout TCL script:
	genppscript -d win32 win32:brender mtea.dwp mtea.dpp mtea.tcl mlchunk 

	This will generate the mtea.tcl script in the win32 directory.

7. Generate the DPP:
	gendpp -l -s win32 -d win32 win32:brender mtea.dwp win32\\mtea.tcl

	This will generate the mlchunk.h and mlchunk.cxx files in the win32 directory.
	It will also generate the mtea.dpp Digital Playprint file in the win32 directory.

	Note: If tcl84.dll from another version of TCL is in your path (i.e. Cygwin's /usr/bin/tcl84.dll),
	then gendpp will throw an "Access Violation" exception. Make sure that tcl84.dll that is used
	to build gendpp is the one that occurs first in your path.

8. Build the title with the generated source. The Visual Studio 6.0 project can be found in the
   %MLE_HOME%\Titles\mtea\src\win32\mtea.dsw file.
   

==================================================================================================

***************** NOTE THAT THE JAVA PLATFORM FOR THIS TITLE IS NOT YET IN PLACE *****************

To master the mtea title for the Java platform, perform the following steps:

1. Open a shell Window and change the working directory to:
	cd %MLE_HOME%\titles\mtea\src\java

2. Generate the Actor Group chunks:
	gengroup -b -j com.wizzer.mtea -d win32 win32:brender mtea.dwp actorid.java groupid.java

	This will generate the actorid.java, groupid.java, g0.chk and teaSet.chk files in the win32
	directory. 

3. Generate the Scene chunks:
	genscene -b -j com.wizzer.mtea -d win32 win32:brender mtea.dwp sceneid.java

	This will generate the sceneid.java and Scene1.chk files in the win32 directory.

4. Generate the MediaRef chunks:
	genmedia -b -d win32 win32:brender mtea.dwp mtea.BOM

	This will generate the mtea.BOM, mandrill.chk, teapot.chk, and winshade.chk files in
	the win32 directory.

5. Generate the Runtime tables:
	gentables -j com.wizzer.mtea -d win32 win32:brender mtea.dwp

	This will generate the mltables.java file in the win32 directory.

6. Generate the DPP layout TCL script:
	genppscript -d win32 win32:brender mtea.dwp mtea.dpp mtea.tcl mlchunk

	This will generate the mtea.tcl script in the win32 directory.

7. Generate the DPP:
	gendpp -b -j com.wizzer.mtea -s win32 -d win32 win32:brender mtea.dwp win32\\mtea.tcl

	This will generate the mlchunk.h and mlchunk.cxx files in the win32 directory.
	It will also generate the mtea.dpp Digital Playprint file in the win32 directory.

	Note: If tcl84.dll from another version of TCL is in your path (i.e. Cygwin's /usr/bin/tcl84.dll),
	then gendpp will throw an "Access Violation" exception. Make sure that tcl84.dll that is used
	to build gendpp is the one that occurs first in your path.

8. Build the title with the generated source.
