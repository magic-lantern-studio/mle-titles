/** @defgroup HelloCubeTitle Magic Lantern HelloCube Title */

/**
 * @file CubeSet.h
 * @ingroup HelloCubeTitle
 *
 * This file defines the CubeSet for the HelloCube title.
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

#ifndef __CUBESET_H_
#define __CUBESET_H_

// Include Inventor header files.
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/sensors/SoFieldSensor.h>

// Include Magic Lantern header files.
#include "mle/mlTypes.h"
#include "mle/mlMalloc.h"
#include "math/vector.h"
#include "mle/MleSet.h"

// Include Title header files.
#include "CubeSet_global.h"

class CUBESETSHARED_EXPORT CubeSet : public MleSet
{
    MLE_SET_HEADER(CubeSet);

  public:

    static void getProperty(MleObject *object, const char *name, unsigned char **value);
    static void setProperty(MleObject *object, const char *name, unsigned char *value);

    // Property declarations.
    // <b>position</b> property contains x and y positions relative to
    // the corresponding stage's coordinate system.  (0, 0) corresponds
    // to the lower left corner (origin of the corresponding set).
    MLE_SET_PROPERTY(MlVector2, position, getPositionProperty, setPositionProperty)

    // Construct a label widget actor.
    CubeSet(void);

    // Destruct a label widget actor.
    virtual ~CubeSet(void);

    // Initialize the set.
    virtual void init(void);

    // Attach the child role to the set.
    void attach(MleRole *parent, MleRole *child);

    // Set the current position.
    virtual void setPosition(MlVector2 &pos);

    // Get the Inventor scene graph for the set.
    SoSeparator *getRoot(void)
    { return m_root; }

    // Get the Inventor camera for the Set.
    SoPerspectiveCamera *getCamera()
    { return m_camera; }

    // A callback used for light rotation sensor.
    static void cameraCB(CubeSet *set, SoFieldSensor *);

  protected:

    // The root of the Inventor scene graph for the set.
    SoSeparator *m_root;

  private:

    // The set's camera.
    SoPerspectiveCamera *m_camera;
    // The set's light transform (for camera's directional light).
    SoRotation *m_lightRot;
};

#endif /* __CUBESET_H_ */
