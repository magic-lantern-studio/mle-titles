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

// Include Inventor header files.
#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTransformSeparator.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/sensors/SoFieldSensor.h>

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"

// Include HelloCube header files.
#include "CubeSet.h"
#include "CubeRole.h"
#include "CubeStage.h"

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

	// Create the Set root.
	m_root = new SoSeparator;
	m_root->ref();

	// Create the Set camera.
	//   There are two possible cameras, one orthographic and one
	//   perspective
	m_cameraSwitch = new SoSwitch;
	m_root->addChild(m_cameraSwitch);

	// Create the perspective camera.
	SoPerspectiveCamera *perspectiveCamera = new SoPerspectiveCamera;
	m_cameraSwitch->addChild(perspectiveCamera);
	perspectiveCamera->position.setValue(0,0,3);

	// Create the orthographic camera.
	SoOrthographicCamera *orthographicCamera = new SoOrthographicCamera;
	m_cameraSwitch->addChild(orthographicCamera);
	orthographicCamera->position.setValue(0,0,3);

	// Use the perspective camera by default.
	m_cameraSwitch->whichChild.setValue(0);

	// XXX temporary

#ifdef MLE_DIGITAL_WORKPRINT
	// Create a headlight.
	SoTransformSeparator *lightSep = new SoTransformSeparator;
	m_root->addChild(lightSep);
	m_lightRot = new SoRotation;
	SoLight *light = new SoDirectionalLight;
	lightSep->addChild(m_lightRot);
	lightSep->addChild(light);
	m_lightRot->rotation.setValue(getCamera()->orientation.getValue());

	// Add a sensor on camera so headlight points same dir as camera.
	SoFieldSensor *sensor =
	    new SoFieldSensor((SoSensorCB *) cameraCB, this);
	sensor->attach(&getCamera()->orientation);
	sensor->setPriority(0);
#endif

	// Attach the Set scene graph to the stage
	//   This is a stage-specific protocol, not a base class feature
	CubeStage *stage = CubeStage::cast(MleStage::g_theStage);
	stage->addSet(NULL, this);
}

CubeSet::~CubeSet(void)
{
    // Do nothing extra.
}

void
CubeSet::init()
{
}

void
CubeSet::attach(MleRole *p, MleRole *c)
{
	// Make sure we really have a child.
	MLE_ASSERT(c);

	// Cast pointers to Inventor roles.
	CubeRole *parent = p ? CubeRole::cast(p) : NULL;
	CubeRole *child  = CubeRole::cast(c);

	// See if we are attaching to another role or to the set.
	if ( parent )
	{
		// It's a role.
		parent->addChild(child);
#if defined(MLE_REHEARSAL)
		child->setIvParent(parent->getRoot());
#endif /* MLE_REHEARSAL */
	}
	else
	{
		// It's the set.
		m_root->addChild(child->getRoot());
#if defined(MLE_REHEARSAL)
		child->setIvParent(m_root);
#endif /* MLE_REHEARSAL */
	}
}

SoCamera *
CubeSet::getCamera(void) const
{
	return (SoCamera *)m_cameraSwitch->getChild(
		m_cameraSwitch->whichChild.getValue());
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

#ifdef MLE_DIGITAL_WORKPRINT
// Camera rotation sensor callback.
void
CubeSet::cameraCB(CubeSet *set, SoFieldSensor *)
{
    set->m_lightRot->rotation.setValue(
	set->getCamera()->orientation.getValue());
}
#endif /* MLE_DIGITAL_WORKPRINT */
