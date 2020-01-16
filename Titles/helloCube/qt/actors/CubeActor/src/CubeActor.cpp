/** @defgroup HelloCubeTitle Magic Lantern HelloCube Title */

/**
 * @file CubeActor.cpp
 * @ingroup CubeTitle
 *
 * This file implements the CubeActor for the HelloCube title.
 *
 * @author Mark S. Millard
 * @date January 14, 2020
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2020 Wizzer Works
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  For information concerning this header file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

// Include system header files.
#include <iostream>

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"

// Include HelloCube header files.
#include "CubeActor.h"
#include "CubeRole.h"

using namespace std;

MLE_ACTOR_SOURCE(CubeActor, MleActor)

CubeActor::CubeActor(void)
 : MleActor()
{
    // Set default property values.
    // The initial position is set to the origin, (0, 0, 0).
    position.setValue(ML_SCALAR(0), ML_SCALAR(0), ML_SCALAR(0));

    // The initial geometry is a unit cube.
    MleArray<float> _geometry(3);
    _geometry[0] = 1.0; // Size in x dimension.
    _geometry[1] = 1.0; // Size in y dimension.
    _geometry[2] = 1.0; // Size in z dimension.
    setGeometryProperty(_geometry);

    // The inital color of the cube is green.
    MleArray<float> _color(3);
    _color[0] = 0.0;  // Red component.
    _color[1] = 1.0;  // Green component.
    _color[2] = 0.0;  // Blue component.
    setColorProperty(_color);
}

CubeActor::~CubeActor(void)
{
	// Do nothing extra.
}

void
CubeActor::init()
{
    //CubeRole *role = CubeRole::cast(getRole());
    CubeRole *role = (CubeRole *)getRole();

    // Push initial data retreived from the workprint into the role.
    role->cubePosition(position);
    role->cubeGeometry(geometry[0], geometry[1], geometry[2]);
    role->cubeColor(color[0], color[1], color[2]);
}

void
CubeActor::setPosition(MlVector3 &pos)
{
    //CubeRole *role = CubeRole::cast(getRole());
    CubeRole *role = (CubeRole *)getRole();

    // Update position property ...
    position.setValue(pos.getValue());
    // ... and push the update to the role.
    role->cubePosition(position);
}

void
CubeActor::setGeometry(MleArray<float> &vertices)
{
    //CubeRole *role = CubeRole::cast(getRole());
    CubeRole *role = (CubeRole *)getRole();

    // Update geometry property ...
    geometry = vertices;
    // ... and push the update to the role.
    role->cubeGeometry(geometry[0], geometry[1], geometry[2]);
}

void
CubeActor::setColor(MleArray<float> &rgb)
{
    CubeRole *role = CubeRole::cast(getRole());

    // Update color property ...
    color = rgb;
    // ... and push the update to the role.
    role->cubeColor(color[0], color[1], color[2]);
}

void
CubeActor:: getProperty(MleObject *object, const char *name, unsigned char **value)
{
    cout << "Getting CubeActor property " << name << "." << endl;
    if (strcmp("color",name) == 0)
    {
        const MleArray<float> *color;
        color = ((CubeActor *)object)->getColorProperty();
        *((MleArray<float> *)value) = *color;
    } else if (strcmp("geometry",name) == 0)
    {
        const MleArray<float> *dimensions;
        dimensions = ((CubeActor *)object)->getGeometryProperty();
        *((MleArray<float> *)value) = *dimensions;
    } else if (strcmp("position",name) == 0)
    {
        MlVector3 position = ((CubeActor *)object)->getPositionProperty();
        *((MlVector3 *)value) = position;
    } else
    {
        // TBD: log warning.
        cout << "***** ERROR: Unknown CubeActor property: " << name << endl;
    }
}

void
CubeActor::setProperty(MleObject *object, const char *name, unsigned char *value)
{
    cout << "Setting CubeActor property " << name << "." << endl;
    if (strcmp("color",name) == 0)
    {
        ((CubeActor *)object)->setColorProperty(*((MleArray<float> *)value));
    } else if (strcmp("geometry",name) == 0)
    {
        ((CubeActor *)object)->setGeometryProperty(*((MleArray<float> *)value));
    } else if (strcmp("position",name) == 0)
    {
        ((CubeActor *)object)->setPositionProperty(*((MlVector3 *)value));
    } else {
        // TBD: log warning.
        cout << "***** ERROR: Unknown CubeActor property: " << name << endl;
    }
}
