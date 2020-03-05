/** @defgroup HelloCubeTitle Magic Lantern HelloCube Title */

/**
 * @file CubeSet.cpp
 * @ingroup HelloCubeTitle
 *
 * This file implements the CubeSet for the HelloCube title.
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

// Include Inventor header files.
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoTransformSeparator.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoLight.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/sensors/SoFieldSensor.h>

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"

// Include HelloCube header files.
#include "CubeStage.h"
#include "CubeSet.h"
#include "CubeRole.h"

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

    // Create the set root.
    m_root = new SoSeparator();
    m_root->ref();

    // Create a perspective camera.
    m_camera = new SoPerspectiveCamera;
    m_root->addChild(m_camera);
    m_camera->position.setValue(0,0,3);

    // Create a headlight.
    SoTransformSeparator *lightSep = new SoTransformSeparator;
    m_root->addChild(lightSep);
    m_lightRot = new SoRotation;
    SoLight *light = new SoDirectionalLight;
    lightSep->addChild(m_lightRot);
    lightSep->addChild(light);
    m_lightRot->rotation.setValue(m_camera->orientation.getValue());

    // Add a sensor on the camera so the headlight points in the same
    // direction as the camera.
    SoFieldSensor *sensor = new SoFieldSensor((SoSensorCB *) cameraCB, this);
    sensor->attach(&m_camera->orientation);
    sensor->setPriority(0);

    // Attach the Set scene graph to the stage
    //   This is a stage-specific protocol, not a base class feature
    CubeStage *stage = CubeStage::cast(MleStage::g_theStage);
    stage->addSet(NULL, this);
}

CubeSet::~CubeSet(void)
{
    if (m_root != NULL) {
        m_root->unref();
        m_root = NULL;
    }
}

void
CubeSet::init()
{
    // Expecting a CubeStage has already been instantiated.
    //CubeStage *stage = CubeStage::cast(MleStage::g_theStage);
    //stage->addSet(NULL, this);

    //MleSet::g_currentSet = this;
}

// Attach the child role to the set.
void
CubeSet::attach(MleRole * /*parent*/, MleRole *child)
{
    // Ignoring parent for this demonstration.

    // Expecting child to be a CubeRole.
    CubeRole *role = CubeRole::cast(child);
    m_root->addChild(role->getRoot());
}

void
CubeSet::setPosition(MlVector2 &pos)
{
    // Update position property.
    position.setValue(pos.getValue());
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

// Camera rotation sensor callback.
void
CubeSet::cameraCB(CubeSet *set, SoFieldSensor *)
{
    set->m_lightRot->rotation.setValue(
        set->m_camera->orientation.getValue());
}
