/** @defgroup mtea Magic Lantern mtea Title */

/**
 * @file texture.cxx
 * @ingroup mtea
 *
 * This file implements texture utilities for the mtea title.
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2000-2025 Wizzer Works
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

// Include Magic Lantern header files.
#include <mle/mlTypes.h>
#include <mle/mlMalloc.h>

// Include BRender target header files.
#include <mle/brendapi.h>

//
// In the mtea title, the updateMaterialRegistry function corrects the 
// map transform of the texture map so it is rendered right-side-up.
// This is necessary because Windows expects row 0 of its bitmaps to
// be the bottom row, whereas the SGI target uses the top row as row 0.
// Eventually, a converter will correct for this at media mastering time.
//
int  updateMaterialRegistry(void)
{
	br_material **materials;
	int	numFound;
	int numMat;

	numMat = BrMaterialCount("*");
	if (!numMat)
		return 0;

	materials = (br_material **)mlMalloc(sizeof(br_material *)*numMat);
	if (!materials)
		return 0;

	numFound = BrMaterialFindMany("*", materials, numMat);
	if (!numFound)
	{
		mlFree(materials);
		return 0;
	}

	for (int i = 0; i < numFound; i++)
	{
		if (materials[i]->colour_map)
		{
			// Correct the orientation of the texture map.
			materials[i]->map_transform.m[0][0] = BR_SCALAR(1);
			materials[i]->map_transform.m[0][1] = BR_SCALAR(0);
			materials[i]->map_transform.m[1][0] = BR_SCALAR(0);
			materials[i]->map_transform.m[1][1] = BR_SCALAR(-1);
			materials[i]->map_transform.m[2][0] = BR_SCALAR(0);
			materials[i]->map_transform.m[2][1] = BR_SCALAR(1);
			BrMaterialUpdate(materials[i], BR_MATU_ALL);
		}
	}

	mlFree(materials);
	return 1;
}

