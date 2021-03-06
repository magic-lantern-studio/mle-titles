/** @defgroup mtea Magic Lantern mtea Title */

/**
 * @file texture.cxx
 * @ingroup mtea
 *
 * This file implements texture utilities for the mtea title.
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

