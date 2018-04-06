/** @defgroup Nulltitle Magic Lantern null Title */

/**
 * @file main.cpp
 * @ingroup NullTitle
 *
 * This file implements the main entry points into the mtea title.
 *
 * @author Mark S. Millard
 * @date September 20, 2017
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2017 Wizzer Works
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

// Include Digital Playprint header files.
#include "mle/ppinput.h"

// Platform data must match the Qt MLE Runtime Engine platform.
#include "mlPlatformData.h"

// Include Magic Lantern Qt Parts header files.
#include "mle/qt/qtstage.h"

// Include title header files.

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

    return(qtData);
}


MlBoolean initEnv(int argc, void **argv)
{
    MleEventEntry *eventTable;
    int *numEvents;
    void *(*initTitle)(void);
    char *playprint;

    // Parse arguments.
    if (argc != 4)
    {
        return(ML_FALSE);
    } else
    {
        eventTable = (MleEventEntry *)argv[0]; // A reference to a table of Magic Lantern events.
        numEvents = (int *)argv[1];            // The number of events in the table.
        playprint =  (char *)argv[2];          // The file name of the Digital Playprint.
        initTitle = (void *(*)(void))argv[3];  // A callback function to initialize title specific data.
    }

    // The title director should already be constructed.
    MLE_ASSERT(g_theTitle);

    // Initialize the platform data.
    g_theTitle->m_platformData = initPlatform();

    // Initialize quit flag.
    g_theTitle->m_quit =  FALSE;

    // Load the playprint.
    if (playprint != NULL)
        g_theTitle->m_dpp = mlLoadPlayprint(playprint, MLE_DPP_FINDPPLE);
    else
        g_theTitle->m_dpp = mlLoadPlayprint(
            ((MleQtPlatformData *)g_theTitle->m_platformData)->m_playprint,
            MLE_DPP_FINDPPLE);

    // Initialize scheduler.
    g_theTitle->m_theScheduler = new MleScheduler();
    // Now set it up to know the standard Magic Lantern phases
    // for actors, roles, sets, and stages.  The user
    // can override this by inserting and deleting phases
    // at will.
    g_theTitle->m_theScheduler->init();

    // Initialize event dispatch manager.
    g_theTitle->m_theEventMgr = new MleEventDispatcher();

    // Setup stage and set; Note: must follow initPlatform()
    if (initTitle)
        g_theTitle->m_titleData = initTitle();
    else
        g_theTitle->m_titleData = NULL;

    return ML_TRUE;
}


int mainLoop(const QGuiApplication &app)
{
    int status = 0;

    while(! QtStage::g_doExit) {
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
    MLE_ASSERT(g_theTitle->m_dpp != NULL);

    // Close Digital Playprint and delete object.
    mlUnloadPlayprint(g_theTitle->m_dpp);

    delete g_theTitle->m_theScheduler;
    delete g_theTitle->m_theEventMgr;
    mlFree(g_theTitle->m_platformData);
    if (g_theTitle->m_titleData)
        delete g_theTitle->m_titleData;
    mlFree(g_theTitle);

    return ML_TRUE;
}
