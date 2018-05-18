/** @defgroup HelloCubeTitle Magic Lantern HelloCube Title */

/**
 * @file CubeActor.h
 * @ingroup HelloCubeTitle
 *
 * This file defines the CubeActor for the HelloCube title.
 *
 * @author Mark S. Millard
 * @date May 15, 2018
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2018 Wizzer Works
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

#ifndef __CUBEACTOR_H_
#define __CUBEACTOR_H_

// Include Magic Lantern header files.
#include "mle/mlTypes.h"
#include "mle/mlMalloc.h"
#include "math/vector.h"
#include "mle/mlArray.h"
#include "mle/MleActor.h"

// Include Title header files.
#include "ShapeActor.h"

class SHAPEACTOR_API CubeActor : public MleActor
{
    MLE_ACTOR_HEADER(CubeActor);

  public:

    static void getProperty(MleObject *object, const char *name, unsigned char **value);
    static void setProperty(MleObject *object, const char *name, unsigned char *value);

    // Property declarations.
    // <b>position</b> property contains x and y positions relative to
    // the corresponding set's coordinate system.  (0, 0) corresponds
    // to the lower left corner (origin of the corresponding set).
    MLE_ACTOR_PROPERTY(MlVector3, position, getPositionProperty, setPositionProperty)
    // <b>geometry</b> property is the cube's vertices.
    MLE_ACTOR_ARRAY_PROPERTY(float, geometry, getGeometryProperty, setGeometryProperty)

    // Construct a label widget actor.
    CubeActor(void);

    // Destruct a label widget actor.
    virtual ~CubeActor(void);

    // Initialize the actor and push initial property values to the role.
    virtual void init(void);

#ifdef MLE_REHEARSAL
    // Tools can change property values directly in actor memory.  This
    // function can be used to propagate the changes to its role
    // to make its states consistent.
    virtual void resolveEdit(const char *property);
#endif  /* MLE_REHEARSAL */

    // Set the current position.
    virtual void setPosition(MlVector3 &pos);

    // Set the cube geometry.
    virtual void setGeometry(MleArray<float> &dimensions);
};

#endif /* __CUBEACTOR_H_ */
