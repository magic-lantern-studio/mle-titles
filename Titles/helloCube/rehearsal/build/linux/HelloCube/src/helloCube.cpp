/** @defgroup HelloCubeTitle Magic Lantern HelloCube Title */

/**
 * @file helloCube.cpp
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

// Include system header files.
#ifdef WIN32
#include <windows.h>
#include <windowsx.h>
#else
#ifdef __linux__
#include <string.h>
#else
#include <strings.h>
#endif
#endif
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Include Magic Lantern header files.
#ifdef WIN32
#include "mle/mlGetOpt.h"
#else
#include <unistd.h>
#endif
#include "mle/mlMalloc.h"
#include "mle/mlFileio.h"
#include "mle/mlAssert.h"
#include "mle/mlTypes.h"

// Include Magic Lantern Runtime Engine header files.
#include "mle/MleDirector.h"
#include "mle/MleEventDispatcher.h"


// Declare external references.
extern MleEventEntry g_eventTable[];
extern int g_numEvents;
extern MlBoolean initEnv(int, void **);
extern int mainLoop(void);
extern MlBoolean cleanupEnv(void);


// Argument structures for parser.
typedef struct _pattern
{
    char            *str;
    struct _pattern *next;
} Pattern;

typedef struct _ArgStruct
{
    char       *commandName;  /* Name of command. */
    int        verbose;       /* Be verbose. */
    char       *workprint;    /* Digital Workprint. */
} ArgStruct;

const char *usage_str = "\
Syntax:   helloCube [-v] <workprint>\n\
\n\
          -v           Be verbose\n\
          <workprint>  Digital Workprint for title\n\
\n\
Function: Execute the helloCube Magic Lantern title.\n\
\n";


int parseArgs(int argc, char *argv[], ArgStruct *args)
{
    /* declare local variables */
    int c;
    int errflg;
    extern char *optarg;
    extern int optind;

    errflg = 0;
    while ((c = getopt(argc, argv, "v")) != -1)
	{
		switch (c)
		{
		  case 'v':
			args->verbose = TRUE;
			break;
		  case '?':
			errflg++;
		}
    }

    if (errflg)
	{
		(void)fprintf(stderr, "%s\n", usage_str);
		return FALSE;
    }

    for ( ; optind < argc; optind++)
	{
		if (! args->workprint)
		{
			args->workprint = strdup(argv[optind]);
		} else {
			fprintf(stderr,"%s\n",usage_str);
			return FALSE;
		}
	}

    /* If there is no specified Digital Workprint file, complain. */
    if (args->workprint == NULL)
	{
		fprintf(stderr,"%s\n",usage_str);
		return FALSE;
    }

    /* Having made it to here implies that we have good arguments. */

    return TRUE;
}


int main(int argc, char **argv)
{
	// Declare local variables.
	ArgStruct args;
    int envArgc;
	void *envArgv[6];
	int retValue;

    // Parse arguments.
    args.commandName = argv[0];
    args.verbose = FALSE;
    args.workprint = NULL;
    if (! parseArgs(argc, argv, &args))
	{
      exit(1);
    }

    // Create a new title environment, the director.
    g_theTitle = (MleDirector*)mlMalloc(sizeof(MleDirector));
    MLE_ASSERT(g_theTitle);

    // Initialize title environment.
    envArgv[0] = (void *)g_eventTable;
    envArgv[1] = (void *)g_numEvents;
    envArgv[2] = args.workprint;
    envArgv[3] = NULL; // Currently no title specific data.
    envArgc = 4;
    if (! initEnv(envArgc,envArgv))
        return FALSE;

    // Main execution loop.
    retValue = mainLoop();

    // Clean up title environment.
    cleanupEnv();

    // Return the value from PostQuitMessage.
    return retValue;
}
