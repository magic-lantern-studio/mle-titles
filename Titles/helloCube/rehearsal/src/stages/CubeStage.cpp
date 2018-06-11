/** @defgroup HelloCubeTitle Magic Lantern Hellocube Title */

/**
 * @file CubeStage.cpp
 * @ingroup HelloCubeTitle
 *
 * @author Mark S. Millard
 * @date June 3, 2018
 *
 * This file implements the Inventor Stage for the HelloCube title.
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2017-2018 Wizzer Works
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
#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif /* WIN32 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#if defined(__linux__)
#include <X11/IntrinsicP.h>
#endif /* __linux__ */


// Include Inventor header files.
#if defined(__linux__)
//#include "mle/MleWalkViewer.h"
//#include "mle/MleExaminerViewer.h"
//#include "mle/MlePlaneViewer.h"
//#include "mle/MleFlyViewer.h"
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/Xt/viewers/SoXtPlaneViewer.h>
#include <Inventor/Xt/viewers/SoXtFlyViewer.h>
#endif /* __linux__ */
#if defined(WIN32)
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/Win/viewers/SoWinPlaneViewer.h>
#include <Inventor/Win/viewers/SoWinFlyViewer.h>
#endif /* WIN32 */

#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSelection.h>

// Include Magic Lantern Runtime Engine header files.
#include "mle/mlAssert.h"
#include "mle/mlMalloc.h"
#include "mle/MleDirector.h"
#include "mle/MleScheduler.h"
#include "mle/MleSet.h"

#if defined(__linux__)
#include "mle/mlPlatformData.h"
#endif /* __linux__ */
#if defined(WIN32)
#include "mle/mlPlatformData.h"
#include "mle/MleEventDispatcher.h"
#endif /* WIN32 */
#include "mle/MleStageFuncs.h"

// Include title header files.
#include "CubeStage.h"
#include "CubeSet.h"


MLE_STAGE_SOURCE(CubeStage,MleStage);


#if defined(__linux__)
static void _processXtEvents()
{
    // Get the application context for the stage.
    XtAppContext appContext = SoXt::getAppContext();

    while (XtAppPending(appContext))
    {
        XEvent event;
        SoXt::nextEvent(appContext, &event);
        Boolean dispatched = SoXt::dispatchEvent(&event);
    }
#if 0
    // Check for events and dispatch them if found.
    while ( XtAppPending(appContext) )
        XtAppProcessEvent(appContext,XtIMAll);
#endif /* 0 */
}
#endif /* __linux__ */


CubeStage::CubeStage(void)
{
#if defined(__linux__)
    // Initialize Inventor and Xt.
    Widget mainWindow = SoXt::init("Magic Lantern");
#endif /* __linux__ */
#if defined(WIN32)
    // Initializes SoWin library (and implicitly also the Coin
    // library). Returns a top-level / shell window to use.
    HWND mainWindow = (HWND)g_theTitle->m_platformData;
    if (mainWindow == NULL)
    {
        mainWindow = SoWin::init("Magic Lantern");
    } else
    {
        SoWin::init(mainWindow);
    }
#endif /* WIN32 */

    // Put the window offscreen if asked.
#if defined(__linux__)
    Widget parent = mainWindow;
#endif /* __linux__ */
#if defined(WIN32)
    HWND parent = mainWindow;
#endif /* WIN32 */

    // Not at rehearsal - no true iv viewer.
#if defined(__linux__)
    m_viewer = new SoXtRenderArea(parent);
#endif /* __linux__ */
#if defined(WIN32)
    m_viewer = new SoWinRenderArea(parent);
#endif /* WIN32 */
    m_viewer->setAutoRedraw(FALSE);

    // Configure viewer.
    m_viewer->setTitle("Magic Lantern - Inventor Stage");
    m_viewer->setSize(SbVec2s(640,480));
#if defined(__linux__)
    m_viewer->setEventCallback((SoXtRenderAreaEventCB *)eventHandler,this);
#endif /* __linux__ */
#if defined(WIN32)
    m_viewer->setEventCallback((SoWinRenderAreaEventCB *)eventHandler,this);
#endif /* WIN32 */
    m_viewer->show();

    // Create the root of the scene graph.
    m_root = new SoSelection;
    m_root->ref();

    // Set up selection.
    m_root->policy.setValue(SoSelection::SINGLE);

    // Attach set root.
    m_sets = new SoSeparator;
    m_root->addChild(m_sets);

    // Done setting up, so attach it to the viewer.
    m_viewer->setSceneGraph(m_root);

#if defined(__linux__)
    SoXt::show(mainWindow);
#endif /* __linux__ */
#if defined(WIN32)
    SoWin::show(mainWindow);
#endif /* WIN32 */

    // Initialize platform data.
    g_theTitle->m_platformData = initPlatform();

#if defined(__linux__)
    // Flush the Xt queue.
    _processXtEvents();
#endif /* __linux__ */
#if defined(WIN32)
    MSG msg;

    // Flush the message queue.
    while ( PeekMessage(&msg, mainWindow, 0, 0, PM_REMOVE) > 0 )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#endif /* WIN32 */

    // Schedule the rendering function.
    g_theTitle->m_theScheduler->insertFunc(
        PHASE_STAGE,(MleSchedulerFunc)update,this,this);
}

CubeStage::~CubeStage(void)
{
}

void CubeStage::init(void)
{
}

// initPlatform
//   Creates and initializes platform-specific data.
void*
CubeStage::initPlatform(void)
{
#if defined(__linux__)
    MleIvPlatformData *data = new MleIvPlatformData();
#endif /* __linux__ */
#if defined(WIN32)
    MleIvPlatformData *data = new MleIvPlatformData();
#endif /* WIN32 */

    // Provide users with the render area widget.
    data->m_widget = m_viewer->getOverlayWidget();
#if defined(WIN32)
    data->m_widget = m_viewer->getGLWidget();
#endif /* WIN32 */
    MLE_ASSERT(data->m_widget);

#if defined(__linux__)
    // Provide users with the application context.
    data->m_appContext = SoXt::getAppContext();
    MLE_ASSERT(data->appContext);
#endif /* __linux__ */

    // Focus management.
    data->m_focusEventHandlerRefCount = 0;

    // Device management.
    data->setKeyboardManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);
    data->setMouseManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);
    data->setJoystickManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);

    return((void *) data);
}

// This adds a set to the stage.
MleSchedulerItem *
CubeStage::addSet(void (*render)(MleSet *),MleSet *set)
{
    MLE_ASSERT(set);

    CubeStage::SetInfo *finfo = new CubeStage::SetInfo;

    if (set->isa("CubeSet")) {
        m_sets->addChild(CubeSet::cast(set)->getRoot());

        finfo->func = NULL;
        finfo->set = set;
    } else
    {
    	// Assume any other kind of set would use the SoCallback mechanism.

        // Create a new callback node.
        SoCallback *callback = new SoCallback;
        m_sets->addChild(callback);

        finfo->func = render;
        finfo->set = set;

        // Set the callback.
        callback->setCallback(setCB,finfo);
    }

    return NULL;
}

// This is the set callback.
//   This function is called from the SoCallback node that corresponds
//   to a set.  In the Inventor stage, only 2D sets are represented by
//   SoCallback node.  Inventor is given control of rendering, and 2D set
//   rendering is invoked through this callback.
void
CubeStage::setCB(void *data,SoAction *action)
{
    // Cast the data to the set info.
    CubeStage::SetInfo *finfo = (CubeStage::SetInfo *)data;

    if ( action->isOfType(SoGLRenderAction::getClassTypeId()) )
    {
        // Have the set do rendering by invoking the callback.
        (*finfo->func)(finfo->set);
    }
}

#if defined(__linux__)
// This function is the Inventor event handler.  It is Installed on the
//   render area to pick up X events before the render area processes them.
//   It should return TRUE if the event is not to be passed on to the
//   render area.
int
CubeStage::eventHandler(CubeStage *stage,XAnyEvent *event)
{
    // Can deliver events to the player here.
    return FALSE;

    // Don't pass this event to the viewer.
    //return TRUE;
}
#endif /* __linux__ */

#if defined(WIN32)
// This function is the Inventor event handler.  It is Installed on the
//   render area to pick up Windows messages before the render area processes them.
//   It should return TRUE if the event is not to be passed on to the
//   render area.
int
CubeStage::eventHandler(CubeStage *stage,MSG *msg)
{
    // Can deliver events to the player here.
    Win32CallData data;
    MleEvent event = msg->message;
    int status;
  
    data.hwnd = msg->hwnd;
    data.uMsg = msg->message;
    data.wParam = msg->wParam;
    data.lParam = msg->lParam;
    status = g_theTitle->m_theEventMgr->dispatchEvent(event,(void *) &data);

    // Don't pass this event to the viewer.
    return TRUE;
}
#endif /* WIN32 */

void
CubeStage::update(CubeStage * stage)
{
    // Draw the scene graph.
    stage->m_viewer->render();

#if defined(__linux__)
    _processXtEvents();
#endif /* __linux__ */
#if defined(WIN32)
    MSG msg;
    HWND window = SoWin::getTopLevelWidget();

    // Flush the message queue.
    while ( PeekMessage(&msg, window, 0, 0, PM_REMOVE) > 0 )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#endif /* WIN32 */
}

void
CubeStage:: getProperty(MleObject *object, const char *name, unsigned char **value)
{
    //cout << "Getting CubeStage property " << name << "." << endl;
    if (strcmp("size",name) == 0)
    {
        MlVector2 property = ((CubeStage *)object)->getSizeProperty();
        *((MlVector2 *)value) = property;
    } else
    {
        // TBD: log warning.
        //cout << "***** ERROR: Unknown CubeStage property: " << name << endl;
    }
}

void
CubeStage::setProperty(MleObject *object, const char *name, unsigned char *value)
{
    //cout << "Setting CubeStage property " << name << "." << endl;
    if (strcmp("size",name) == 0)
    {
        ((CubeStage *)object)->setSizeProperty(*((MlVector2 *)value));
    } else {
        // TBD: log warning.
        //cout << "***** ERROR: Unknown CubeStage property: " << name << endl;
    }
}
