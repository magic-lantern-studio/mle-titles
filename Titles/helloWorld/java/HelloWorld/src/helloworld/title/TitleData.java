/*
 * TitleData.java
 * Created on Mar 28, 2006
 */

// COPYRIGHT_BEGIN
// COPYRIGHT_END

// Declare package.
package helloworld.title;

// Import generated title classes.
import gen.MleRuntimeTables;
import gen.DppTOC;

/**
 * Data specific to the title.
 * 
 * @author Wizzer Works
 */
public class TitleData
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
    public TitleData()
    {
        super();
    }

}
