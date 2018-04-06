This file describes the steps for mastering the DPP Image Test title for the Magic Lantern
Java Runtime Engine. Keep in mind that Java uses a Big Endian file format; therefore, we
specify the "-b" option when appropriate.

To master the DPP Image Test title, use the following steps.

1. Change working directory to:
	cd M:\projects\MagicLantern\Titles\dppTest\java\com.wizzer.mle.title.dpptest\src

2. Generate the Actor Group chunks:
	gengroup -b -j gen -d gen java2d DppImageTest.dwp ActorID.java GroupID.java

	Note: this will generate the Group and Set chunks in the gen subdirectory.
	The ActorID.java and GroupID.java classes will also be generated in the the gen
	subdirectory, belonging to the "gen" package.

3. Generate the Scene chunks:
	genscene -b -j gen -d gen java2d DppImageTest.dwp SceneID.java

	Note: this will generate the Scene chunks in the gen subdirectory.
	The SceneID.java class will also be generated in the gen subdirectory, belonging
	to the "gen" package.

4. Generate the MediaRef chunks:
	genmedia -b -d gen java2d DppImageTest.dwp DppImageTest.BOM

	Note: this will generate the MediaRef chunks in the gen subdirectory.
	A bill-of-materials, DppImageTest.BOM, will also be generated in the gen
	subdirectory.

5. Generate the Runtime tables:
	gentables -j gen -d gen java2d DppImageTest.dwp

	Note: this will generate the MleRuntimeTables.java class that describes
        the tables for constructing the title. It will be placed in the gen subdirectory.

6. Generate the DPP layout TCL script:
	genppscript -d gen java2d DppImageTest.dwp DppImageTest.dpp DppImageTest.tcl DppTOC

	Note: this will generate the TCL layout script used by the gendpp utility.
	It will be placed in the gen subdirectory.

7. Generate the DPP:
	gendpp -b -j gen -s gen -d gen java2d DppImageTest.dwp gen\\DppImageTest.tcl

	Note: this will generate the Digital Playprint. It will also generate the TOC
	entry lookup class, DppTOC.java, in the gen subdirectory.

8. Build the title with the generated source.
