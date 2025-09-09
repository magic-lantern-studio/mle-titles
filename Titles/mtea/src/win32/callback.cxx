/** @defgroup mtea Magic Lantern mtea Title */

/**
 * @file callback.cxx
 * @ingroup mtea
 *
 * This file implements the events and their callbacks which
 * are specific to this title.
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2000-2025 Wizzer Works
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
#include <windows.h>
#include <windowsx.h>

// Include Magic Lantern header files.
#include <mle/mlAssert.h>

// Include Magic Lantern Runtime Engine header files.
#include <mle/MleScheduler.h>
#include <mle/MleDirector.h>

// Include Magic Lantern Runtime header files for PC target.
#include <mle/pcstage.h>

// Include title header files.
#include "callback.h"

MleEventEntry g_eventTable[] =
{
    {WM_CREATE,msgCreate,NULL,MLE_EVMGR_IMMEDIATE|MLE_EVMGR_ENABLED},
    {WM_DESTROY,msgDestroy,(void *)g_theTitle,MLE_EVMGR_IMMEDIATE|MLE_EVMGR_ENABLED},
    {WM_ACTIVATEAPP,msgActivateApp,(void *)g_theTitle,MLE_EVMGR_IMMEDIATE|MLE_EVMGR_ENABLED}
};

int g_numEvents = sizeof(g_eventTable) / sizeof(MleEventEntry);

//
// Message handling callbacks
//

//
// msgCreate()
//
// Handles WM_CREATE messages
// 
// Creates any sub-windows and puts the menu checks/enable into
// the initial state
//
int msgCreate(MleEvent event,void *callData,void *clientData)
{
    // declare local variables
    Win32CallData *eventData = (Win32CallData *)callData;
	HMENU menu;
 	LPCREATESTRUCT cs;

    menu = GetMenu(eventData->hwnd);
    cs = (LPCREATESTRUCT)(eventData->lParam);

	//
 	// Application view pointer is passed through
	// the CREATESTRUCT
	//
	PCBRenderStage* stage = (PCBRenderStage*)cs->lpCreateParams;

	//
	// Store the view pointer in window extra data.
	//
	MLE_INST_STAGE_SET(eventData->hwnd,stage);

	//
	// Paint window.
	//
	UpdateWindow(eventData->hwnd);

    return 0;
}

//
// msgDestroy()
//
// Handles WM_DESTROY messages.
//
int msgDestroy(MleEvent event,void *callData,void *clientData)
{
    // Declare local variables.
    Win32CallData *eventData = (Win32CallData *)callData;
  
    PCBRenderStage* stage = MLE_INST_STAGE_GET(eventData->hwnd);
  
    //
    // Single window application - exiting window quits app.
    //
    PostQuitMessage(0);
    return 0;
}


// 
// msgActivateApp()
//
// Handles WM_ACTIVEATEAPP messages.
//
int msgActivateApp(MleEvent event,void *callData,void *clientData)	
{
    // Declare local variables.
    Win32CallData *eventData = (Win32CallData *)callData;
  
    return 0;
}

