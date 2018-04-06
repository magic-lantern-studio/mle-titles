/*
 * TitleRegistry.java
 * Created on Mar 31, 2005
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

// Import standard Java classes.
import java.util.Observer;
import java.util.Observable;
import java.util.Vector;

// Import Magic Lantern Runtime Engine classes.
import com.wizzer.mle.runtime.core.MleActor;
import com.wizzer.mle.runtime.core.MleTables;
import com.wizzer.mle.runtime.core.MleRuntimeException;


/**
 * This class manages a registry of title elements (e.g. Actors).
 * 
 * @author Mark S. Millard
 */
public class TitleRegistry implements Observer
{
    // The Singleton instance of the title registry.
    private static TitleRegistry m_theRegistry = null;
    // The Actor registry.
    private Vector m_actorRegistry = null;
    
    // Hide the default constructor.
    private TitleRegistry()
    {
        super();
        
        // Create a container for the Actors in the title.
        m_actorRegistry = new Vector();
        
        // Add the registry as an Observer of the table manager.
        MleTables.getInstance().addObserver(this);
    }
    
    /**
     * Get the Singleton instance of the title registry.
     * 
     * @return A <code>TitleRegistry</code> is returned.
     */
    public static TitleRegistry getInstance()
    {
        if (m_theRegistry == null)
            m_theRegistry = new TitleRegistry();
        return m_theRegistry;
    }
    
    /**
     * Get the registry of Actors.
     * 
     * @return A <code>Vector</code> is returned containing the
     * Actors that have been registered for the title.
     */
    public Vector getActorRegistry()
    {
        return m_actorRegistry;
    }
    
    /**
     * Add an Actor to the title registry.
     * 
     * @param actor The Actor to add to the registry.
     * 
     * @return <b>true</b> will be returned if the Actor is successfully added
     * to the registry. Otherwise, <b>false</b> will be returned.
     * 
     * @throws MleRuntimeException This exception is thrown if the input argument
     * is <b>null</b>.
     */
    public boolean addActor(MleActor actor)
        throws MleRuntimeException
    {
        if (actor == null)
        {
            throw new MleRuntimeException("Unable to add Actor to title registry.");
        }
        
        return m_actorRegistry.add(actor);
    }

    /**
     * Remove an Actor from the title registry.
     * 
     * @param actor The Actor to remove from the registry.
     * 
     * @return <b>true</b> will be returned if the Actor is successfully removed
     * from the registry. Otherwise, <b>false</b> will be returned.
     * 
     * @throws MleRuntimeException This exception is thrown if the input argument
     * is <b>null</b>.
     */
    public boolean removeActor(MleActor actor)
        throws MleRuntimeException
    {
        if (actor == null)
        {
            throw new MleRuntimeException("Unable to remove Actor from title registry.");
        }
        
        return m_actorRegistry.remove(actor);
    }
    
    /**
     * Clear the title registry by removing all registered title
     * elements.
     */
    public void clear()
    {
        // Clear the Actor registry.
        m_actorRegistry.removeAllElements();
    }

    /**
     * This method is called whenever the observed object is changed.
     * <p>
     * If the Observable is the <code>MleTables</code> class and the Object is
     * an <code>MleActor</code>, then the Actor is added to the title registry.
     * </p>
     * 
     * @param obs The Observable object.
     * @param obj An argument passed by the notifyObservers method from the
     * Observable object.
     */
    public void update(Observable obs, Object obj)
    {
        if (obs instanceof MleTables)
        {
            if (obj instanceof MleActor)
                m_actorRegistry.add(obj);
        }
    }

}
