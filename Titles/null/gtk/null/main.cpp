/** @defgroup NullTitle Magic Lantern null Title */

/**
 * @file main.cpp
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

// Include system header files.
//#include <getopt.h>

// Include Gtk header files.

// Include Magic Lantern header files.
#ifdef WIN32
#include <mle/mlGetOpt.h>
#else
#include <unistd.h>
#endif
#include <mle/mlMalloc.h>
#include <mle/mlFileio.h>
#include <mle/mlAssert.h>
#include <mle/mlTypes.h>
#include <mle/mlErrno.h>

// Include Magic Lantern Runtime Engine header files.
#include <mle/MleDirector.h>
#include <mle/MleEventDispatcher.h>
#include <mle/MleScheduler.h>

// Include title header files.
#include "mle/ivstage.h"

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
    char *commandName;  /* name of command */
    char *playprint;    /* name of playprint file to load */
} ArgStruct;

const char *usage_str = "\
Syntax:  null <playprint>\n\
\n\
         <playprint>    Digital Playprint generated from null.dwp\n\
\n\
Function: Execute the null Magic Lantern title.\n\
\n\
An empty stage is displayed.\n";


static char *getCanonicalPath(char *path)
{
    return strdup(path);
}

// Parse command line options.
int parseArgs(int argc, char *argv[], ArgStruct *args)
{
    // Declare local variables.
    extern int optind;

    // Parse options here, if there are any.

    // Parse remaining arguments.
    for ( ; optind < argc; optind++)
    {
        if (! args->playprint)
        {
            args->playprint = getCanonicalPath(argv[optind]);
        } else
        {
            fprintf(stderr,"%s\n",usage_str);
            return FALSE;
        }
    }

    // If there is no specified playprint, complain.
    if (args->playprint == NULL)
    {
        fprintf(stderr,"%s\n",usage_str);
        return FALSE;
    }

    // Having made it to here implies that we have good arguments.
    return TRUE;
}

// A handle to the title's global data.
MleDirector *g_theTitle;

// Title main entry point.
int main(int argc, char *argv[])
{
    // Declare local variables.
    int envArgc;
    void *envArgv[4];
    void *playprint = NULL;
    int retValue;

    // Parse remaining commandline arguments.
    ArgStruct args;
    args.commandName = argv[0];
    args.playprint = NULL;
    if (! parseArgs(argc, argv, &args))
        exit(1);
    playprint = args.playprint;

    // Create a new title environment, the director.
    g_theTitle = (MleDirector*)mlMalloc(sizeof(MleDirector));
    MLE_ASSERT(g_theTitle);

    // Initialize the title.
    envArgv[0] = (void *)g_eventTable;
    envArgv[1] = (void *)&g_numEvents;
    envArgv[2] = playprint;
    envArgv[3] = NULL;
    envArgc = 4;
    MlBoolean status = initEnv(envArgc, envArgv);
    if (status == ML_FALSE)
        exit(1);

    // Create the stage and initialize it.
    MleIvStage *theStage = new MleIvStage();
    //theStage->init();
    //theStage->setName("null Title");
    //theStage->show();

    // Main execution loop.
    retValue = mainLoop();

    // Cleanup title environment.
    cleanupEnv();
    //delete theStage;

    // Returns the value from main loop of execution.
    return(retValue);
}
