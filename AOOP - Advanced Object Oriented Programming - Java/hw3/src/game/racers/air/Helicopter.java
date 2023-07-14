/**
 * @author Noam Karasso
 */

package game.racers.air;

import game.racers.Racer;
import utilities.EnumContainer.Color;

/**
 * Represents a helicopter racer that can race in the air.
 * Inherits from Racer and implements AerialRacer.
 */
public class Helicopter extends Racer implements AerialRacer {

	static final String CLASS_NAME = "Helicopter";
	static final double DEFAULT_MAX_SPEED = 400;
	static final double DEFAULT_ACCELERATION = 50;
	static final Color DEFAULT_color = Color.BLUE;
	
	/**
     * Constructs a helicopter racer with the given parameters
     * @param name the name of the helicopter racer
     * @param maxSpeed the maximum speed of the helicopter racer
     * @param acceleration the acceleration of the helicopter racer
     * @param color the color of the helicopter racer
     */
	public Helicopter(String name, double maxSpeed, double acceleration, Color color){
		super(name,maxSpeed,acceleration,color);
	}

	/**
     * Constructs a default helicopter racer with default values
     * Uses the constants defined in the class for default values
     */
	public Helicopter(){
		super(CLASS_NAME + " #" + getSerial(), DEFAULT_MAX_SPEED, DEFAULT_ACCELERATION, DEFAULT_color);
	}
	
	/**
	 * Constructs a new Helicopter object by copying the attributes of another Helicopter
	 * @param other the Helicopter object to copy
	 */
	public Helicopter(Helicopter other) {
		super(other);
	}
	
	/**
	 * Creates and returns a deep copy of this Helicopter object
	 * @return a new Helicopter object that is a copy of this instance
	 */
	public Helicopter clone() {
		return new Helicopter(this);
	}
	
	 /**
     * Returns the name of the class
     * @return the name of the class
     */
	@Override
	public String className() {
		return CLASS_NAME;
	}


}
