# HelloCube Magic Lantern Title

The HelloCube title is an application that displays a green cube.
It is a standalone application in that it does not use the default
Magic Lantern SDK parts; such as the MleIvStage, Mle3dSet, Mle3dRole,
etc. Instead, the title provides an example how to write an application
from scratch, targeting an Open Inventor platform and reading the
title contents from a Magic Lantern Digital Workprint.

The HelloCube includes the following part implementations:
* CubeStage - an Open Inventor stage
* CubeSet - a 3D set managing the Open Inventor scene graph
* CubeRole - a 3D role used to render the Opne Inventor cube
* CubeActor - a actor defining the cube's behavior
