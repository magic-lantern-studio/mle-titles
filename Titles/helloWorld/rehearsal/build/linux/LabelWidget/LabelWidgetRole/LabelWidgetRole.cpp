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

#include <string.h>
//#include <qdebug.h>

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"
#include "mle/MleActor.h"
#include "mle/MleRole.h"

// Include HelloWorld header files.
#include "LabelWidgetActor.h"
#include "LabelWidgetRole.h"

MLE_ROLE_SOURCE(LabelWidgetRole, Mle2dRole)


LabelWidgetRole::LabelWidgetRole(MleActor *actor)
 : Mle2dRole(actor)
{
    m_labelPosition.setValue(ML_SCALAR(0), ML_SCALAR(0));
    m_label = NULL;
}

LabelWidgetRole::~LabelWidgetRole(void)
{
    if (m_label != NULL) mlFree(m_label);
}

void
LabelWidgetRole::labelLocation(MlVector2 &pos)
{
    m_labelPosition.setValue(pos.getValue());
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
}

void
LabelWidgetRole::draw(void *data)
{
    //qDebug() << "LabelWidgetRole: rendering label.";

    if (data != NULL)
    {
        // 'data' should be a reference to a Set's offscreen buffer.
        // Draw the the label into the Set's offscreen buffer.
/*
        QPixmap *buffer = (QPixmap *) data;
        QPainter painter(buffer);
        int x = m_labelPosition[0];
        int y = m_labelPosition[1];

        // Set pen attributes.
        QPen colorStyle;
        colorStyle.setStyle(Qt::SolidLine);
        colorStyle.setWidth(2);
        colorStyle.setColor(QColor(255, 0, 0)); // red, no transparency
        painter.setPen(colorStyle);

        // Set font attributes.
        QFont font = painter.font() ;
        font.setPointSize(18);
        painter.setFont(font);

        // Render the text.
        if (m_label != NULL)
            painter.drawText(QPoint(x, y), m_label);
*/
    }
}
