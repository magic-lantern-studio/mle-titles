This file describes the steps for mastering the HelloWolrd Test title for the
Magic Lantern Java Runtime Engine. Keep in mind that Java uses a Big Endian
file format; therefore, we specify the "-b" option when appropriate.

To master the DPP Image Test title, use the following steps.

1. Change working directory to:
    cd $MLE_HOME/Titles/helloWorld/java/HelloWorld/src
    mkdir gen

2. Generate the Actor Group chunks:
    gengroup -b -j gen -d gen java2d ../workprints/HelloWorld.dwp ActorID.java GroupID.java

    Note: this will generate the Group and Set chunks in the gen subdirectory.
    The ActorID.java and GroupID.java classes will also be generated in the gen
    subdirectory, belonging to the "gen" package.

3. Generate the Scene chunks:
    genscene -b -j gen -d gen java2d ../workprints/HelloWorld.dwp SceneID.java

    Note: this will generate the Scene chunks in the gen subdirectory.
    The SceneID.java class will also be generated in the gen subdirectory,
    belonging to the "gen" package.

4. Generate the MediaRef chunks:
    genmedia -b -d gen java2d ../workprints/HelloWorld.dwp HelloWorld.BOM

    Note: this will generate the MediaRef chunks in the gen subdirectory.
    A bill-of-materials, HelloWorld.BOM, will also be generated in the gen
    subdirectory.

5. Generate the Runtime tables:
    gentables -j gen -d gen java2d ../workprints/HelloWorld.dwp

    Note: this will generate the MleRuntimeTables.java class that describes
    the tables for constructing the title. It will be placed in the gen
    subdirectory.

6. Generate the DPP layout TCL script:
    genppscript -d gen java2d ../workrints/HelloWorld.dwp HelloWorld.dpp HelloWorld.tcl DppTOC

    Note: this will generate the TCL layout script used by the gendpp utility.
    It will be placed in the gen subdirectory.

7. Generate the DPP:
    gendpp -b -j gen -s gen -d gen java2d ../workprints/HelloWorld.dwp gen/HelloWorld.tcl

    Note: this will generate the Digital Playprint. It will also generate the
    TOC entry lookup class, DppTOC.java, in the gen subdirectory.

8. Build the title with the generated source.
