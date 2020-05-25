/** @defgroup mtea Magic Lantern mtea Title */

/**
 * @file title.cxx
 * @ingroup mtea
 *
 * This file implements utilities for the mtea title.
 *
 * @author Mark S. Millard
 * @date May 1, 2003
 */

// COPYRIGHT_BEGIN
//
//  Copyright (C) 2000-2007  Wizzer Works
//
//  Wizzer Works makes available all content in this file ("Content").
//  Unless otherwise indicated below, the Content is provided to you
//  under the terms and conditions of the Common Public License Version 1.0
//  ("CPL"). A copy of the CPL is available at
//
//      http://opensource.org/licenses/cpl1.0.php
//
//  For purposes of the CPL, "Program" will mean the Content.
//
//  For information concerning this Makefile, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

// Include system header files
#include <windows.h>
#include <windowsx.h>

// Include Magic Lantern header files.
#include "mle/mlTypes.h"
#include "mle/mlMalloc.h"
#include "mle/mlErrno.h"

// Include Runtime Player/Kernel header files.
#include "mle/MleDirector.h"
#include "mle/MleLoad.h"
#include "mle/MleScheduler.h"
#include "mle/MleEventDispatcher.h"
#include "mle/MleStage.h"

// Include Digital Playprint header files.
#include "mle/ppinput.h"

// Include Parts header files
#include "mle/pcstage.h"

// Platform data must match the win32 MLE Runtime Engine platform.
#include "mle/mlPlatformData.h"


// Forward declarations.
static MleEventDispatcher *initEventMgr(MleEventEntry *eventTable,int numEvents);
static MleWin32PlatformData *initPlatform(HINSTANCE hInstance);
static BOOL mainWindowRegister(void);


MlBoolean initEnv(int argc,void **argv)
{
    // Declare local variables.
    HINSTANCE hInstance;
    int nCmdShow;
    MleEventEntry *eventTable;
    int numEvents;
    void *(*initTitle)(void);
	char *playprint;

    // Parse arguments.
    if (argc != 6)
	{
        return(FALSE);
    } else
	{
        hInstance = (HINSTANCE)argv[0];
        nCmdShow = (int)argv[1];
        eventTable = (MleEventEntry *)argv[2];
        numEvents = (int)argv[3];
		playprint =  (char *)argv[4];
        initTitle = (void *(*)(void))argv[5];
    }  

    // Initialize the platform data.
    g_theTitle->m_platformData = initPlatform(hInstance);

    // Initialize quit flag.
    g_theTitle->m_quit =  FALSE;

    // Load the playprint.
	if (playprint != NULL)
		g_theTitle->m_dpp = mlLoadPlayprint(playprint,MLE_DPP_FINDPPLE);
	else
		g_theTitle->m_dpp = mlLoadPlayprint(
			((MleWin32PlatformData *)g_theTitle->m_platformData)->m_playprint,
			MLE_DPP_FINDPPLE);

    // Initialize scheduler.
    g_theTitle->m_theScheduler = new MleScheduler;

    // Now set it up to know the standard Magic Lantern phases
    // for actors, roles, sets, and stages.  The user
    // can override this by inserting and deleting phases
    // at will.
    g_theTitle->m_theScheduler->init();

    // Initialize event dispatch manager.
    g_theTitle->m_theEventMgr = initEventMgr(eventTable,numEvents);

    // Setup stage and set; Note: must follow initPlatform()
    if (initTitle)
        g_theTitle->m_titleData = initTitle();
    else
	    g_theTitle->m_titleData = NULL;

    // Initialize stage.
    if (mainWindowRegister() == FALSE)
    {
        MessageBox(NULL,"Could not register window class",
                   "ERROR",MB_OK | MB_TASKMODAL);
        return FALSE;
    }
    new PCBRenderStage();
	((PCBRenderStage *)MleStage::g_theStage)->m_showMode = nCmdShow;
    ((PCBRenderStage *)MleStage::g_theStage)->init();

    // Load the first group.
    (void) mlLoadBootScene();

    return TRUE;
}


void win32Cycle(void)
{
    //
    // Run all the scheduled phases.  This will even work if
    // the title author has inserted his own phases.
    //
    MleSchedulerIterator iter(g_theTitle->m_theScheduler);
    for (MleSchedulerPhase *phase = iter.firstPhase();
         phase != NULL;
         phase = iter.nextPhase() ) 
    {
    	g_theTitle->m_theScheduler->go(phase);
    }
}


int mainLoop(void)
{
    // Declare local variables.
    MSG msg;
    HACCEL hAccelTable;
    MleWin32PlatformData* win32Data = (MleWin32PlatformData*)g_theTitle->m_platformData;
  
    // Load keyboard shortcuts.
    hAccelTable = LoadAccelerators(win32Data->m_appInstance,win32Data->m_appName);
  
    // Grab messages and process them until WM_QUIT happens.
    for (;;)
	{
#ifdef _GDK_
        if (PeekMessage(&msg,0,0,0,PM_REMOVE) && (msg.message != WM_PAINT)) 
#else /* _GDK_ */
        if (PeekMessage(&msg,0,0,0,PM_REMOVE))
#endif /* _GDK_ */
		{
            if (msg.message == WM_QUIT)
                break;
            if (! TranslateAccelerator(msg.hwnd,hAccelTable,&msg))
			{
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else
		{
            win32Cycle();

            // Formerly called check if need update,
            // and then WaitMessage() if not.
        }

		// Quit on title request
		if (g_theTitle->m_quit == TRUE)
			break;
    }
  
    return(msg.wParam);
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

    return TRUE;
}


//
// mainWindowRegister()
//
// Attempt to register a window class for simple view window.
//
static BOOL
mainWindowRegister(void)
{
    // Declare local variables.
    WNDCLASS  wc;
    MleWin32PlatformData *titleEnv = (MleWin32PlatformData*)g_theTitle->m_platformData;
  
    //
    // Build window class structure.
    //
    memset(&wc,0,sizeof(wc));
  
#ifdef _GDK_
    wc.style         = CS_HREDRAW | CS_VREDRAW;
#else /* _GDK_ */
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
#endif /* _GDK_ */
    wc.lpfnWndProc   = (WNDPROC)MleWndProc;
    wc.cbClsExtra    = 0;
    // Window points to relevant stage. 
    wc.cbWndExtra    = sizeof(PCBRenderStage*); 
    wc.hInstance     = titleEnv->m_appInstance;
    wc.hIcon         = LoadIcon (titleEnv->m_appInstance,titleEnv->m_appName);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = titleEnv->m_appName;
    wc.lpszClassName = titleEnv->m_appName;
  
    //
    // Register the window class and return FALSE if unsuccesful.
    //
    if (! RegisterClass(&wc))
        return FALSE;
  
    return TRUE;
}


//
// Initialize Magic Lantern Dispatch Manager.
//
static MleEventDispatcher *
initEventMgr(MleEventEntry *eventTable,int numEvents)
{
    // Initialize dispatch manager
    // - dynamically allocate memory for events
    // - make room for 'numEvents' total events
    // - do not use queing; Windows already does this
    g_theTitle->m_theEventMgr = new MleEventDispatcher();
  
    // Install Magic Lantern event callbacks.
    g_theTitle->m_theEventMgr->installEventCB(eventTable,numEvents);
  
    return(g_theTitle->m_theEventMgr);
}


static MleWin32PlatformData *
initPlatform(HINSTANCE hInstance)
{
    // Declare local variables.
    MleWin32PlatformData* win32Data;

    // Allocate a platform specific data structure.
    //win32Data = (MleWin32PlatformData*)mlMalloc(sizeof(MleWin32PlatformData));
	win32Data = new MleWin32PlatformData();

    // Initialize the platform specific data
    //    Save the instance handle
    win32Data->m_appInstance = hInstance;    
    //    Load the application name
    LoadString(hInstance,IDS_APPNAME,
         win32Data->m_appName,sizeof(win32Data->m_appName));
    //    Load the application description
    LoadString(hInstance,IDS_DESCRIPTION,
         win32Data->m_appTitle,sizeof(win32Data->m_appTitle));
    //    Load the application description
    LoadString(hInstance,IDS_PLAYPRINT,
         win32Data->m_playprint,sizeof(win32Data->m_playprint));

    // Initialize input manager flags.
    win32Data->setKeyboardManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);
    win32Data->setMouseManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);
    win32Data->setJoystickManager(MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED);

    // XXX - extract window style from Set properties.
    win32Data->m_winStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | 
        WS_THICKFRAME | WS_MAXIMIZEBOX | WS_CLIPCHILDREN;

    // XXX - extract window size from Set properties
    win32Data->m_defaultWinWidth = DEFAULT_VIEW_WIDTH;
    win32Data->m_defaultWinHeight = DEFAULT_VIEW_HEIGHT;

    return(win32Data);
}  

//
// MleWndProc()
//
// procedure that calls standard dispatch mechanism.
//
LRESULT CALLBACK MleWndProc(
  HWND hwnd,
  UINT uMsg,
  WPARAM wParam,
  LPARAM lParam)
{           
    // Declare local variables.
    Win32CallData data;
    MleEvent event = uMsg;
    int status;
  
    data.hwnd = hwnd;
    data.uMsg = uMsg;
    data.wParam = wParam;
    data.lParam = lParam;
    status = g_theTitle->m_theEventMgr->dispatchEvent(event,(void *) &data);
    if (status == MLE_E_EVMGR_FAILEDDISPATCH)
        //
        // Probably failed because it was not registered with the
        // Magic Lantern Event Dispatch Manager. Try the Windows default.
        //
        return(DefWindowProc(hwnd,uMsg,wParam,lParam));
    else
        return(status);
}


// If the Game Developer Kit is enabled,
// pull in the direct draw library.

#if defined(_GDK_)
#pragma comment(lib,"ddraw")
#endif /* _GDK_ */

//
// Causes debug/release - float/fixed libaries to be loaded
//

#if defined(_DEBUG)
    /*
     * Debug libraries
     */
#if BASED_FIXED
#pragma comment(lib,"brdbmxr")
#pragma comment(lib,"brfwmxr")
#pragma comment(lib,"brmtmxr")
#pragma comment(lib,"brfmmxr")
#endif
#if BASED_FLOAT
#pragma comment(lib,"brdbmfr")
#pragma comment(lib,"brfwmfr")
#pragma comment(lib,"brmtmfr")
#pragma comment(lib,"brfmmfr")
#endif

#pragma comment(lib,"brpmmr")
#pragma comment(lib,"brstmr")
#pragma comment(lib,"hstwnmr")

#else
    /*
     * Release libraries
     */
#if BASED_FIXED
#pragma comment(lib,"brdbmxr")
#pragma comment(lib,"brfwmxr")
#pragma comment(lib,"brmtmxr")
#pragma comment(lib,"brfmmxr")
#endif
#if BASED_FLOAT
#pragma comment(lib,"brdbmfr")
#pragma comment(lib,"brfwmfr")
#pragma comment(lib,"brmtmfr")
#pragma comment(lib,"brfmmfr")
#endif

#pragma comment(lib,"brpmmr")
#pragma comment(lib,"brstmr")
#pragma comment(lib,"hstwnmr")

#endif
