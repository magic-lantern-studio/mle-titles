/** @defgroup DppTestTitle Magic Lantern null Title */

/**
 * @file main.cpp
 * @ingroup DppTestTitle
 *
 * This file implements the main entry points into the imagetest title.
 *
 * @author Mark S. Millard
 * @date October 12, 2017
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

// Inlclude system header files.
#include <getopt.h>

// Include Qt header files.
#include <QApplication>
#include <QScreen>
#include <QTimer>
#include <qdebug.h>

// Include Magic Lantern header files
#include "mle/mlTypes.h"
#include "mle/mlMalloc.h"
#include "mle/mlAssert.h"
#include "mle/mlErrno.h"

// Include Magic Lantern Runtime Engine header files.
#include "mle/MleDirector.h"
#include "mle/MleEventDispatcher.h"
#include "mle/MleScheduler.h"

// Include title header files.
#include "mle/qt/qtstage.h"
#include "mle/qt/qt2dset.h"
#include "mle/qt/2dimgrole.h"
#include "mle/qt/imagmref.h"
#include "mle/2dimga.h"

// Declare external references.
extern MleEventEntry g_eventTable[];
extern int g_numEvents;
extern MlBoolean initEnv(int, void **);
extern int mainLoop(const QGuiApplication &);
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
    char *filename;     /* name of playprint file to load */
} ArgStruct;

const char *usage_str = "\
Syntax:  dpptest <file>\n\
\n\
         <file>    Digital Playprint\n\
\n\
Function: Execute the dpptest Magic Lantern title.\n\
\n\
A Qt stage is used to display an image referenced by the Digital Playprint.\n";


static char *getCanonicalPath(char *path)
{
    return strdup(path);
}

int parseArgs(int argc, char *argv[], ArgStruct *args)
{
    /* Declare local variables. */
    extern int optind;

    // Parse options here, if there are any.

    // Parse remaining arguments.
    for ( ; optind < argc; optind++)
    {
        if (! args->filename)
        {
            args->filename = getCanonicalPath(argv[optind]);
        } else
        {
            fprintf(stderr,"%s\n",usage_str);
            return FALSE;
        }
    }

    /* If there is no specified playprint, complain. */
    if (args->filename == NULL)
    {
        fprintf(stderr,"%s\n",usage_str);
        return FALSE;
    }

    /* Having made it to here implies that we have good arguments. */

    return TRUE;
}

int main(int argc, char *argv[])
{
    // Declare local variables.
    int envArgc;
    void *envArgv[4];
    char *playprint = NULL;
    int retValue;

    // Initialize Qt application.
    QApplication app(argc, argv);

    // Parse remaining commandline arguments.
    ArgStruct args;
    args.commandName = argv[0];
    args.filename = NULL;
    if (! parseArgs(argc, argv, &args))
        exit(1);
    playprint = args.filename;

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

    // Main execution loop.
    retValue = mainLoop(app);

    // Finish by cleaning up the title execution components.
    cleanupEnv();

    // Returns the value from main loop of execution.
    return(retValue);
}
