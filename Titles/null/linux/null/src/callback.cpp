/** @defgroup NullTitle Magic Lantern null Title */

/**
 * @file callback.ccp
 * @ingroup NullTitle
 *
 * This file implements the events and their callbacks which
 * are specific to this title.
 */

// COPYRIGHT_BEGIN
// The MIT License (MIT)
//
// Copyright (c) 2022-2024 Wizzer Works
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
//#include <qdebug.h>
#include <iostream>

// Include Magic Lantern header files.
#include <mle/mlAssert.h>

// Include Magic Lantern Runtime Engine header files.
#include <mle/MleScheduler.h>
#include <mle/MleDirector.h>
#include <mle/MleEventDispatcher.h>

// Include Magic Lantern Runtime header files for Xt target.
//#include <mle/ivstage.h>

// Include title header files.
#include "callback.h"

using namespace std;

MleEventEntry g_eventTable[] =
{
    /* {<event>, <callback>, <client data>, <event dispatch mode>} */
    /* e.g. {QT_CLOSE_EVENT,msgClose,(void *)g_theTitle,MLE_EVMGR_IMMEDIATE|MLE_EVMGR_ENABLED} */
    {NULLTITLE_CLOSE_EVENT,msgClose,(void *)g_theTitle,MLE_EVMGR_IMMEDIATE|MLE_EVMGR_ENABLED}
};

int g_numEvents = sizeof(g_eventTable) / sizeof(MleEventEntry);

//
// Message handling callbacks
//

//
// msgClose()
//
// Handles XEvent messages
// 
// Process close event before shutting down title.
//
int msgClose(MleEvent event,void *callData,void *clientData)
{
    //qDebug() << "null Title: processing QT_CLOSE_EVENT message.";
	cout << "null Title: processing XEvent message." << endl;
    return 0;
}
