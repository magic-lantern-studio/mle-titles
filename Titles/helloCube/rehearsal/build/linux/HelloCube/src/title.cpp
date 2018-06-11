/** @defgroup HelloCubeTitle Magic Lantern HelloCube Title */

/**
 * @file title.cpp
 * @ingroup HelloCubeTitle
 *
 * @author Mark S. Millard
 * @date June 7, 2018
 *
 * This file implements the HelloCube title.
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

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"
#include "mle/mlFileio.h"
#include "mle/mlAssert.h"
#include "mle/mlTypes.h"

// Include Magic Lantern Runtime Engine header files.
#include "mle/MleLoad.h"
#include "mle/MleDirector.h"
#include "mle/MleScheduler.h"
#include "mle/MleEventDispatcher.h"
#include "mle/mlPlatformData.h"

#include "mle/Dwp.h"
#include "mle/DwpItem.h"

// Include HelloCube title header files.
#include "CubeStage.h"

// External declarations.
extern void mleDwpInit();

// Forward declarations.
static MleIvPlatformData *initPlatform(void);
static MleEventDispatcher *initEventMgr(MleEventEntry *eventTable,int numEvents);


// Global handle for Digital Workprint.
static MleDwpItem *g_workprint;


// Initialize the HelloCube title environment.
MlBoolean initEnv(int argc, void **argv)
{
	MleEventEntry *eventTable;
	long numEvents;
	void *(*initTitle)(void);
	char *workprint;

	// Parse arguments.
	if (argc != 4) {
		return ML_FALSE;
	} else {
		eventTable = (MleEventEntry *)argv[0];
		numEvents = (long) argv[1];
		workprint = (char *)argv[2];
        initTitle = (void *(*)(void))argv[3];
	}

	// Initialize the platform data.
	g_theTitle->m_platformData = initPlatform();

	// Initialize the quit flag.
	g_theTitle->m_quit = FALSE;

	// Load the Digital Workprint.
	mleDwpInit();
	g_workprint = mlLoadWorkprint(workprint);

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

    // Initialize stage.
    new CubeStage();
    ((CubeStage *)MleStage::g_theStage)->init();

    // Load the first group.
    (void) mlLoadBootScene(g_workprint);

    return ML_TRUE;
}


// Main loop of execution.
int mainLoop(void)
{
    return 0;
}


// Clean up HelloCube title environment.
MlBoolean cleanupEnv(void)
{
    MLE_ASSERT(g_theTitle->m_theScheduler = NULL);
    MLE_ASSERT(g_theTitle->m_theEventMgr = NULL);
    MLE_ASSERT(g_theTitle->m_platformData = NULL);

    // Close Digital Workprint - XXX: unload functionality is not yet available.
    //mlUnloadWorkprint(g_workprint);

    // Cleanup Magic Lantern Runtime Engine and title components.
    delete g_theTitle->m_theScheduler;
    delete g_theTitle->m_theEventMgr;
    delete (MleIvPlatformData *)g_theTitle->m_platformData;
    //if (g_theTitle->m_titleData)
    //    delete g_theTitle->m_titleData;
    //mlFree(g_theTitle);

    return ML_TRUE;
}


// Initialize the Inventor platform.
MleIvPlatformData *initPlatform(void)
{
    MleIvPlatformData *ivPlatformData;

    // Create platform specific data for Inventor platform.
    ivPlatformData = new MleIvPlatformData();

    // Initialize input manager flags.
    ivPlatformData->setKeyboardManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);
    ivPlatformData->setMouseManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);
    ivPlatformData->setJoystickManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);

    // XXX: extract window size from properties
    //ivPlatformData->m_defaultWidth = DEFAULT_VIEW_WIDTH;
    //ivPlatformData->m_defaultHeight = DEFAULT_VIEW_HEIGHT;

    return ivPlatformData;
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
