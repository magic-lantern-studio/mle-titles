/** @defgroup HelloWorldTitle Magic Lantern HelloWorld Title */

/**
 * @file LabelWidgetRole.cpp
 * @ingroup HelloWorldTitle
 *
 * This file implements the LabelWidgetRole for the HelloWorld title.
 *
 * @author Mark S. Millard
 * @date February 5, 2018
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2018-2020 Wizzer Works
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
#include <string.h>

// Include Inventor header files.
#include <Inventor/nodes/SoFont.h>

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"
#include "mle/MleActor.h"
#include "mle/MleRole.h"
#include "mle/MleStage.h"

// Include HelloWorld header files.
#include "LabelWidgetActor.h"
#include "LabelWidgetRole.h"

using namespace std;

MLE_ROLE_SOURCE(LabelWidgetRole, Mle3dRole)


LabelWidgetRole::LabelWidgetRole(MleActor *actor)
 : Mle3dRole(actor)
{
    m_labelPosition.setValue(ML_SCALAR(0), ML_SCALAR(0));
    m_label = NULL;

    // Specify the font.
    SoFont *font = new SoFont;
    font->name.setValue("Times-Roman");
    font->size.setValue(24.0);

    // Specify the location.
    _textTranslate = new SoTranslation;
    //textTranslate->translation.setValue(0.25, 0.0, 0.25);
   _textTranslate->translation.setValue(m_labelPosition[0], m_labelPosition[1], 0.25);
   _textTranslate->ref();

    // Initialize internal implementation of role.
    _label = new SoText2();
    _label->ref();
    _label->string = "Default Label";

    // Add label to scene graph.
    m_root->addChild(font);
    m_root->addChild(_textTranslate);
	m_root->addChild(_label);
}

LabelWidgetRole::~LabelWidgetRole(void)
{
    if (m_label != NULL) mlFree(m_label);
    // Note: unable to delete SoText2 because destructor is protected.
    //if (_label != NULL) delete _label;
    _textTranslate->unref();
    _label->unref();
}

void
LabelWidgetRole::labelLocation(MlVector2 &pos)
{
    m_labelPosition.setValue(pos.getValue());

    _textTranslate->translation.setValue(m_labelPosition[0], m_labelPosition[1], 0.25);
}

void
LabelWidgetRole::label(const char *str)
{
    // Remove old label.
    if (m_label != NULL) mlFree(m_label);
    // Apply new label.
    if (str != NULL) {
        m_label = (char *) mlMalloc(strlen(str) + 1);
        strcpy(m_label, str);
    } else
        m_label = NULL;

	_labelStr.setValue(m_label);
	_label->string = _labelStr;
}

void
LabelWidgetRole::draw(void *data)
{
	cout << "LabelWidgetRole: rendering label." << "\n";

    if (data != NULL)
    {
        // This widget is designed for an Inventor Mle2dSet. So the data
    	// argument should always be NULL.
    }
}

void
LabelWidgetRole::setAttribute(const char *name, void *value)
{
	if (! strcmp(name, "position")) {
		MlVector2 *position = (MlVector2 *)value;
		this->labelLocation(*position);
	} else if (! strcmp(name, "label")) {
		const char *str = (const char *)value;
		this->label(str);
	}
}

void *
LabelWidgetRole::getAttribute(const char *name)
{
	if (! strcmp(name, "position")) {
		return (void *)&m_labelPosition;
	} else if (! strcmp(name, "label")) {
		return (void *)m_label;
	} else {
	    return NULL;
	}
}
