/** @defgroup HelloCubeTitle Magic Lantern HelloCube Title */

/**
 * @file CubeRole.h
 * @ingroup HelloCubeTitle
 *
 * This file defines the CubeRole for the HelloCube title.
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
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"

// Include HelloCube header files.
#include "CubeRole.h"

using namespace std;

MLE_ROLE_SOURCE(CubeRole, MleRole)

CubeRole::CubeRole(MleActor *actor)
  : MleRole(actor)
{
    // Note: this can not be done during role initialization since the Mle3dSet is
    // expecting the m_root to already exist when it is attached to the set (before
    // init() is called.).
    m_cube = new SoCube();
    // Set default cube size.
    cubeGeometry(1.0, 1.0, 1.0);

    m_translation = new SoTranslation();
    // Default location is (0, 0, 0).

    m_material = new SoMaterial();
    // Set default cube color - red.
    cubeColor(1.0, 0.0, 0.0);

    m_root = new SoSeparator();
    m_root->ref();

    //m_root->addChild(m_translation);
    m_root->addChild(m_material);
    m_root->addChild(m_cube);
}

CubeRole::~CubeRole()
{
	// SoCube::~SoCube() is protected. Therefore we can't delete it from here.
	// delete m_cube;
    m_root->unref();
}

void
CubeRole::init()
{
    // Note: init() is called after the bound actor has been initialized.
    // This occurs after the role has been attached to the set.

    // Add role to its set. This is required by unittest, but is not normally
    // done with a Digital Workprint based titled.
    //m_set->attach(NULL,this);
}

void
CubeRole::cubePosition(const MlVector3 &pos)
{
    if (m_translation == NULL) return;
    // TBD - throw error (role not initialized).

	m_position = pos;

    SoSFVec3f translation;
    translation.setValue(pos[0], pos[1], pos[2]);
    m_translation->translation = translation;
}

void
CubeRole::cubeGeometry(const float width, const float height, const float depth)
{
    if (m_cube == NULL) return;
    // TBD - throw error (role not initialized).

     m_width  = width;  // Size in x dimension.
     m_height = height; // Size in y dimension.
     m_depth  = depth;  // Size in z dimension.

     SoSFFloat ivWidth;
     ivWidth.setValue(m_width);
     SoSFFloat ivHeight;
     ivHeight.setValue(m_height);
     SoSFFloat ivDepth;
     ivDepth.setValue(m_depth);
     m_cube->width  = ivWidth;
     m_cube->height = ivHeight;
     m_cube->depth  = ivDepth;
}

void
CubeRole::cubeColor(const float red, const float green, const float blue)
{
    if (m_material == NULL) return;
    // TBD - throw error (role not initialized).

	m_red   = red;
	m_green = green;
	m_blue  = blue;

    m_material->diffuseColor.setValue(m_red, m_green, m_blue);
}

void
CubeRole::draw(void */*data*/)
{
    // Nothing to draw since rendering will be handled by the Inventor
    // scene graph. In fact, this routine is never called by the
    // CubeSet since it is not needed.
}
