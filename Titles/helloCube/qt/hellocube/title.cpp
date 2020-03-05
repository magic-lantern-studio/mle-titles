/** @defgroup HelloCubeTitle Magic Lantern HelloCube Title */

/**
 * @file main.cpp
 * @ingroup HelloCubeTitle
 *
 * This file implements the main entry points into the HelloCube title.
 *
 * @author Mark S. Millard
 * @date June 18, 2018
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

// Include Qt header files.
#include <QApplication>
#include <QScreen>
#include <QTimer>

// Include Magic Lantern header files
#include "mle/mlTypes.h"
#include "mle/mlMalloc.h"
#include "mle/mlAssert.h"
#include "mle/mlErrno.h"

// Include Magic Lantern Runtime Engine header files.
#include "mle/MleDirector.h"
#include "mle/MleEventDispatcher.h"
#include "mle/MleScheduler.h"
#include "mle/MleLoad.h"

// Include Digital Workprint header files.
#include "mle/Dwp.h"
#include "mle/DwpItem.h"
#include "mle/DwpLoad.h"

// Platform data must match the Qt MLE Runtime Engine platform.
#include "mlPlatformData.h"

// Include Magic Lantern Qt Parts header files.

// Include title header files.
#include "mle/qt/CubeStage.h"

using namespace std;

// External declarations.
extern void mleDwpInit();

// Forward declarations.
static MleEventDispatcher *initEventMgr(MleEventEntry *eventTable,int numEvents);


// Global handle for Digital Workprint.
static MleDwpItem *g_workprint;


static MleQtPlatformData *
initPlatform()
{
    // Declare local variables.
    MleQtPlatformData* qtData;

    // Allocate a platform specific data structure.
    qtData = new MleQtPlatformData();

    // Initialize the platform specific data
    //    Load the playprint file name from a Qt resource.
    //LoadString(hInstance,IDS_PLAYPRINT,
    //     qtData->m_playprint,sizeof(qtData->m_playprint));

    // Initialize input manager flags.
    qtData->setKeyboardManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);
    qtData->setMouseManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);
    qtData->setJoystickManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);

    // Todo: extract window style from Set properties.
    //qtData->m_winStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
    //    WS_THICKFRAME | WS_MAXIMIZEBOX | WS_CLIPCHILDREN;

    // Todo: extract window size from Set properties
    qtData->m_defaultWinWidth = DEFAULT_VIEW_WIDTH;
    qtData->m_defaultWinHeight = DEFAULT_VIEW_HEIGHT;

    return qtData;
}


MlBoolean initEnv(int argc, void **argv)
{
    MleEventEntry *eventTable;
    int numEvents;
    void *(*initTitle)(void);
    char *workprint;

    // Parse arguments.
    if (argc != 4) {
        return ML_FALSE;
    } else {
        eventTable = (MleEventEntry *)argv[0];
        numEvents = *((int *)argv[1]);
        workprint = (char *)argv[2];
        initTitle = (void *(*)(void))argv[3];
    }

    // The title director should already be constructed.
    MLE_ASSERT(g_theTitle);

    // Initialize the platform data.
    g_theTitle->m_platformData = initPlatform();

    // Initialize the quit flag.
    g_theTitle->m_quit = FALSE;

    // Load the Digital Workprint.
    mleDwpInit();
    g_workprint = mlLoadWorkprint(workprint);
    if (g_workprint == NULL) {
        // Unable to load Digital Workprint.
        cout << "Unable to load Digital Workprint " << workprint << ".\n";
        return ML_FALSE;
    }

    // Initialize scheduler.
    g_theTitle->m_theScheduler = new MleScheduler;

    // Now set it up to know the standard Magic Lantern phases
    // for actors, roles, sets, and stages.  The user
    // can override this by inserting and deleting phases
    // at will.
    g_theTitle->m_theScheduler->init();

    // Initialize event dispatch manager.
    g_theTitle->m_theEventMgr = initEventMgr(eventTable, numEvents);

    // Setup stage and set; Note: must follow initPlatform().
    if (initTitle)
        g_theTitle->m_titleData = initTitle();
    else
        g_theTitle->m_titleData = NULL;

    // Create and initialize stage.
    CubeStage *theStage = new CubeStage();
    theStage->init();

    // Load the first group.
    (void) mlLoadBootScene(g_workprint);

    // Show the stage.
    theStage->setName("HelloCube Title");
    theStage->show();

    return ML_TRUE;
}


int mainLoop(const QApplication &app)
{
    int status = 0;

    while(! CubeStage::g_doExit) {
        // Execute the scheduled phases in order of insertion.
        g_theTitle->m_theScheduler->goAll();

        // Process pending Qt events.
        app.processEvents();

        //qDebug() << "null Title: mainloop iteration.";
    }

    return status;
}


MlBoolean cleanupEnv(void)
{
    MLE_ASSERT(g_theTitle->m_theScheduler != NULL);
    MLE_ASSERT(g_theTitle->m_theEventMgr != NULL);
    MLE_ASSERT(g_theTitle->m_platformData != NULL);

    // Close Digital Workprint - XXX: unload functionality is not yet available.
    //mlUnloadWorkprint(g_workprint);

    // Cleanup Magic Lantern Runtime Engine and title components.
    delete g_theTitle->m_theScheduler;
    delete g_theTitle->m_theEventMgr;
    delete (MleQtPlatformData *)g_theTitle->m_platformData;
    //if (g_theTitle->m_titleData)
    //    delete g_theTitle->m_titleData;
    //mlFree(g_theTitle);

    return ML_TRUE;
}


// Initialize Magic Lantern Dispatch Manager.
MleEventDispatcher *initEventMgr(MleEventEntry *eventTable, int numEvents)
{
    // Initialize dispatch manager
    // - dynamically allocate memory for events
    // - make room for 'numEvents' total events
    // - do not use queing; Windows already does this
    g_theTitle->m_theEventMgr = new MleEventDispatcher();

    // Install Magic Lantern event callbacks.
    g_theTitle->m_theEventMgr->installEventCB(eventTable, numEvents);

    return g_theTitle->m_theEventMgr;
}
