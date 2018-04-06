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
//  Copyright (C) 2000-2007  Wizzer Works
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

// Include Magic Lantern Runtime Engine header files.
#include "mle/MleScheduler.h"
#include "mle/MleDirector.h"

// Include Magic Lantern Extension header files.
#include "math/vector.h"
#include "math/rotation.h"

// Include title header files.
#include "spinnera.h"


MLE_ACTOR_SOURCE(SpinnerActor,MleActor);


SpinnerActor::SpinnerActor()
{ 
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
