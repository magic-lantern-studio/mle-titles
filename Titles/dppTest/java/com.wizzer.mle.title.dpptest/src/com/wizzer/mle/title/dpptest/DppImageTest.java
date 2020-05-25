/*
 * DppImageTest.java
 * Created on Feb 28, 2005
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
import java.awt.Color;
import java.util.Vector;

// Import Magic Lantern Runtime Engine classes.
import com.wizzer.mle.runtime.MleTitle;
import com.wizzer.mle.runtime.core.MleRuntimeException;
import com.wizzer.mle.runtime.dpp.MleDppException;
import com.wizzer.mle.runtime.dpp.MleDppLoader;
import com.wizzer.mle.runtime.dpp.MleDppUtil;
import com.wizzer.mle.runtime.event.MleEventDispatcher;
import com.wizzer.mle.runtime.event.MleEventManager;
import com.wizzer.mle.runtime.scheduler.MlePhase;
import com.wizzer.mle.runtime.scheduler.MleScheduler;

// Import Magic Lantern J2D Parts classes.
import com.wizzer.mle.parts.MleShutdownCallback;
import com.wizzer.mle.parts.j2d.MleJ2dPlatformData;
import com.wizzer.mle.parts.stages.Mle2dStage;
import com.wizzer.mle.parts.actors.MleImageActor;

// Import title generated classes.
import gen.MleRuntimeTables;
import gen.ActorID;
import gen.DppTOC;

/**
 * This test displays an image using the Magic Lantern Runtime
 * Engine and the Java2d target library.
 * <p>
 * The elements of the title are loaded from a mastered Digital
 * Playprint.
 * </p>
 *
 * @author Mark S. Millard
 */
public class DppImageTest
{
    // The number of phases in the scheduler.
    private static int NUM_PHASES = 6;
    
    // The parts registry.
    TitleRegistry m_partsRegistry = null;
    
    // The width of the platform Stage.
    private static int m_width = 640;
    // The height of the Image to display.
    private static int m_height = 480;
    
    // Container for title specific data.
    private MleTitle m_title = null;
    // The usage string.
    private String m_usage = "usage: DppImageTest <file>";

    /**
     * The default constructor.
     */
    public DppImageTest()
    {
        super();
        
        // Get a reference to the global title container.
        m_title  = MleTitle.getInstance();
        
        // Initialize the title specific data.
        m_title.m_titleData = new DppImageTestData();
        ((DppImageTestData)(m_title.m_titleData)).m_tables = new MleRuntimeTables();
        ((DppImageTestData)(m_title.m_titleData)).m_toc = new DppTOC();
    }
    
    /**
     * Initialize the title environment.
     */
    public void init()
    {
        // Initialize the platform specific data.
        MleJ2dPlatformData platformData = new MleJ2dPlatformData();
        platformData.m_width = m_width;
        platformData.m_height = m_height;
        m_title.m_platformData = platformData;
        
        // Initialize the title registry of parts. The registry
        // will add itself as an Observer to the MleTables class
        // so that it will be notified when an Actor has been loaded
        // from the Digital Playprint.
        m_partsRegistry = TitleRegistry.getInstance();

        // Load the Digital Playprint. The name of the playprint is extracted
        // from the title specific data Object. The DPP should be in the
        // Big Endian format for titles written in Java.
        m_title.m_theDpp = MleDppLoader.getInstance().mleLoadPlayprint(
            ((DppImageTestData)(m_title.m_titleData)).m_playprint,
            MleDppUtil.MLE_DPP_FINDPPBE);
        
        // Create the event dispatcher.
        MleEventDispatcher manager = new MleEventDispatcher();
        m_title.m_theDispatcher = manager;
        
        //  Create the scheduler.
        MleScheduler scheduler = new MleScheduler(NUM_PHASES);
        MleTitle.g_theActorPhase = new MlePhase("Actor Phase");
        scheduler.addPhase(MleTitle.g_theActorPhase);
        MleTitle.g_thePostActorPhase = new MlePhase("Post Actor Phase");
        scheduler.addPhase(MleTitle.g_thePostActorPhase);
        MleTitle.g_thePreRolePhase = new MlePhase("Pre Role Phase");
        scheduler.addPhase(MleTitle.g_thePreRolePhase);
        MleTitle.g_theRolePhase = new MlePhase("Role Phase");
        scheduler.addPhase(MleTitle.g_theRolePhase);
        MleTitle.g_theSetPhase = new MlePhase("Set Phase");
        scheduler.addPhase(MleTitle.g_theSetPhase);
        MleTitle.g_theStagePhase = new MlePhase("Stage Phase");
        scheduler.addPhase(MleTitle.g_theStagePhase);
        m_title.m_theScheduler = scheduler;
        
        // Initialize the exit status.
        MleEventManager.setExitStatus(false);
        
        // Create and initialize the Stage.
        try
        {
	        Mle2dStage theStage = new Mle2dStage();
	        theStage.init();
	        theStage.setBackgroundColor(Color.white);
        } catch (MleRuntimeException ex)
        {
            System.out.println("ImageTest: Unable to create and initialize the Stage.");
            System.exit(-1);
        }
        
        // Load the first Scene.
        try
        {
            MleDppLoader.getInstance().mleLoadBootScene();
        } catch (MleDppException ex)
        {
            System.out.println("DppImageTest: Unable to load Boot Scene.");
            System.out.println(ex.getMessage());
            System.exit(-1);
        } catch (MleRuntimeException ex)
        {
            System.out.println("DppImageTest: Unable to load Boot Scene.");
            System.out.println(ex.getMessage());
            System.exit(-1);
        }
        
        // Resize the Stage based on the size of the image. We get the instance of
        // the actor from the Actor registry that was created when the Boot Scene
        // was loaded.
        Vector actors = m_partsRegistry.getActorRegistry();
        int width = ((MleImageActor)(actors.elementAt(ActorID.MleDPPActor_a0))).getWidth();
        int height = ((MleImageActor)(actors.elementAt(ActorID.MleDPPActor_a0))).getHeight();
        ((Mle2dStage)Mle2dStage.getInstance()).sizeTo(width,height);
 
    }

    /**
     * The main loop of execution.
     */
    public void mainloop()
    {
        while (! MleEventManager.okToExit())
        {
            // Process delayed events.
            m_title.m_theDispatcher.dispatchEvents();
        
            // Run the scheduled phases.
            m_title.m_theScheduler.run();
        }
    }
    
    // Parse the command line arguments.
    private boolean parseArgs(String[] args)
    {
        boolean retValue = false;
        
        if ((args != null) && (args.length == 1))
        {
            // Set the name of the DPP file.
            ((DppImageTestData)m_title.m_titleData).m_playprint = args[0];
            retValue = true;
        }
        
        return retValue;
    }

    /**
     * The main entry point for running the image test Magic
     * Lantern title.
     * 
     * @param args Command line arguments.
     */
    public static void main(String[] args)
    {
        // Create and initialize the title.
        DppImageTest title = new DppImageTest();
        
        // Parse the command line arugments.
        if (! title.parseArgs(args))
        {
            System.out.println(title.m_usage);
            System.exit(-1);
        }
        
        // Initialize the title.
        title.init();
        
        // Install a callback for exiting the title cleanly.
        try
        {
            MleTitle.getInstance().m_theDispatcher.installEventCB(
                    MleEventManager.MLE_QUIT,new MleShutdownCallback(),null);
        } catch (MleRuntimeException ex)
        {
            System.out.println("DppImageTest: Unable to install shutdown callback.");
            System.exit(-1);            
        }
        
        // Begin main loop execution.
        title.mainloop();
        
        // Clean up
    }
}
