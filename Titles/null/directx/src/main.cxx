/** @defgroup null Magic Lantern null Title */

/**
 * @file main.cxx
 * @ingroup Null
 *
 * This file implements the main entry points into the mtea title.
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

// Include Win32 header files.
#include <windows.h>
#include <windowsx.h>

// Include Magic Lantern header files
#include "mle/mlTypes.h"
#include "mle/mlMalloc.h"
#include "mle/mlAssert.h"
#include "mle/mlErrno.h"

// Include Magic Lantern Runtime Engine header files.
#include "mle/MleDirector.h"
#include "mle/MleEventDispatcher.h"

// Include title header files.

// Declare external references.
extern MleEventEntry g_eventTable[];
extern int g_numEvents;
extern MlBoolean initEnv(int, void **);
extern int mainLoop(void);
extern MlBoolean cleanupEnv(void);

// Convert a wide Unicode string to an UTF8 string
static LPSTR utf8Encode(LPCWSTR wstr)
{
    if (wstr == NULL) return NULL;
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, wcslen(wstr), NULL, 0, NULL, NULL);
    LPSTR strTo = (char *) mlMalloc(size_needed + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, wcslen(wstr), strTo, size_needed, NULL, NULL);
	strTo[size_needed] = '\0';
    return strTo;
}

//
// parseArgs()
//
// Parse commandline arguments. Currently, the only argument may be
// the Digital Playprint.
//
void **parseArgs(LPSTR cmdline, int *argc)
{
	void **argv = NULL;
	*argc = 0;

	// Let Windows parse command line into manageable argument list.
	LPWSTR *szArglist;
    int nArgs;
    int i;

    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    if( NULL == szArglist )
    {
        wprintf(L"CommandLineToArgvW failed\n");
        return 0;
    }

	// Create argument vector for title.
	if (nArgs == 2)
	{
		char *playprint = utf8Encode(szArglist[1]);
		argv = (void **)mlMalloc(sizeof(void *));
		argv[0] = mlMalloc(sizeof(void *));
		argv[0] = (void *)playprint;
		*argc = 1;
	}

	// Free memory allocated for CommandLineToArgvW arguments.
    LocalFree(szArglist);

	return argv;
}

//
// freeArgs()
//
// Free memory allocated for processing the commandline arguments.
//
void freeArgs(void **argv, int argc)
{
	for (int i = 0; i < argc; i++)
	{
		mlFree(argv[i]);
	}
	if (argv != NULL) mlFree(argv);
}

//
// WinMain()
//
// Win32 Runtime Player.
//
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    // Declare local variables.
	int argc;
	void **argv;
    int envArgc;
    void *envArgv[6];
	void *playprint = NULL;
    int retValue;

	// Parse commandline arguments.
	argv = parseArgs(lpCmdLine,&argc);
    if (argc == 1) {
		playprint = argv[0];
	} else {
		OutputDebugString("Usage: null <playprint>\n");
		freeArgs(argv,argc);
		return(-1);
	}
  
    // Create a new title environment, the director.
    g_theTitle = (MleDirector*)mlMalloc(sizeof(MleDirector));
    MLE_ASSERT(g_theTitle);
  
    // Initialize title environment.
    envArgv[0] = (void *)hInstance;
    envArgv[1] = (void *)nCmdShow;
    envArgv[2] = (void *)g_eventTable;
    envArgv[3] = (void *)g_numEvents;
	envArgv[4] = playprint;
    envArgv[5] = NULL;
    envArgc = 6;
    if (! initEnv(envArgc,envArgv))
        return FALSE;

    // Free memory allocated for commandline arguments.
	freeArgs(argv,argc);

	// Perform necessary patches to the materials.
	//updateMaterialRegistry();
  
    //
    // Main execution loop.
    //
    retValue = mainLoop();
  
    //
    // Cleanup title environment.
    //
    cleanupEnv();
  
    //
    // Returns the value from PostQuitMessage.
    //
    return(retValue); 
}
