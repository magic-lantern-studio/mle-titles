/*
 * LabelWidgetRole.java
 * Created on January 10, 2011
 */

// COPYRIGHT_BEGIN
// COPYRIGHT_END

// Declare package.
package helloworld.roles;

// Import standard Java classes.
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.font.FontRenderContext;
import java.awt.geom.Rectangle2D;

// Import Magic Lantern classes.
import com.wizzer.mle.parts.j2d.MleBufferedImage;
import com.wizzer.mle.parts.roles.Mle2dRole;

/**
 * This class is a role that is capable of rendering a text string on
 * a <code>Mle2dSet</code>.
 * 
 * @author Wizzer Works
 */
public class LabelWidgetRole extends Mle2dRole
{
	/** The text to display. */
	public String m_text = new String();
	/** The x position of the text. */
	public float m_x = 0;
	/** The y position of the text. */
	public float m_y = 0;

	/** The font. */
	protected Font m_font;
	/** The font color. */
	protected Color m_foregroundColor ;
	
	/**
	 * The default constructor.
	 */
	public LabelWidgetRole()
	{
		//System.out.println("Creating a LabelWidgetRole.");
		init();
	}

	/**
	 * Initialize the role.
	 * <p>
	 * This method is not yet called during construction via the Digital
	 * Playprint. That is why it is being called by the above constructor.
	 * </p>
	 */
	@Override
	public void init()
	{
		m_font = new Font("Serif", Font.PLAIN, 24);
		m_foregroundColor = Color.RED;
	}
	
	/**
	 * Set the text string that will be rendered by this widget.
	 * 
	 * @param text The text to display.
	 */
	public void setText(String text)
	{
		m_text = new String(text);
	}
	
	/**
	 * Set the position where the text string will be rendered.
	 * 
	 * @param x The x coordinate position, relative to the Set's
	 * coordinate space.
	 * @param y The y coordinate position, relative to the Set's
	 * coordinate space.
	 */
	public void setPosition(float x, float y)
	{
		m_x = x;
		m_y = y;
	}
	
	/**
	 * Render the role.
	 * 
	 * @param buffer The offscreen buffer to render into. This buffer
	 * should be provided by the associated <code>Set</code>.
	 */
	@Override
	public void draw(MleBufferedImage buffer)
	{
		//System.out.println("LabelWidgetRole draw()called.");

        Graphics2D g = (Graphics2D)buffer.getGraphics();
        if (m_text != null)
        {
        	// Set the rendering attributes.
        	g.setFont(m_font);
        	g.setColor(m_foregroundColor);
        	
        	// Set bounding region.
        	/*
        	FontRenderContext frc = g.getFontRenderContext();
        	Rectangle2D textBounds = m_font.getStringBounds(m_text, frc);
    		float[] min = new float[2];
    		float[] max = new float[2];
    		min[0] = m_x; min[1] = m_y;
    		max[0] = (float) (m_x + textBounds.getWidth());
    		max[1] = (float) (m_y + textBounds.getHeight());
    		setBounds(min, max);
    		*/
        	
        	// Render the string.
        	g.drawString(m_text, m_x, m_y);
        }
	}

}
