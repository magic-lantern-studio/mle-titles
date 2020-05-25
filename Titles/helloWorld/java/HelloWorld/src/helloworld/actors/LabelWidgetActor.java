/*
 * LabelWidgetActor.java
 * Created on January 10, 2011
 */

// COPYRIGHT_BEGIN
// COPYRIGHT_END

// Declare package.
package helloworld.actors;

// Import standard Java classes.
import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

// Import Magic Lantern Runtime classes.
import com.wizzer.mle.math.MlVector2;
import com.wizzer.mle.runtime.core.IMleProp;
import com.wizzer.mle.runtime.core.MleActor;
import com.wizzer.mle.runtime.core.MleRole;
import com.wizzer.mle.runtime.core.MleRuntimeException;

// Import HelloWorld classes.
import helloworld.roles.LabelWidgetRole;

/**
 * This class is an actor capable of displaying a text string. The string to display
 * is specified by the <i>text</i> property in the Digital Workprint. The position of
 * the string is specified by the <i>position</i> property.
 * 
 * @author Wizzer Works
 */
public class LabelWidgetActor extends MleActor
{
	/** Property name for widget identifier. */
	public final String LABELWIDGET_ID_PROPERTY = "id";
	/** Property name for text. */
	public final String LABELWIDGET_TEXT_PROPERTY = "text";
	/** Property name for position. */
	public final String LABELWIDGET_POSITION_PROPERTY = "position";

	/** Widget identifier. */
	String m_id = null;
	/** Label text property. */
	String m_text = null;
	/** Label position property. */
	MlVector2 m_position = new MlVector2();
	
	/**
	 * Dispose all resources associated with the Actor.
     * 
     * @throws MleRuntimeException This exception is thrown if the
     * actor can not be successfully disposed.
	 */
	@Override
	public void dispose() throws MleRuntimeException
	{
		//System.out.println("LabelWidgetActor dispose() called.");
	}

	/**
	 * Initialize the actor.
	 * <p>
	 * The <code>LabelWidgetActor</code> will set the properties on its
	 * associated role, the <code>LabelWidgetRole</code>.
	 * </p>
	 * <p>
	 * Note that the implementation of this actor is dependent upon the
	 * <code>LabelWidgetRole</code>. A better way to implement this
	 * actor would be to use the <code>IMleProp</code> to push and/or
	 * pull property values between the actor and its role.
	 * </p>
	 * 
	 * @throws MleRuntimeException This exception is thrown if the
     * actor can not be successfully initialized.
	 */
	@Override
	public void init() throws MleRuntimeException
	{
		//System.out.println("LabelWidgetActor init() called.");
		MleRole role = getRole();
		if (role instanceof LabelWidgetRole)
		{
			LabelWidgetRole widgetRole = (LabelWidgetRole) role;
			widgetRole.setText(m_text);
			widgetRole.setPosition(m_position.m_vector[0], m_position.m_vector[1]);
		}
	}

	/**
	 * Get the property value for the specified key.
	 * 
	 * @param name The key for the property value.
	 * 
	 * @return The property value will be returned as a generic <code>Object</code>.
	 * If the named property is not found, then the <code>MleRuntimeException</code>
	 * will be thrown.
	 * 
	 * @throws MleRuntimeException This exception is thrown if the key value is
	 * <b>null</b> or if the specified property is not a member of this actor.
	 */
	@Override
	public Object getProperty(String name) throws MleRuntimeException
	{
	    if (name != null)
	    {
	        if (name.equals(LABELWIDGET_POSITION_PROPERTY))
	            return m_position;
	        else if (name.equals(LABELWIDGET_TEXT_PROPERTY))
	            return m_text;
	        else if (name.equals(LABELWIDGET_ID_PROPERTY))
	            return m_id;
	    }

	    // Specified name does not exist.
	    throw new MleRuntimeException("LabelWidgetActor: Unable to get property " + name + ".");
	}

	/**
	 * Set the property value for the specified key.
	 * 
	 * @param name The key for the property value.
	 * @param property The property value to set.
	 * 
	 * @throws MleRuntimeException This exception is thrown if the key value is
	 * <b>null</b> or if the specified property is <b>null</b> or not a member of this actor.
	 */
	@Override
	public void setProperty(String name, IMleProp property)
		throws MleRuntimeException
	{
		//System.out.println("LabelWidgetActor setProperty() called, name = " + name + ".");
        if ((name == null) || (property == null))
        	throw new MleRuntimeException("LabelWidgetActor: Unable to set property " + name + ".");
		
		try
		{
			if (name.equals(LABELWIDGET_ID_PROPERTY))
			{
				// Expecting a string value.
				BufferedReader reader = new BufferedReader(new InputStreamReader(property.getStream()));
				m_id = reader.readLine();
			} else if (name.equals(LABELWIDGET_TEXT_PROPERTY))
			{
				// Expecting a string value.
				BufferedReader reader = new BufferedReader(new InputStreamReader(property.getStream()));
				m_text = reader.readLine();
			} else if (name.equals(LABELWIDGET_POSITION_PROPERTY))
			{
	            // Expecting 2 single-precision floating-point values.
	            DataInputStream in = new DataInputStream(property.getStream());
	            float x = in.readFloat();
	            float y = in.readFloat();
	            m_position.setValue(x,y);
			} else
				throw new MleRuntimeException("LabelWidgetActor: Unable to set property " + name + ".");
		} catch (IOException ex)
		{
			throw new MleRuntimeException("LabelWidgetActor: Unable to set property " + name + ".");
		}
	}

	/**
	 * Set the property array for the specified key.
	 * 
	 * @param name The key for the property array values.
	 * @param length The length of the property array (in bytes).
	 * @param nElements The number of elements in the array.
	 * @param property The property values to set.
	 * 
	 * @throws MleRuntimeException This exception is always thrown because it is not
	 * yet implemented.
	 */
	@Override
	public void setPropertyArray(String name, int length, int nElements,
		ByteArrayInputStream property) throws MleRuntimeException
	{
		throw new MleRuntimeException("LabelWidgetActor: Unable to set property array " + name + ".");
	}

}
