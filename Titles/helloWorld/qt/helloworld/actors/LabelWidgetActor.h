/** @defgroup HelloWorldTitle Magic Lantern HelloWorld Title */

/**
 * @file LabelWidgetActor.h
 * @ingroup HelloWorldTitle
 *
 * This file defines the LabelWidgetActor for the HelloWorld title.
 *
 * @author Mark S. Millard
 * @date February 5, 2018
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2018 Wizzer Works
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

#ifndef __LABELWIDGETACTOR_H_
#define __LABELWIDGETACTOR_H_

// Include Magic Lantern header files.
#include "mle/mlTypes.h"
#include "mle/mlMalloc.h"
#include "math/vector.h"
#include "mle/MleActor.h"

// Include Title header files.
#include "WidgetActor.h"

class WIDGETACTOR_API LabelWidgetActor : public MleActor
{
    MLE_ACTOR_HEADER(LabelWidgetActor);

  public:

    static void getProperty(MleObject *object, const char *name, unsigned char **value); // value is an output parameter.
    static void setProperty(MleObject *object, const char *name, unsigned char *value); // value is an input parameter.

    // Property declarations.
    // <b>id</b> property is a widget identifier string.
    MLE_ACTOR_DYNAMIC_PROPERTY(char *, id, getIdProperty, setIdProperty)
    // <b>position</b> property contains x and y positions relative to
    // the corresponding set's coordinate system.  (0, 0) corresponds
    // to the lower left corner (origin of the corresponding set).
    MLE_ACTOR_PROPERTY(MlVector2, position, getPositionProperty, setPositionProperty)
    // <b>text</b> property is the widget's label.
    MLE_ACTOR_DYNAMIC_PROPERTY(char *, text, getTextProperty, setTextProperty)

    // Construct a label widget actor.
    LabelWidgetActor(void);

    // Destruct a label widget actor.
    virtual ~LabelWidgetActor(void);

    // Initialize the actor and push initial property values to the role.
    virtual void init(void);

#ifdef MLE_REHEARSAL
    // Tools can change property values directly in actor memory.  This
    // function can be used to propagate the changes to its role
    // to make its states consistent.
    virtual void resolveEdit(const char *property);
#endif  /* MLE_REHEARSAL */

    // Set the widget identifier.
    virtual void setId(char *str);

    // Set the current position.
    virtual void setPosition(MlVector2 &pos);

    // Set the label text.
    virtual void setText(char *str);
};

#endif /* __LABELWIDGETACTOR_H_ */
