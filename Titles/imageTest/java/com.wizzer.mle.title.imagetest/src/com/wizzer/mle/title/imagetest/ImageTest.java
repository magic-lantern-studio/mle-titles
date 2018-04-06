/*
 * ImageTest.java
 * Created on Feb 17, 2005
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
package com.wizzer.mle.title.imagetest;

// Import standard Java classes.
import java.awt.Color;
import java.io.File;
import java.io.ByteArrayInputStream;

// Import Magic Lantern Runtime Engine classes.
import com.wizzer.mle.runtime.MleTitle;
import com.wizzer.mle.runtime.core.MleRuntimeException;
import com.wizzer.mle.runtime.core.MleSet;
import com.wizzer.mle.runtime.core.MleProp;
import com.wizzer.mle.runtime.event.MleEventDispatcher;
import com.wizzer.mle.runtime.event.MleEventManager;
import com.wizzer.mle.runtime.scheduler.MlePhase;
import com.wizzer.mle.runtime.scheduler.MleScheduler;

// Import Magic Lantern J2D Parts classes;
import com.wizzer.mle.parts.MleShutdownCallback;
import com.wizzer.mle.parts.j2d.MleJ2dPlatformData;
import com.wizzer.mle.parts.actors.MleImageActor;
import com.wizzer.mle.parts.roles.MleImageRole;
import com.wizzer.mle.parts.stages.Mle2dStage;
import com.wizzer.mle.parts.sets.Mle2dSet;

/**
 * This test displays an image using the Magic Lantern Runtime
 * Engine and the Java2d target library.
 * 
 * @author Mark S. Millard
 */
public class ImageTest
{
    // The number of phases in the scheduler.
    private static int NUM_PHASES = 6;
    
    // The width of the Image to display.
    private static int m_width = 640;
    // The height of the Image to display.
    private static int m_height = 480;
    
    // Container for title specific data.
    private MleTitle m_title = null;
    // The name of the image file to display.
    private String m_filename = null;
    // The usage string.
    private String m_usage = "usage: ImageTest <file>";
    
    protected static class Counter extends Thread
    {
        // The counter.
        private static int m_count = 0;
                
        /**
         * Get the current count.
         * 
         * @return The value of the counter is returned.
         */
        public int getCount()
        {
            return m_count;
        }
        
        /**
         * Update the counter at 1 second intervals.
         */
        public void run()
        {
            System.out.println("Executing Count Task: " + m_count);
            m_count++;
            try {
            	Thread.sleep(1000);
            } catch (InterruptedException ex)
            {
                System.out.println("Caught Interrupted Exception.");
            }
        }
    }
    
    /**
     * The default constructor.
     */
    public ImageTest()
    {
        super();
        
        // Get a reference to the global title container.
        m_title  = MleTitle.getInstance();
        
        // Initialize the platform specific data.
        MleJ2dPlatformData platformData = new MleJ2dPlatformData();
        platformData.m_width = m_width;
        platformData.m_height = m_height;
        m_title.m_platformData = platformData;
        
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
        
        MleEventManager.setExitStatus(false);
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
            
            // Exit after running 10 times = 10 seconds.
            //if (((Counter)m_title.m_titleData).getCount() == 10)
            //	m_exitOk = true;
        }
    }
    
    // Parse the command line arguments.
    private boolean parseArgs(String[] args)
    {
        boolean retValue = false;
        
        if ((args != null) && (args.length == 1))
        {
            m_filename = args[0];
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
        ImageTest title = new ImageTest();
        
        // Parse the command line arugments.
        if (! title.parseArgs(args))
        {
            System.out.println(title.m_usage);
            System.exit(-1);
        }
        
        //Counter counter = new Counter();
        //MleTitle.getInstance().m_titleData = counter;
        //MleTask count = new MleTask(counter);
        //MleTitle.g_theStagePhase.addTask(count);
        
        //MleTitle.getInstance().m_theScheduler.dump();
        
        // Create a Stage.
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
        
        // Create a Set. The image specified by the Actor will be
        // rendered onto this Set via the Role.
        try
        {
	        Mle2dSet imgSet = new Mle2dSet();
	        imgSet.init();
	        MleSet.setCurrentSet(imgSet);
        } catch (MleRuntimeException ex)
        {
            System.out.println("ImageTest: Unable to create and initialize the Set.");
            System.exit(-1);
        }

        // Create an image Actor.
        MleImageActor imgActor = new MleImageActor();
        
        // Initialize the Actor's properties. Note that this will usually be done
        // by loading a Group from a Digital Workprint (Rehearsal Player) or the
        // Digital Playprint (Target Player).
        File file = new File(title.m_filename);
        if (! file.exists())
        {
            System.out.println("ImageTest: File " + title.m_filename + " does not exist.");
            System.exit(-1);
        }

        try
        {
            int length = title.m_filename.length();
            byte[] buffer = title.m_filename.getBytes();
            ByteArrayInputStream input = new ByteArrayInputStream(buffer);
            
            MleProp property = new MleProp(length,input);
            imgActor.setProperty("filename",property);
        } catch (MleRuntimeException ex)
        {
            System.out.println("ImageTest: Unable to set property 'filename'.");
            System.exit(-1);
        }
        
        // Create an image Role. This constructor will attach the Role to
        // the specified Actor. It will also be associated with the current Set.
        MleImageRole imgRole = new MleImageRole(imgActor);
        imgRole.init();

        // Atttach the Role to the Set.
        try
        {
            ((Mle2dSet)MleSet.getCurrentSet()).attachRoles(null,imgRole);
        } catch (MleRuntimeException ex)
        {
            System.out.println("ImageTest: Unable to bind Role to Set.");
            System.exit(-1);            
        }
        
        // Initialize the Actor after it has been properly bound to the Role.
        try
        {
            imgActor.init();
        } catch (MleRuntimeException ex)
        {
            System.out.println("ImageTest: Unable to initialize Actor.");
            System.exit(-1);            
        }
        
        // Resize the Stage based on the size of the image.
        float[] min = new float[2];
        float[] max = new float[2];
        imgRole.getBounds(min,max);
        int width = (int)(max[0] - min[0]);
        int height = (int)(max[1] - min[1]);
        ((Mle2dStage)Mle2dStage.getInstance()).sizeTo(width,height);
        
        // Install a callback for exiting the title cleanly.
        try
        {
            MleTitle.getInstance().m_theDispatcher.installEventCB(
                    MleEventManager.MLE_QUIT,new MleShutdownCallback(),null);
        } catch (MleRuntimeException ex)
        {
            System.out.println("ImageTest: Unable to install shutdown callback.");
            System.exit(-1);            
        }
        
        // Begin main loop execution.
        title.mainloop();
        
        // Clean up
    }
}
