/** @defgroup HelloCubeTitle Magic Lantern Hellocube Title */

/**
 * @file CubeStage.cpp
 * @ingroup HelloCubeTitle
 *
 * @author Mark S. Millard
 * @date January 13, 2018
 *
 * This file implements the Inventor Stage for the HelloCube title.
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
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Include Qt header files
#include <QApplication>

// Include Inventor header files.
#if defined(__linux__)
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/Qt/viewers/SoQtPlaneViewer.h>
#include <Inventor/Qt/viewers/SoQtFlyViewer.h>
#endif /* __linux__ */

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
#include "mle/MleStageFuncs.h"

// Include title header files.
#include "CubeStage.h"
#include "CubeSet.h"

// Global declaration for Magic Lantern Qt events.
CUBESTAGESHARED_EXPORT MleEvent QT_RESIZE_EVENT = 0x0000;
CUBESTAGESHARED_EXPORT MleEvent QT_CLOSE_EVENT  = 0x0001;
CUBESTAGESHARED_EXPORT MleEvent QT_EXPOSE_EVENT = 0x0002;
CUBESTAGESHARED_EXPORT MleEvent QT_MOUSE_EVENT  = 0x0003;
CUBESTAGESHARED_EXPORT MleEvent QT_PAINT_EVENT  = 0x0004;

MLE_STAGE_SOURCE(CubeStage,MleStage);


#if defined(__linux__)
static void _processQtEvents()
{
    QCoreApplication *app = QApplication::instance();
    app->processEvents();
}
#endif /* __linux__ */

CubeStage::CubeStage(void)
{
#if defined(__linux__)
    // Initializes SoQt library (and implicitly also the Coin
    // library). Returns a top-level shell widget to use.
    QWidget *mainWindow = SoQt::init("Magic Lantern");
#endif /* __linux__ */

    // Put the window offscreen if asked.
#if defined(__linux__)
    QWidget *parent = mainWindow;
#endif /* __linux__ */

    // Not at rehearsal - no true iv viewer.
#if defined(__linux__)
    m_viewer = new SoQtRenderArea(parent);
#endif /* __linux__ */
    m_viewer->setAutoRedraw(FALSE);

    // Configure viewer.
    m_viewer->setTitle("Magic Lantern - Inventor Stage");
    m_viewer->setSize(SbVec2s(640,480));
#if defined(__linux__)
    m_viewer->setEventCallback((SoQtRenderAreaEventCB *)eventHandler,this);
#endif /* __linux__ */
    m_viewer->show();

    // Create the root of the scene graph.
    m_root = new SoSelection;
    m_root->ref();

    // Set up selection pick policy.
    m_root->policy.setValue(SoSelection::SINGLE);

    // Attach set root.
    m_sets = new SoSeparator;
    m_root->addChild(m_sets);

    // Done setting up, so attach it to the viewer.
    m_viewer->setSceneGraph(m_root);

#if defined(__linux__)
    SoQt::show(mainWindow);
#endif /* __linux__ */

    // Initialize platform data.
    g_theTitle->m_platformData = initPlatform();

#if defined(__linux__)
    // Flush the Qt queue.
    _processQtEvents();
#endif /* __linux__ */
}

CubeStage::~CubeStage(void)
{
    if (m_root != NULL) {
        m_root->unref();
        m_root = NULL;
    }
}

void CubeStage::init(void)
{
    // Declare local variables
    MleCallbackId cbId;

    // Insert close callback into event dispatch manager.
    MleEvent closeEvent = QT_CLOSE_EVENT;
    cbId = g_theTitle->m_theEventMgr->installEventCB(
        closeEvent, CubeStage::closeEventCB, (void *)this);

    // Schedule the rendering function.
    g_theTitle->m_theScheduler->insertFunc(
        PHASE_STAGE, (MleSchedulerFunc)update, this, this);
}

// initPlatform
//   Creates and initializes platform-specific data.
void*
CubeStage::initPlatform(void)
{
#if defined(__linux__)
    MleIvPlatformData *data = new MleIvPlatformData();
#endif /* __linux__ */

    // Provide users with the render area widget.
    data->m_widget = m_viewer->getOverlayWidget();
    MLE_ASSERT(data->m_widget);

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
// This function is the Inventor event handler.  It is installed on the
//   render area to pick up events before the render area processes them.
//   It should return TRUE if the event is not to be passed on to the
//   render area.
SbBool
CubeStage::eventHandler(CubeStage */*stage*/,QEvent *event)
{
    QEvent::Type type = event->type();
    if (type == QEvent::Hide) {
        CubeStage::exit(event);
    }

    // Can deliver events to the player here.
    return FALSE;

    // Don't pass this event to the viewer.
    //return TRUE;
}
#endif /* __linux__ */

void
CubeStage::update(CubeStage * stage)
{
    // Draw the scene graph.
    stage->m_viewer->render();

#if defined(__linux__)
    _processQtEvents();
#endif /* __linux__ */
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

void
CubeStage::setName(const QString &name)
{
    m_viewer->setTitle(name.toUtf8());
}

void
CubeStage::show()
{
    m_viewer->show();
}

void
CubeStage::exit(QEvent */*event*/)
{
    //qDebug() << "CubeStage: exit received Qt Close event.";
    // Dispatch Magic Lantern close event.
    g_theTitle->m_theEventMgr->dispatchEvent(QT_CLOSE_EVENT, NULL);
}

int
CubeStage::closeEventCB(MleEvent /*event*/,void */*callData*/,void */*clientData*/)
{
    // Declare local variables.
    //CubeStage *theStage = (CubeStage *)clientData;
    //QtCallData *eventData = (QtCallData *)callData;

    // Process the close event.
    CubeStage::g_doExit = ML_TRUE;

    return 0;
}

MlBoolean CubeStage::g_doExit = ML_FALSE;
