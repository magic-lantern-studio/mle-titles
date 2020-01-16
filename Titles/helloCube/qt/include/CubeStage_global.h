/** @defgroup HelloCubeTitle Magic Lantern Parts */

/**
 * @file CubeStage_global.h
 * @ingroup HelloCubeTitle
 *
 * This file defines the Cube Stage global support.
 *
 * @author Mark S. Millard
 * @date January 14, 2020
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

#ifndef __MLE_CUBESTAGE_GLOBAL_H_
#define __MLE_CUBESTAGE_GLOBAL_H_

// Include Qt header files.
#include <QtCore/qglobal.h>

// Include Magic Lantern header files
#include "mle/MleEvent.h"

#if defined(CUBESTAGE_LIBRARY)
#  define CUBESTAGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CUBESTAGESHARED_EXPORT Q_DECL_IMPORT
#endif

extern CUBESTAGESHARED_EXPORT MleEvent QT_RESIZE_EVENT;
extern CUBESTAGESHARED_EXPORT MleEvent QT_CLOSE_EVENT;
extern CUBESTAGESHARED_EXPORT MleEvent QT_EXPOSE_EVENT;
extern CUBESTAGESHARED_EXPORT MleEvent QT_MOUSE_EVENT;
extern CUBESTAGESHARED_EXPORT MleEvent QT_PAINT_EVENT;

#define MLE_RESIZE_STAGE_PRIORITY       10
#define MLE_RESIZE_SET_PRIORITY          9
#define MLE_RESIZEPAINT_STAGE_PRIORITY  -1

class MleResizeEvent
{
  public:
    int m_width;
    int m_height;
};

#endif // __MLE_CUBESTAGE_GLOBAL_H_
