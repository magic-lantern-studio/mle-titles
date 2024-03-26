/** @defgroup mtea Magic Lantern mtea Title */

/**
 * @file spinnera.cxx
 * @ingroup mtea
 *
 * This file implements the SpinnerActor class for the mtea title.
 *
 * @author Mark S. Millard
 * @date May 1, 2003
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2003-2022 Wizzer Works
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
#include <iostream>

// Include Magic Lantern Runtime Engine header files.
#include "mle/MleScheduler.h"
#include "mle/MleDirector.h"

// Include Magic Lantern Extension header files.
#include "math/vector.h"
#include "math/rotation.h"

// Include title header files.
#include "spinnera.h"

#if defined(__linux__)
#if defined(HAVE_LOG4CXX)
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/helpers/exception.h"
#include "log4cxx/consoleappender.h"
#include "log4cxx/patternlayout.h"

using namespace log4cxx;
using namespace log4cxx::helpers;

LoggerPtr g_spinnerLogger(Logger::getLogger("SpinnerActor"));
static MlBoolean g_spinnerLoggerInitialized = FALSE;
#endif /* HAVE_LOG4CXX */
#endif

using namespace std;


MLE_ACTOR_SOURCE(SpinnerActor,MleActor);


SpinnerActor::SpinnerActor()
{
#if defined(__linux__)
#if defined(HAVE_LOG4CXX)
	if (!g_spinnerLoggerInitialized) {
		// Create an appender for the logging output pattern.
		PatternLayoutPtr patternLayout = (PatternLayoutPtr) new PatternLayout("[%-5p] %d %c - %m%n");
		ConsoleAppenderPtr appender = (ConsoleAppenderPtr) new ConsoleAppender(patternLayout);

		/// Set up a simple configuration that logs to the console.
	    BasicConfigurator::configure(appender);
	    //LoggerPtr logger(Logger::getLogger("main"));
	    LOG4CXX_DEBUG(g_spinnerLogger, "log4cxx Initialized");
	    g_spinnerLoggerInitialized = TRUE;
	}
#endif /* HAVE_LOG4CXX */
#endif
}

#ifdef MLE_REHEARSAL
void SpinnerActor::initClass()
{
    // Register parent actor's Members
    mleRegisterActorClass(SpinnerActor, MleActor);

    // Register the Property Members
    mleRegisterActorMember(SpinnerActor, scale, MlVector3);
    mleRegisterActorMember(SpinnerActor, orientation, MlRotation);
    mleRegisterActorMember(SpinnerActor, position, MlVector3);
    mleRegisterActorMember(SpinnerActor, model, MediaRef);
    mleRegisterActorMember(SpinnerActor, colorMap, MediaRef);
    mleRegisterActorMember(SpinnerActor, texture, MediaRef);

    // Mark all the properties that belongs to the "transform" property
    // data set.
    mleRegisterActorMemberDataset(SpinnerActor, scale, MLE_PROP_DATASET_TRANSFORM);
    mleRegisterActorMemberDataset(SpinnerActor, orientation, MLE_PROP_DATASET_TRANSFORM);
    mleRegisterActorMemberDataset(SpinnerActor, position, MLE_PROP_DATASET_TRANSFORM);
}


void SpinnerActor::resolveEdit(const char* prop)
{ 
    if (prop) 
    { 
	    if (!strcmp("scale",prop)) 
            scale.push(this);
        else 
        if (!strcmp("orientation",prop)) 
            orientation.push(this);
        else 
        if (!strcmp("position",prop))
            position.push(this);
        else 
        if (!strcmp("model",prop)) 
            model.push(this);
        else 
        if (!strcmp("colorMap",prop)) 
            colorMap.push(this);
        else 
        if (!strcmp("texture",prop)) 
        {
			texture.push(this);
            model.push(this);
        }
    }
    else 
       //Update transform-related properties only.
       update(); 
}
#endif /* MLE_REHEARSAL */

SpinnerActor::~SpinnerActor()
{
    // Remove the behave function from the scheduler.
    g_theTitle->m_theScheduler->remove(this);
}


void  SpinnerActor::init()
{
#if defined(HAVE_LOG4CXX)
#else
#endif

    colorMap.push(this);
    texture.push(this);
    model.push(this);
    update();

    // Register with the scheduler.
    g_theTitle->m_theScheduler->insertFunc(PHASE_ACTOR,(MleSchedulerFunc)behave,this,this);
}


void SpinnerActor::update()
{
    // Update transform-related properties only.
    scale.push(this);
    orientation.push(this);
    position.push(this);
}


void SpinnerActor::behave(SpinnerActor* spinner)
{
    // Define spin parameters.
    static MlRotation delta(MlVector3(
//		ML_SCALAR(0),ML_SCALAR(1),ML_SCALAR(0)), ML_SCALAR(0.35));
		ML_SCALAR(0),ML_SCALAR(1),ML_SCALAR(0)), ML_SCALAR(0.035));

    spinner->orientation.m_rotation *= delta;
    spinner->orientation.push(spinner);
}

void
SpinnerActor:: getProperty(MleObject *object, const char *name, unsigned char **value)
{
#if defined(HAVE_LOG4CXX)
	LOG4CXX_DEBUG(g_spinnerLogger, "Getting SpinnerActor property " << name << ".");
#else
    cout << "Getting SpinnerActor property " << name << "." << endl;
#endif
    if (strcmp("position",name) == 0)
    {
    	Mle3dTranslationProperty position = ((SpinnerActor *)object)->getPositionProperty();
        *((Mle3dTranslationProperty *)value) = position;
    } else if (strcmp("orientation",name) == 0)
    {
    	Mle3dQuaternionRotationProperty orientation = ((SpinnerActor *)object)->getOrientationProperty();
    	*((Mle3dQuaternionRotationProperty *)value) = orientation;
    } else if (strcmp("scale",name) == 0)
    {
    	Mle3dNonuniformScaleProperty scale = ((SpinnerActor *)object)->getScaleProperty();
        *((Mle3dNonuniformScaleProperty *)value) = scale;
    } else if (strcmp("model",name) == 0)
    {
    	Mle3dModelProperty model = ((SpinnerActor *)object)->getModelProperty();
        *((Mle3dModelProperty *)value) = model;
    } else if (strcmp("texture",name) == 0)
    {
    	Mle3dTextureMapProperty texture = ((SpinnerActor *)object)->getTextureProperty();
        *((Mle3dTextureMapProperty *)value) = texture;
    } else if (strcmp("colorMap",name) == 0)
    {
    	Mle3dColorMapProperty cmap = ((SpinnerActor *)object)->getColorMapProperty();
        *((Mle3dColorMapProperty *)value) = cmap;
    } else
    {
        // TBD: log warning.
        cout << "***** ERROR: Unknown SpinnerActor property: " << name << endl;
    }
}

void
SpinnerActor::setProperty(MleObject *object, const char *name, unsigned char *value)
{
#if defined(HAVE_LOG4CXX)
	LOG4CXX_DEBUG(g_spinnerLogger, "Setting SpinnerActor property " << name << ".");
#else
    cout << "Setting SpinnerActor property " << name << "." << endl;
#endif
    if (strcmp("position",name) == 0)
    {
    	((SpinnerActor *)object)->setPositionProperty(*((Mle3dTranslationProperty *)value));
    } else if (strcmp("orientation",name) == 0)
    {
    	((SpinnerActor *)object)->setOrientationProperty(*((Mle3dQuaternionRotationProperty *)value));
    } else if (strcmp("scale",name) == 0)
    {
    	((SpinnerActor *)object)->setScaleProperty(*((Mle3dNonuniformScaleProperty *)value));
    } else if (strcmp("model",name) == 0)
    {
    	((SpinnerActor *)object)->setModelProperty(*((Mle3dModelProperty *)value));
    } else if (strcmp("texture",name) == 0)
    {
    	((SpinnerActor *)object)->setTextureProperty(*((Mle3dTextureMapProperty *)value));
    } else if (strcmp("colorMap",name) == 0)
    {
    	((SpinnerActor *)object)->setColorMapProperty(*((Mle3dColorMapProperty *)value));
    } else {
        // TBD: log warning.
        cout << "***** ERROR: Unknown SpinnerActor property: " << name << endl;
    }
}
