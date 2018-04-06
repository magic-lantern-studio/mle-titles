/** @defgroup null Magic Lantern null Title */

/**
 * @file mlPlatformData.h
 * @ingroup Null
 *
 * This file contains platform specific declarations for the mtea title.
 *
 * @author Mark S. Millard
 * @date April 24, 2015
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

#ifndef __MLE_PLATFORMDATA_H_
#define __MLE_PLATFORMDATA_H_

// Include system header files.
#include <windows.h>
#include <windowsx.h>

// Include Magic Lantern types.
#include "mle/mlTypes.h"


/**
 * This structure is what goes into the m_platformData slot
 * of the MleDirector structure for the Win32 API.
 */
typedef struct MleWin32PlatformData
{
    HINSTANCE m_appInstance;       /* Passed in from WinMain   */
    char      m_appName[9];        /* Derived from appInstance */
    char      m_appTitle[41];      /* Derived from appInstance */
    char      m_playprint[256];    /* Derived from appInstance */
    DWORD     m_winStyle;          /* Initialized in main      */
    int       m_defaultWinWidth;   /* Initialized in main      */
    int       m_defaultWinHeight;  /* Initialized in main      */
    MlBoolean m_keyboardManager;   /* Is there a registered keyboard manager? */
    MlBoolean m_mouseManager;      /* Is there a registered mouse manager? */
    MlBoolean m_joystickManager;   /* Is there a registered joystick manager? */

} MleWin32PlatformData;


//
// Constants for MleWin32Data initialization
//
#define IDS_APPNAME         102
#define IDS_DESCRIPTION     103
#define IDS_PLAYPRINT       104
#define DEFAULT_VIEW_WIDTH  320
#define DEFAULT_VIEW_HEIGHT 240

// Definitions for use on keyboardManager, mouseManager,
// and joystickManager booleans.
#define MLE_INPUT_DEVICE_MANAGER_NOT_INSTANTIATED FALSE
#define MLE_INPUT_DEVICE_MANAGER_INSTANTIATED     TRUE


#endif /* __MLE_PLATFORMDATA_H_ */
