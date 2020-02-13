/** @defgroup HelloCubeTitle Magic Lantern HelloCube Title */

/**
 * @file CubeRole.h
 * @ingroup HelloCubeTitle
 *
 * This file defines the CubeRole for the HelloCube title.
 *
 * @author Mark S. Millard
 * @date May 14, 2018
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

#ifndef __CUBEROLE_H_
#define __CUBEROLE_H_

// Include Inventor header files.
#ifdef MLE_DIGITAL_WORKPRINT
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoMaterial.h>
#endif /* MLE_DIGITAL_WORKPRINT */

// Include Magic Lantern header files.
#include "mle/mlTypes.h"
#include "math/vector.h"
//#include "mle/MleIv3dRole.h"
#include "mle/MleRole.h"

// Include Title header files.
#include "ShapeRole.h"

// Declare external classes.
class MleActor;

class SHAPEROLE_API CubeRole : public MleRole
{
    MLE_ROLE_HEADER(CubeRole);

  public:

    // Construct a cube role.
    CubeRole(MleActor *actor);

    // Destruct a cube role.
    virtual ~CubeRole(void);

    // Initialize the cube role.
    virtual void init(void);

    // Update the position where the cube is drawn.
    void cubePosition(const MlVector3 &pos);

    // Update the cube geometry to render.
    void cubeGeometry(const float width, const float height, const float depth);

    // Update the cube color.
    void cubeColor(const float red, const float green, const float blue);

    // The render() function of the 3D Set calls this function to update
    // this role every cycle.
    virtual void draw(void *data);

#ifdef MLE_DIGITAL_WORKPRINT
    SoSeparator *getRoot() { return m_root; }
#endif /* MLE_DIGITAL_WORKPRINT */

  protected:

    // Cube coordinate position.
    MlVector3 m_position;

    // Cube geometry parameters.
    float m_width;  // Size in x dimension.
    float m_height; // Size in y dimension.
    float m_depth;  // Size in z dimension.

    // Cube color parameters.
    float m_red;
    float m_green;
    float m_blue;

#ifdef MLE_DIGITAL_WORKPRINT
    SoSeparator *m_root;
    SoCube *m_cube;
    SoMaterial *m_material;
#endif /* MLE_DIGITAL_WORKPRINT */
};

#endif /* __CUBEROLE_H_ */
