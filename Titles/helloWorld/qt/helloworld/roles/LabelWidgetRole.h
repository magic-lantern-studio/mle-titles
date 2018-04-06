/** @defgroup HelloWorldTitle Magic Lantern HelloWorld Title */

/**
 * @file LabelWidgetRole.h
 * @ingroup HelloWorldTitle
 *
 * This file defines the LabelWidgetRole for the HelloWorld title.
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

#ifndef __LABELWIDGETROLE_H_
#define __LABELWIDGETROLE_H_

// Include Qt header files.
#include <QPixmap>
#include <QPainter>

// Include Magic Lantern header files.
#include "mle/mlTypes.h"
#include "math/vector.h"
#include "mle/2drole.h"

// Include Title header files.
#include "WidgetRole.h"

// Declare external classes.
class MleActor;

class WIDGETROLE_API LabelWidgetRole : public Mle2dRole
{

    MLE_ROLE_HEADER(LabelWidgetRole);

  public:

    // Construct a label widget role.
    LabelWidgetRole(MleActor *actor);

    // Destruct a label widget role.
    virtual ~LabelWidgetRole(void);

    // Update the position where the label is drawn.  The position is
    // in screen coordinate and lower left is the label origin.
    void labelLocation(MlVector2 &pos);

    // Update the label text to render.
    void label(const char *str);

    // The render() function of the 2D Set calls this function to update
    // this role every cycle.
    virtual void draw(void *data);

  protected:

    // Label origin (lower left) in screen coordinate.
    MlVector2 m_labelPosition;

    // Label text;
    char *m_label;
};

#endif /* __LABELWIDGETROLE_H_ */
