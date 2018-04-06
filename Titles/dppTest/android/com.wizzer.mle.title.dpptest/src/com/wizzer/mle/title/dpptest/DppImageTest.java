// Declare package.
package com.wizzer.mle.title.dpptest;

// Import standard Java classes.
import java.io.InputStream;

// Import Android classes.
import android.app.Activity;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;

// Import Magic Lantern classes.
import com.wizzer.mle.parts.MleShutdownCallback;
import com.wizzer.mle.parts.j2d.MleJ2dPlatformData;
import com.wizzer.mle.parts.stages.Mle2dStage;
import com.wizzer.mle.runtime.MleTitle;
import com.wizzer.mle.runtime.ResourceManager;
import com.wizzer.mle.runtime.core.MleInputStream;
import com.wizzer.mle.runtime.core.MleRuntimeException;
import com.wizzer.mle.runtime.dpp.MleDppException;
import com.wizzer.mle.runtime.dpp.MleDppLoader;
import com.wizzer.mle.runtime.dpp.MleDppUtil;
import com.wizzer.mle.runtime.event.MleEventDispatcher;
import com.wizzer.mle.runtime.event.MleEventManager;
import com.wizzer.mle.runtime.scheduler.MlePhase;
import com.wizzer.mle.runtime.scheduler.MleScheduler;
import com.wizzer.mle.title.dpptest.R;

//Import DppImageTest classes.
import gen.ActorID;
import gen.DppTOC;
import gen.MleRuntimeTables;

/**
 * This Activity is used to test the Magic Lantern Runtime Engine using
 * a Digital Playprint.
 * 
 * @author Mark S. Millard
 */
public class DppImageTest extends Activity
{
    // The number of phases in the scheduler.
    private static int NUM_PHASES = 6;
    
    // The width of the Image to display.
    private static int m_width = 320;
    // The height of the Image to display.
    private static int m_height = 480;

    // The parts registry.
    TitleRegistry m_partsRegistry = null;
    
    // Container for title specific data.
    private MleTitle m_title = null;
    // The name of the DPP file to load.
    private String m_filename = null;
    // Output tag for logging status messages.
    private static String DEBUG_TAG = "Magic Lantern Digital Playprint Image Test";

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
        	// Retrieve the name of the DDP file.
            m_filename = resources.getString(R.string.dpp_filename);

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
        
        // Get a reference to the global title container.
        m_title  = MleTitle.getInstance();
        
        // Parse the application resources.
        if (! parseResources(getResources()))
        {
        	Log.e(DppImageTest.DEBUG_TAG, "Unable to parse title resources.");
            System.exit(-1);
        }
        
        // Initialize the title specific data.
        m_title.m_titleData = new DppImageTestData();
        ((DppImageTestData)(m_title.m_titleData)).m_tables = new MleRuntimeTables();
        ((DppImageTestData)(m_title.m_titleData)).m_toc = new DppTOC();
        ((DppImageTestData)(m_title.m_titleData)).m_playprint = m_filename;
    }
    
    /**
     * Called after onCreate(Bundle) or onStop() when the current activity is now being displayed to the user.
     * It will be followed by onResume(). 
     */
    @Override
    public void onStart()
    {
    	super.onStart();

        // Initialize the title.
        init();

        // Install a callback for exiting the title cleanly.
        try
        {
            MleTitle.getInstance().m_theDispatcher.installEventCB(
                    MleEventManager.MLE_QUIT,new MleShutdownCallback(),null);
        } catch (MleRuntimeException ex)
        {
        	Log.e(DppImageTest.DEBUG_TAG, "Unable to install shutdown callback.");
            System.exit(-1);            
        }
        
        // Return to Android application life cycle.
    }
    
    /**
     * 
     */
    @Override
    public void onResume()
    {
    	super.onResume();

        // Begin main loop execution.
        Mainloop mainloop = new Mainloop();
        mainloop.start();
    }
    
    /**
     * Initialize the title environment.
     */
    private void init()
    {
        // Initialize the platform specific data.
        MleJ2dPlatformData platformData = new MleJ2dPlatformData();
        platformData.m_width = m_width;
        platformData.m_height = m_height;
        platformData.m_context = this;
        platformData.m_R = com.wizzer.mle.title.dpptest.R.class;
        m_title.m_platformData = platformData;
        
        // Initialize the title registry of parts. The registry
        // will add itself as an Observer to the MleTables class
        // so that it will be notified when an Actor has been loaded
        // from the Digital Playprint.
        m_partsRegistry = TitleRegistry.getInstance();

        // Load the Digital Playprint. The name of the playprint is extracted
        // from the title specific data Object. The DPP should be in the
        // Big Endian format for titles written in Java.
        String resourceName = m_filename.substring(0,
        	((DppImageTestData)(m_title.m_titleData)).m_playprint.lastIndexOf('.'));
        try
        {
        	// Validate that the resource, indicated by the playprint filename, exists.
        	// The id for the resource is extracted from the Android R.raw class using reflection
        	// The name of the id MUST match the value extracted from the playprint filename
        	// (e.g. if the expected id is R.raw.playprint, then the value of the playprint filename
        	//  should be playprint or playprint.dpp).
        	int id = ResourceManager.getResourceId(R.raw.class, resourceName);
        	
	        Resources resources = getResources();
	        InputStream in = resources.openRawResource(id);
	        m_title.m_theDpp = MleDppLoader.getInstance().mleLoadPlayprint(
	        	new MleInputStream(in), MleDppUtil.MLE_DPP_FINDPPBE);
	        if (m_title.m_theDpp == null)
	        {
	        	Log.e(DEBUG_TAG, "Unable to load Digital Playprint " + resourceName + ".");
	        	System.exit(-1);
	        }
        } catch (Resources.NotFoundException ex)
        {
        	Log.e(DEBUG_TAG, "Resource, " + resourceName + ", does not exist.");
            System.exit(-1);
        } catch (MleRuntimeException ex)
        {
        	Log.e(DEBUG_TAG, ex.getMessage());
        	System.exit(-1);   
        }        
        
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

	        // Set the Activity's View.
	        setContentView(theStage.m_windowView);

        } catch (MleRuntimeException ex)
        {
            Log.e(DEBUG_TAG, "Unable to create and initialize the Stage.");
            System.exit(-1);
        }
        
        // Load the first Scene.
        try
        {
            MleDppLoader.getInstance().mleLoadBootScene();
        } catch (MleDppException ex)
        {
        	Log.e(DEBUG_TAG, "Unable to load Boot Scene.");
        	Log.e(DEBUG_TAG, ex.getMessage());
            System.exit(-1);
        } catch (MleRuntimeException ex)
        {
        	Log.e(DEBUG_TAG, "Unable to load Boot Scene.");
            Log.e(DEBUG_TAG, ex.getMessage());
            System.exit(-1);
        }
        
        // Resize the Stage based on the size of the image. We get the instance of
        // the actor from the Actor registry that was created when the Boot Scene
        // was loaded.
        //Vector actors = m_partsRegistry.getActorRegistry();
        //int width = ((MleImageActor)(actors.elementAt(ActorID.MleDPPActor_a0))).getWidth();
        //int height = ((MleImageActor)(actors.elementAt(ActorID.MleDPPActor_a0))).getHeight();
        //((Mle2dStage)Mle2dStage.getInstance()).sizeTo(width,height);
 
    }

}