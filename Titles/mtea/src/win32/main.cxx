/** @defgroup mtea Magic Lantern mtea Title */

/**
 * @file main.cxx
 * @ingroup mtea
 *
 * This file implements the main entry points into the mtea title.
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
#include "texture.h"

// Declare external references.
extern MleEventEntry g_eventTable[];
extern int g_numEvents;
extern MlBoolean initEnv(int, void **);
extern int mainLoop(void);
extern MlBoolean cleanupEnv(void);

//
// parseArgs()
//
// Parse commandline arguments. Currently, the only argument may be
// the Digital Playprint.
//
void **
parseArgs(LPSTR cmdline, int *argc)
{
	void **argv = NULL;
	*argc = 0;

	if (cmdline != NULL)
	{
		char *playprint = (char *)mlMalloc(strlen(cmdline) + 1);
		strcpy(playprint,cmdline);
		argv = (void **)mlMalloc(sizeof(void *));
		argv[0] = mlMalloc(sizeof(void *));
		argv[0] = (void *)playprint;
		*argc = 1;
	}

	return argv;
}

//
// freeArgs()
//
// Free memory allocated for processing the commandline arguments.
//
void
freeArgs(void **argv, int argc)
{
	for (int i = 0; i < argc; i++)
	{
		mlFree(argv[i]);
	}
	mlFree(argv);
}

//
// WinMain()
//
// Win32 Runtime Player.
//
int 
APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
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
    if (argc == 1)
		playprint = argv[0];
  
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
	updateMaterialRegistry();
  
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
