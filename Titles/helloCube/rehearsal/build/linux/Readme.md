HelloCube Magic Lantern Title
==============================

The HelloCube title is an example on how to write a Magic Lantern title using components provided by the Magic Lantern SDK. The application will display a green cube in a window displayed on the target platform.

## Target Platforms

HelloCube is an application that targets the inventor platform. It is an Open Inventor application leveraging the Open Inventor components provided by the Magic Lantern SDK.

Currently, only the Linux operating system is supported and has only been tested on Ubuntu 16.04 LTS 64-bit OS.

## Dependencies

The HelloCube title has the following dependencies:

* Digital Workprint - the HelloCube title requires the HelloCube.dwp located in the _workprints_ directory.
* CubeActor - the Actor defining the parameters of the cube
* CubeRole - the Role used to render the cube in the inventor platform
* CubeSet - the Set used to encapsulate the roles being performed on stage
* CubeStage - the Stage for the inventor target platform

## Build Instructions

TBD - To buid the HelloCube title, do the following:

## Execution Instructions

To run or execute the HelloCube title, do the following:

````
$ cd $MLE_HOME/Titles/helloCube/rehearsal
$ helloCube workprints/HelloCube.dwp
````

Release Notes
=============

TBD
