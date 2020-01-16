/** @defgroup HellocubeTitle Magic Lantern HelloCube Title */

/**
 * @file CubeStage.h
 * @ingroup HelloCubeTitle
 *
 * @author Mark S. Millard
 * @date January 13, 2020
 *
 * This file defines the Inventor Stage for the HelloCube title.
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

#ifndef __CUBESTAGE_H_
#define __CUBESTAGE_H_

// Include Qt header files.
#include <QString>

// Include Inventor header files.
#include <Inventor/SbLinear.h>
#if defined(__linux__)
#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/Qt/viewers/SoQtFullViewer.h>
#endif

// Include Magic Lantern header files.
#include "mle/mlTypes.h"
#include "mle/MleStage.h"
#include "mle/MleScheduler.h"
#include "mle/MleEventDispatcher.h"

#include "math/vector.h"

// Include title header files.
#include "CubeStage_global.h"

class SoSelection;
class SoSeparator;
class SoAction;
//class SoCamera;

class MleSet;
class MleSchederItem;


class CUBESTAGESHARED_EXPORT CubeStage : public MleStage
{
    MLE_STAGE_HEADER(CubeStage);

  public:

    static void getProperty(MleObject *object, const char *name, unsigned char **value);
    static void setProperty(MleObject *object, const char *name, unsigned char *value);

    // Property declarations.
    MLE_STAGE_PROPERTY(MlVector2,size,getSizeProperty,setSizeProperty)

    // Constructor and destructor.
    CubeStage(void);
    virtual ~CubeStage(void);
    
    // Initialize the stage.
    void init(void);

    // Stage-specific API.
    //   This is new API (not inherited) for this particular stage type.

    // addSet() registers a new set with this stage.
    virtual MleSchedulerItem *addSet(void (*render)(MleSet *),MleSet *set);

    // Called by a set when it's camera moves.
    //void setCameraMoved(MleSet *set, SoCamera *cam);

    // Initializes platform-specific data for this stage.
    // Returns pointer to the initialized platform-specific data structure.
    void *initPlatform(void);

    // Set the name of the stage.
    void setName(const QString &name);

    // Make the stage visible.
    void show(void);

    // Exit the stage.
    static void exit(QEvent *event);

    // This callback is used to capture the close message. It is called
    // via the event dispatch manager.
    static int closeEventCB(MleEvent event,void *callData,void *clientData);

    // Flag indicating that the stage will exit.
    static MlBoolean g_doExit;

  protected:

    // Our viewer is just a render area.
#if defined(__linux__)
    SoQtRenderArea *m_viewer;
#endif /* __linux__ */

    // Root of the scene graph.
    SoSelection *m_root;
    SoSeparator *m_sets;

    // This is a local struct definition to bundle information for the
    //   Inventor callback node.  It contains information about the
    //   set, so the set rendering function can be called during
    //   Inventor scene graph traversal.  In this Inventor stage, only
    //   2D set is added as Inventor callback node.
    typedef struct _SetInfo {
        void (*func)(MleSet *);
        MleSet *set;
    } SetInfo;

    // Update() is the function the stage registers with the scheduler.
    static void update(CubeStage *stage);

    // setCB() is the callback for the Inventor callback node
    //   used to invoke a set.  Only the 2D set uses this in
    //   this stage.
    static void setCB(void *data,SoAction *action);

    // eventHandler() is the callback for Inventor event handling.
#if defined(__linux__)
    static SbBool eventHandler(CubeStage *stage,QEvent *event);
#endif /* __linux__ */
};

#endif /* __CUBESTAGE_H_ */
