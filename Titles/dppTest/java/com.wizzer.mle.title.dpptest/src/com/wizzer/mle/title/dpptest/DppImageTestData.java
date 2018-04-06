/*
 * DppImageTestData.java
 * Created on Mar 1, 2005
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

// Declare package.
package com.wizzer.mle.title.dpptest;

// Import generated title classes.
import gen.MleRuntimeTables;
import gen.DppTOC;

/**
 * Data specific to the DppImageTest title.
 * 
 * @author Mark S. Millard
 */
public class DppImageTestData
{
    /** The name of the Digital Playprint to load. */
    public String m_playprint = null;
    /** The Runtime Engine tables. */
    public MleRuntimeTables m_tables = null;
    /** The DPP Table-of-Contents. */
    public DppTOC m_toc = null;

    /**
     * The default constructor.
     */
    public DppImageTestData()
    {
        super();
    }

}
