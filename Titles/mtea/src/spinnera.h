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
// The MIT License (MIT)
//
// Copyright (c) 2003-2019 Wizzer Works
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


#ifndef __SPINNER_A_H_
#define __SPINNER_A_H_

// Use position and orientation members; uncomment to use transform property.
#define POSORI

// Include Magic Lantern Runtime Engine header files.
#include "mle/MleActor.h"

// Include Magic Lantern Extension header files.
#include "mle/propdef.h"
#include "mle/3dmodelp.h"
#include "mle/3dcomapp.h"
#include "mle/3dtexmpp.h"
#include "mle/3dtranlp.h"
#include "mle/3dqrotp.h"
#include "mle/3dnscalp.h"

// Include Actor's header files.
#include "SpinnerActor.h"

#if defined(__linux__)
#if defined(HAVE_LOG4CXX)
#include "log4cxx/logger.h"

using namespace log4cxx;
extern LoggerPtr g_spinnerLogger;;
#endif /* HAVE_LOG4CXX */
#endif

class SPINNERACTOR_API SpinnerActor : public MleActor
{
    MLE_ACTOR_HEADER(SpinnerActor);

  public:

    static void getProperty(MleObject *object, const char *name, unsigned char **value); // value is an output parameter.
    static void setProperty(MleObject *object, const char *name, unsigned char *value);  // value is an input parameter.

    // Property declarations.
    MLE_ACTOR_PROPERTY(Mle3dTranslationProperty, position, getPositionProperty, setPositionProperty)
    MLE_ACTOR_PROPERTY(Mle3dQuaternionRotationProperty, orientation, getOrientationProperty, setOrientationProperty)
	MLE_ACTOR_PROPERTY(Mle3dNonuniformScaleProperty, scale, getScaleProperty, setScaleProperty)
	MLE_ACTOR_PROPERTY(Mle3dModelProperty, model, getModelProperty, setModelProperty)
	MLE_ACTOR_PROPERTY(Mle3dTextureMapProperty, texture, getTextureProperty, setTextureProperty)
	MLE_ACTOR_PROPERTY(Mle3dColorMapProperty, colorMap, getColorMapProperty, setColorMapProperty)

	/**
	 * Default constructor.
	 */
	SpinnerActor();

	/**
	 * Destructor.
	 */
	~SpinnerActor();

	/**
	 * Initialize the SpinnerActor.
	 */
	void init();

	void update();

	void resolveEdit(const char *property);

	static void behave(SpinnerActor* spinner);
  
	// The member properties.
	//Mle3dTranslationProperty        position;
	//Mle3dQuaternionRotationProperty orientation;
	//Mle3dNonuniformScaleProperty    scale;
	//Mle3dModelProperty              model;
	//Mle3dTextureMapProperty         texture;
	//Mle3dColorMapProperty           colorMap;

};


#endif /* __SPINNER_A_H_ */ 
