/** @defgroup mtea Magic Lantern mtea Title */

/**
 * @file spinnera.h
 * @ingroup mtea
 *
 * This file declares the SpinnerActor class for the mtea title.
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


#ifndef __SPINNER_A_H_
#define __SPINNER_A_H_

// Use position and orientation members; uncomment to use transform property.
#define POSORI

// Include Magic Lantern Runtime Engine header files.
#include "mle/MleActor.h"

// Include Magic Lantern Extension header files.
#include "mle/3dmodelp.h"
#include "mle/3dcomapp.h"
#include "mle/3dtexmpp.h"
#include "mle/3dtranlp.h"
#include "mle/3dqrotp.h"
#include "mle/3dnscalp.h"

#include "SpinnerActor.h"


class SPINNERACTOR_API SpinnerActor : public MleActor
{
    MLE_ACTOR_HEADER(SpinnerActor);

  public:

	SpinnerActor();

	~SpinnerActor();

	void init();

	void update();

	void resolveEdit(const char *property);

	static void behave(SpinnerActor* spinner);
  
	// The member properties.
	Mle3dTranslationProperty        position;
	Mle3dQuaternionRotationProperty orientation;
	Mle3dNonuniformScaleProperty    scale;
	Mle3dModelProperty              model;
	Mle3dTextureMapProperty         texture;
	Mle3dColorMapProperty           colorMap;

};


#endif /* __SPINNER_A_H_ */ 
