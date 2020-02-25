/** @defgroup HelloWorldTitle Magic Lantern HelloWorld Title */

/**
 * @file LabelWidgetActor.cpp
 * @ingroup HelloWorldTitle
 *
 * This file implements the LabelWidgetActor for the HelloWorld title.
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

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"
#include "mle/MleRole.h"

// Include HelloWorld header files.
#include "LabelWidgetActor.h"

using namespace std;

MLE_ACTOR_SOURCE(LabelWidgetActor, MleActor)

#ifdef MLE_REHEARSAL
void
LabelWidgetActor::initClass(void)
{
    mleRegisterActorClass(LabelWidgetActor, MleActor);

    mleRegisterActorMember(LabelWidgetActor, id, string);
    mleRegisterActorMember(LabelWidgetActor, position, MlVector2);
    mleRegisterActorMember(LabelWidgetActor, text, string);

    // Mark all the properties that belongs to the "transform" property
    // data set.
    mleRegisterActorMemberDataset(LabelWidgetActor, position, MLE_PROP_DATASET_TRANSFORM);
}
#endif /* MLE_REHEARSAL */

LabelWidgetActor::LabelWidgetActor(void)
 : MleActor()
{
    // Set default property values.
    id = (char *) mlMalloc(sizeof(char) * 13);
    strcpy(id, "Label Widget");
    position.setValue(ML_SCALAR(0), ML_SCALAR(0));
    text = (char *) mlMalloc(sizeof(char) * 11);
    strcpy(text, "Text Label");
}

LabelWidgetActor::~LabelWidgetActor(void)
{
    if (id != NULL) mlFree(id);
    if (text != NULL) mlFree(text);
}

void
LabelWidgetActor::init()
{
	MleRole *role = getRole();

	// Push initial data got from the workprint to the role.
	role->setAttribute("position", (void *)&position);
	role->setAttribute("label", (void *)text);
}

#ifdef MLE_REHEARSAL
void
LabelWidgetActor::resolveEdit(const char *property)
{
	MleRole *role = getRole();

	if (! property || strcmp(property, "position") == 0)
	    role->setAttribute("position", (void *)&position);
	else if(strcmp(property, "text") == 0)
	    role->setAttribute("label", (void *)text);


}
#endif /* MLE_REHEARSAL */

void
LabelWidgetActor::setId(char *str)
{
    size_t size = strlen((const char *)str) + 1;
    setIdProperty(str,size);
    // Note that role does not have an id, so there is nothing to push.
}

void
LabelWidgetActor::setPosition(MlVector2 &pos)
{
	MleRole *role = getRole();

	// Update position property and push the update to the role.
	position.setValue(pos.getValue());
	role->setAttribute("position", (void *)&position);
}

void
LabelWidgetActor::setText(char *str)
{
	MleRole *role = getRole();

	// Update text property and push the update to the role.
    if (text != NULL) mlFree(text);
    text = (char *) mlMalloc(strlen(str) + 1);
    strcpy(text, str);
    role->setAttribute("label", (void *)text);
}

void
LabelWidgetActor:: getProperty(MleObject *object, const char *name, unsigned char **value)
{
    cout << "Getting LabelWidgetActor property " << name << "." << endl;
    if (strcmp("id",name) == 0)
    {
        const char *id = ((LabelWidgetActor *)object)->getIdProperty();
        *value = (unsigned char *)id;
    } else if (strcmp("text",name) == 0)
    {
        const char *text = ((LabelWidgetActor *)object)->getTextProperty();
        *value = (unsigned char *)text;
    } else if (strcmp("position",name) == 0)
    {
        MlVector2 position = ((LabelWidgetActor *)object)->getPositionProperty();
        *((MlVector2 *)value) = position;
    } else
    {
        // TBD: log warning.
        cout << "***** ERROR: Unknown LabelWidgetActor property: " << name << endl;
    }
}

void
LabelWidgetActor::setProperty(MleObject *object, const char *name, unsigned char *value)
{
    cout << "Setting LabelWidgetActor property " << name << "." << endl;
    if (strcmp("id",name) == 0)
    {
        size_t size = strlen((const char *)value) + 1;
        ((LabelWidgetActor *)object)->setIdProperty((const char *)value,size);
    } else if (strcmp("text",name) == 0)
    {
        size_t size = strlen((const char *)value) + 1;
        ((LabelWidgetActor *)object)->setTextProperty((const char *)value,size);
    } else if (strcmp("position",name) == 0)
    {
       ((LabelWidgetActor *)object)->setPositionProperty(*((MlVector2 *)value));
    } else {
        // TBD: log warning.
        cout << "***** ERROR: Unknown LabelWidgetActor property: " << name << endl;
    }
}
