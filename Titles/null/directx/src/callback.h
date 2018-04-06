/** @defgroup null Magic Lantern null Title */

/**
 * @file callback.h
 * @ingroup Null
 *
 * This file contains declarations for events and their callbacks which
 * are specific to this title.
 *
 * @author Mark S. Millard
 * @date Aprli 24, 2015
 */

// COPYRIGHT_BEGIN
//
//  Copyright (C) 2000-2015  Wizzer Works
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


#ifndef __CALLBACK_H_
#define __CALLBACK_H_

// Include system header files.
#include <windows.h>

// Include Magic Lantern Runtime header files.
#include "mle/MleEventDispatcher.h"


//
// Event callback prototypes.
//

//
// Callbacks for Windows Messages.
int msgCreate(MleEvent event,void *callData,void *clientData);
int msgDestroy(MleEvent event,void *callData,void *clientData);
int msgActivateApp(MleEvent event,void *callData,void *clientData);
int msgPaint(MleEvent event,void *callData,void *clientData);

    
#endif __CALLBACK_H_
