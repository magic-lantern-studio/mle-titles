/** @defgroup HelloCubeTitle Magic Lantern Parts */

/**
 * @file main.cpp
 * @ingroup HelloCubeTitle
 *
 * This file implements the Qt CubeActor unit test.
 *
 * @author Mark S. Millard
 * @date January 13, 2020
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2020 Wizzer Works
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

// Include Qt header files.
#include <QApplication>
#include <QTimer>

// Include Magic Lantern Runtime Engine header files.
#include "mle/MleDirector.h"
#include "mle/MleEventDispatcher.h"

// Include title header files.
#include "CubeStage.h"
#include "CubeSet.h"
#include "CubeRole.h"
#include "CubeActor.h"

int mainloop(const QApplication &app)
{
    int status = 0;

    while(! CubeStage::g_doExit) {
        // Execute the scheduled phases in order of insertion.
        g_theTitle->m_theScheduler->goAll();

        // Process pending Qt events.
        app.processEvents();

        //qDebug() << "CubeStage Unit Test: mainloop iteration.";
    }

    return status;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Initialize the title. Normally this would be in a title template.
    g_theTitle = new MleDirector();
    g_theTitle->m_theEventMgr = new MleEventDispatcher();
    g_theTitle->m_theScheduler = new MleScheduler();
    g_theTitle->m_theScheduler->init();

    // Create the stage and initialize it.
    CubeStage *theStage = new CubeStage();
    theStage->init();
    theStage->setName("CubeActor Unit Test");

    // Add the set and initialize it.
    CubeSet *aSet = new CubeSet();
    aSet->init();

    // Create an actor.
    CubeActor *anActor = new CubeActor();

    // And its role. Note that the CubeRole requires Open Inventor initialization (which
    // is done by the CubeStage).
    CubeRole *theRole = new CubeRole(anActor);
    theRole->init();

    // The CubeActor requires a role before it can be initialized. This is because the
    // CubeActor in this demo hard codes the CubeRole dependency.
    anActor->init();

    theStage->show();

    // Quit after 10 seconds. For platforms that do not have windows that are closeable.
    //if (QCoreApplication::arguments().contains(QString::fromUtf8("--timeout")))
    //    QTimer::singleShot(10000, qApp, &QCoreApplication::quit);

    //const int exitValue = app.exec();
    const int exitValue = mainloop(app);

    // Clean up.
    delete theStage;

    return exitValue;
}
