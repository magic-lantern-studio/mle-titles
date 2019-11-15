/** @defgroup HelloCubeTitle Magic Lantern HelloCube Title */

/**
 * @file CubeActor.cpp
 * @ingroup CubeTitle
 *
 * This file implements the CubeSet for the HelloCube title.
 *
 * @author Mark S. Millard
 * @date May 15, 2018
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2018-2020 Wizzer Works
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
#include "CubeSet.h"

using namespace std;

MLE_SET_SOURCE(CubeSet, MleSet)

#ifdef MLE_DIGITAL_WORKPRINT
void
CubeSet::initClass(void)
{
    mleRegisterSetClass(CubeSet, MleSet);

    mleRegisterSetMember(CubeSet, position, MlVector2);

    // Mark all the properties that belongs to the "transform" property
    // data set.
    //mleRegisterSetMemberDataset(CubeSet, position, MLE_PROP_DATASET_TRANSFORM);
}
#endif /* MLE_DIGITAL_WORKPRINT */

CubeSet::CubeSet(void)
 : MleSet()
{
    // Set default property values.
    // The initial position is set to the origin, (0, 0).
    position.setValue(ML_SCALAR(0), ML_SCALAR(0));
}

CubeSet::~CubeSet(void)
{
    // Do nothing extra.
}

void
CubeSet::init()
{
}

#ifdef MLE_DIGITAL_WORKPRINT
void
CubeSet::resolveEdit(const char *property)
{
#if 0
    if (! property || strcmp(property, "position") == 0)
      // TBD - nothing to do yet.
#endif
}
#endif /* MLE_DIGITAL_WORKPRINT */

void
CubeSet::setPosition(MlVector2 &pos)
{
    // Update position property.
    position.setValue(pos.getValue());
}

void
CubeSet:: getProperty(MleObject *object, const char *name, unsigned char **value)
{
    cout << "Getting CubeSet property " << name << "." << endl;
    if (strcmp("position",name) == 0)
    {
        MlVector2 position = ((CubeSet *)object)->getPositionProperty();
        *((MlVector2 *)value) = position;
    } else
    {
        // TBD: log warning.
        cout << "***** ERROR: Unknown CubeSet property: " << name << endl;
    }
}

void
CubeSet::setProperty(MleObject *object, const char *name, unsigned char *value)
{
    cout << "Setting CubeSet property " << name << "." << endl;
    if (strcmp("position",name) == 0)
    {
        ((CubeSet *)object)->setPositionProperty(*((MlVector2 *)value));
    } else {
        // TBD: log warning.
        cout << "***** ERROR: Unknown CubeSet property: " << name << endl;
    }
}
