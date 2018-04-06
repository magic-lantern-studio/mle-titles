/*
 * HelloWorld.java
 * Created on January 7, 2011
 */

// COPYRIGHT_BEGIN
// COPYRIGHT_END

// Declare package.
package helloworld.title;

// Import Magic Lantern Runtime Engine classes.
import com.wizzer.mle.runtime.MleTitle;
import com.wizzer.mle.runtime.core.MleRuntimeException;
import com.wizzer.mle.runtime.event.MleEventDispatcher;
import com.wizzer.mle.runtime.event.MleEventManager;
import com.wizzer.mle.runtime.scheduler.MlePhase;
import com.wizzer.mle.runtime.scheduler.MleScheduler;
import com.wizzer.mle.runtime.dpp.MleDppLoader;
import com.wizzer.mle.runtime.dpp.MleDppUtil;
import com.wizzer.mle.runtime.dpp.MleDppException;

// Import Magic Lantern J2D Parts classes.
import com.wizzer.mle.parts.MleShutdownCallback;
import com.wizzer.mle.parts.j2d.MleJ2dPlatformData;
import com.wizzer.mle.parts.stages.Mle2dStage;

// Import title generated classes.
import gen.MleRuntimeTables;
import gen.DppTOC;

/**
 * This title displays a stage using the Magic Lantern Runtime
 * Engine and the Java2d target library. The string "Hello World!"
 * is displayed using the Label actor.
 * <p>
 * The elements of the title are loaded from a mastered Digital
 * Playprint.
 * </p>
 *
 * @author Wizzer Works
 */
public class HelloWorld
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
    private String m_usage = "usage: HelloWorld <file>";

    /**
     * The default constructor.
     */
    public HelloWorld()
    {
        super();
        
        // Get a reference to the global title container.
        m_title  = MleTitle.getInstance();
        
        // Initialize the title specific data.
        m_title.m_titleData = new TitleData();
        ((TitleData)(m_title.m_titleData)).m_tables = new MleRuntimeTables();
        ((TitleData)(m_title.m_titleData)).m_toc = new DppTOC();
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
            ((TitleData)(m_title.m_titleData)).m_playprint,
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
        } catch (MleRuntimeException ex)
        {
            System.out.println("Simple: Unable to create and initialize the Stage.");
            System.exit(-1);
        }
        
        // Load the first Scene.
        try
        {
            MleDppLoader.getInstance().mleLoadBootScene();
        } catch (MleDppException ex)
        {
            System.out.println("Simple: Unable to load Boot Scene.");
            System.out.println(ex.getMessage());
            System.exit(-1);
        } catch (MleRuntimeException ex)
        {
            System.out.println("Simple: Unable to load Boot Scene.");
            System.out.println(ex.getMessage());
            System.exit(-1);
        }

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
            ((TitleData)m_title.m_titleData).m_playprint = args[0];
            retValue = true;
        }
        
        return retValue;
    }

    /**
     * The main entry point for running the Simple Magic
     * Lantern title.
     * 
     * @param args Command line arguments.
     */
    public static void main(String[] args)
    {
        // Create and initialize the title.
        HelloWorld title = new HelloWorld();
        
        // Parse the command line arguments.
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
            System.out.println("Simple: Unable to install shutdown callback.");
            System.exit(-1);            
        }
        
        // Begin main loop execution.
        title.mainloop();
        
        // Clean up
    }
}
