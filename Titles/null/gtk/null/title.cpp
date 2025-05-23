/** @defgroup NullTitle Magic Lantern null Title */

/**
 * @file title.cpp
 * @ingroup NullTitle
 *
 * This file implements the main entry points into the null title.
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2022-2025 Wizzer Works
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

// Include Gtk header files.

// Include Magic Lantern header files
#include <mle/mlTypes.h>
#include <mle/mlMalloc.h>
#include <mle/mlAssert.h>
#include <mle/mlErrno.h>

// Include Magic Lantern Runtime Engine header files.
#include <mle/MleDirector.h>
#include <mle/MleEventDispatcher.h>
#include <mle/MleScheduler.h>
#include <mle/MleLoad.h>
#include <mle/mlPlatformData.h>
#include <mle/ivstage.h>


// Include Digital Playprint header files.
#include <mle/ppinput.h>

// Include Open Inventor header files.
#include <Inventor/Gtk/SoGtk.h>

// Include title header files.


// Initialize Magic Lantern Dispatch Manager.
static MleEventDispatcher *initEventMgr(MleEventEntry *eventTable, int numEvents)
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


// Initialize title environment.
MlBoolean initEnv(int argc, void **argv)
{
    MleEventEntry *eventTable;
    int *numEvents;
    void *(*initTitle)(void);
    const char *playprint;

    // Parse arguments.
    if (argc != 4)
    {
        return(ML_FALSE);
    } else
    {
        eventTable = (MleEventEntry *)argv[0]; // A reference to a table of Magic Lantern events.
        numEvents = (int *)argv[1];            // The number of events in the table.
        playprint =  (const char *)argv[2];    // The file name of the Digital Playprint.
        initTitle = (void *(*)(void))argv[3];  // A callback function to initialize title specific data.
    }

    // The title director should already be constructed.
    MLE_ASSERT(g_theTitle);

    // Initialize the platform data.
    //g_theTitle->m_platformData = initPlatform();

    // Initialize quit flag.
    g_theTitle->m_quit =  FALSE;

    // Load the playprint.
    if (playprint != NULL)
        g_theTitle->m_dpp = mlLoadPlayprint(playprint, MLE_DPP_FINDPPLE);
    // Todo: need to do something if playprint not specified.

    // Initialize scheduler.
    g_theTitle->m_theScheduler = new MleScheduler();

    // Now set it up to know the standard Magic Lantern phases
    // for actors, roles, sets, and stages.  The user
    // can override this by inserting and deleting phases
    // at will.
    g_theTitle->m_theScheduler->init();

    // Initialize event dispatch manager.
    //g_theTitle->m_theEventMgr = new MleEventDispatcher();
    g_theTitle->m_theEventMgr = initEventMgr(eventTable, *numEvents);

    // Setup stage and set; Note: must follow initPlatform()
    if (initTitle)
        g_theTitle->m_titleData = initTitle();
    else
        g_theTitle->m_titleData = NULL;

    // Create and initialize stage.
    //new MleIvStage();
    //((MleIvStage *)MleStage::g_theStage)->init();

    // Initialize the platform data.
    //g_theTitle->m_platformData = ((MleIvStage *)MleStage::g_theStage)->initPlatform();

    // Load the first group.
    //(void) mlLoadBootScene(g_workprint);

    return ML_TRUE;
}


static void _processScheduledPhases(void)
{
    // Run all the scheduled phases.  This will even work if
    // the title author has inserted his own phases.
    MleSchedulerIterator iter(g_theTitle->m_theScheduler);
    for (MleSchedulerPhase *phase = iter.firstPhase();
         phase != NULL;
         phase = iter.nextPhase() )
    {
        g_theTitle->m_theScheduler->go(phase);
    }
}


// Main loop of execution.
int mainLoop()
{
    int status = 0;

#if 0
    while(! QtStage::g_doExit) {
        // Execute the scheduled phases in order of insertion.
        g_theTitle->m_theScheduler->goAll();

        // Process pending Qt events.
        app.processEvents();

        //qDebug() << "null Title: mainloop iteration.";
    }
#endif /* 0 */
    // Get the application context for the stage.
    XtAppContext appContext = SoXt::getAppContext();

    for (;;)
    {
        // Check for events and dispatch them if found.
        while (XtAppPending(appContext))
        {
            XEvent event;
            SoXt::nextEvent(appContext, &event);
            Boolean dispatched = SoXt::dispatchEvent(&event);
        }
#if 0
        while (XtAppPending(appContext))
            XtAppProcessEvent(appContext,XtIMAll);
#endif /* 0 */

        // Process phases registered with the scheduler.
        _processScheduledPhases();

        // Quit on title request.
        if (g_theTitle->m_quit == ML_TRUE)
            break;
    }

    return status;
}


// Clean up title environment.
MlBoolean cleanupEnv(void)
{
    MLE_ASSERT(g_theTitle->m_theScheduler != NULL);
    MLE_ASSERT(g_theTitle->m_theEventMgr != NULL);
    MLE_ASSERT(g_theTitle->m_platformData != NULL);
    MLE_ASSERT(g_theTitle->m_dpp != NULL);

    // Close Digital Playprint and delete object.
    mlUnloadPlayprint(g_theTitle->m_dpp);

    delete g_theTitle->m_theScheduler;
    delete g_theTitle->m_theEventMgr;
    mlFree(g_theTitle->m_platformData);
    //if (g_theTitle->m_titleData)
        // m_titleData is a callback function; can't delete it
        //delete g_theTitle->m_titleData;
    mlFree(g_theTitle);

    return ML_TRUE;
}
