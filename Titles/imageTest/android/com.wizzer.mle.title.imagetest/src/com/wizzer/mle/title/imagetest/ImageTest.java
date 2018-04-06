// Declare package.
package com.wizzer.mle.title.imagetest;

// Import standard Java classes.
import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.io.IOException;

// Import Android classes.
import android.app.Activity;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;

//Import Magic Lantern Runtime Engine classes.
import com.wizzer.mle.runtime.MleTitle;
import com.wizzer.mle.runtime.ResourceManager;
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

public class ImageTest extends Activity
{
   // The number of phases in the scheduler.
    private static int NUM_PHASES = 6;
    
    // The width of the Image to display.
    private static int m_width = 320;
    // The height of the Image to display.
    private static int m_height = 480;
    
    // Container for title specific data.
    private MleTitle m_title = null;
    // The name of the image file to display.
    private String m_filename = null;
    // Output tag for logging status messages.
    private static String DEBUG_TAG = "Magic Lantern Image Test";
    
    /**
     * The main loop of execution.
     */
    protected class Mainloop extends Thread
    {
    	/**
    	 * Dispatch Magic Lantern events and process scheduled phases.
    	 * This will continue indefinitely until the application indicates
    	 * that it is Ok to exit via the <code>MleEventManager</code>.
    	 */
    	public void run()
    	{
	        while (! MleEventManager.okToExit())
	        {
	            // Process delayed events.
	            m_title.m_theDispatcher.dispatchEvents();
	        
	            // Run the scheduled phases.
	            m_title.m_theScheduler.run();
	            
                // Attempt to garbage collect.
	            System.gc();
	        }
    	}
    }
    
    // Parse the title resources.
    private boolean parseResources(Resources resources)
    {
        boolean retValue = false;
        
        if (resources != null)
        {
            m_filename = resources.getString(R.string.logo_filename);
            retValue = true;
        }
        
        return retValue;
    }

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle icicle)
    {
        super.onCreate(icicle);
        
        // Parse the application resources.
        if (! parseResources(getResources()))
        {
        	Log.e(ImageTest.DEBUG_TAG, "Unable to parse title resources.");
            System.exit(-1);
        }
        
        // Get a reference to the global title container.
        m_title  = MleTitle.getInstance();
        
        // Initialize the platform specific data.
        MleJ2dPlatformData platformData = new MleJ2dPlatformData();
        platformData.m_width = m_width;
        platformData.m_height = m_height;
        platformData.m_context = this;
        platformData.m_R = com.wizzer.mle.title.imagetest.R.class;
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
     
        // Create a Stage.
        try
        {
        	Mle2dStage theStage = new Mle2dStage();
	        theStage.init();
	        
	        // Set the Activity's View.
	        setContentView(theStage.m_windowView);
	        
        } catch (MleRuntimeException ex)
        {
        	Log.e(ImageTest.DEBUG_TAG, "Unable to create and initialize the Stage.");
            System.exit(-1);
        }
    }

    /**
     * Called after onCreate(Bundle) or onStop() when the current activity is now being displayed to the user.
     * It will be followed by onResume(). 
     */
    @Override
    public void onStart()
    {
    	super.onStart();
        
        // Create a Set. The image specified by the Actor will be
        // rendered onto this Set via the Role.
        try
        {
	        Mle2dSet imgSet = new Mle2dSet();
	        imgSet.init();
	        MleSet.setCurrentSet(imgSet);
        } catch (MleRuntimeException ex)
        {
        	Log.e(ImageTest.DEBUG_TAG, "Unable to create and initialize the Set.");
            System.exit(-1);
        }

        // Create an image Actor.
        MleImageActor imgActor = new MleImageActor();
        
        // Initialize the Actor's properties. Note that this will usually be done
        // by loading a Group from a Digital Workprint (Rehearsal Player) or the
        // Digital Playprint (Target Player).
        String resourceName = m_filename.substring(0, m_filename.lastIndexOf('.'));
        try
        {
        	// Validate that the resource, indicated by m_filename, exists.
        	// The id for the resource is extracted from the Android R.raw class using reflection
        	// The name of the id MUST match the value extracted from m_filename (e.g. if the expected
        	// id is R.raw.wwlogo, then the value of m_filename should be wwlogo or wwlogo.gif).
        	int id = ResourceManager.getResourceId(R.raw.class, resourceName);
        	
	        Resources resources = getResources();
	        InputStream in = resources.openRawResource(id);
	        in.close();
        } catch (Resources.NotFoundException ex)
        {
        	Log.e(ImageTest.DEBUG_TAG, "Resource, " + resourceName + ", does not exist.");
            System.exit(-1);
        } catch (IOException ex)
        {
        	Log.e(ImageTest.DEBUG_TAG, "Unable to access resource, " + resourceName + ", due to IO error.");
            System.exit(-1);        	
        } catch (MleRuntimeException ex)
        {
        	Log.e(ImageTest.DEBUG_TAG, ex.getMessage());
        	System.exit(-1);   
        }
        
        try
        {
        	// Use the resource name for the property since we will be pulling the image data
        	// out of the Resource cache.
            int length = resourceName.length();
            byte[] buffer = resourceName.getBytes();
            ByteArrayInputStream input = new ByteArrayInputStream(buffer);
            
            MleProp property = new MleProp(length,input);
            imgActor.setProperty("filename",property);
        } catch (MleRuntimeException ex)
        {
        	Log.e(ImageTest.DEBUG_TAG, "Unable to set property 'filename'.");
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
        	Log.e(ImageTest.DEBUG_TAG, "Unable to bind Role to Set.");
            System.exit(-1);            
        }
        
        // Initialize the Actor after it has been properly bound to the Role.
        try
        {
            imgActor.init();
        } catch (MleRuntimeException ex)
        {
        	Log.e(ImageTest.DEBUG_TAG, "Unable to initialize Actor.");
            System.exit(-1);            
        }
        
        // Resize the Stage based on the size of the image.
        //float[] min = new float[2];
        //float[] max = new float[2];
        //imgRole.getBounds(min,max);
        //int width = (int)(max[0] - min[0]);
        //int height = (int)(max[1] - min[1]);
        //((Mle2dStage)Mle2dStage.getInstance()).sizeTo(width,height);
        
        // Install a callback for exiting the title cleanly.
        try
        {
            MleTitle.getInstance().m_theDispatcher.installEventCB(
                    MleEventManager.MLE_QUIT,new MleShutdownCallback(),null);
        } catch (MleRuntimeException ex)
        {
        	Log.e(ImageTest.DEBUG_TAG, "Unable to install shutdown callback.");
            System.exit(-1);            
        }
        
        // Return to Android application life cycle.
    }
    
    @Override
    public void onRestart()
    {
    	super.onRestart();
    	Log.i(MleTitle.DEBUG_TAG, "Recieved onRestart().");
    }
    
    @Override
    public void onResume()
    {
    	super.onResume();
    	Log.i(MleTitle.DEBUG_TAG, "Recieved onResume().");

        // Begin main loop execution.
        Mainloop mainloop = new Mainloop();
        mainloop.start();
    }
      
    @Override
    public void onPause()
    {
    	super.onPause();
    	Log.i(MleTitle.DEBUG_TAG, "Recieved onPause().");
    	
    	// Stop the scheduler and event manager.
    	MleEventManager.setExitStatus(true);
    }
    
    @Override
    public void onStop()
    {
    	super.onStop();
    	Log.i(MleTitle.DEBUG_TAG, "Recieved onStop().");
    }
    
    @Override
    public void onDestroy()
    {
    	Log.i(MleTitle.DEBUG_TAG, "Recieved onDestory().");
    }
}