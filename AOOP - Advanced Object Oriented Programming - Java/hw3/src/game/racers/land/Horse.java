/**
 * @author Noam Karasso
 */

package game.racers.land;

import game.racers.Racer;
import utilities.EnumContainer.*;

/**
 * Represents a horse racer that can race on land
 * Inherits from Racer and implements LandRacer
 */
public class Horse extends Racer implements LandRacer {

	static final String CLASS_NAME = "Horse";
	static final double DEFAULT_MAX_SPEED = 50;
	static final double DEFAULT_ACCELERATION = 3;
	static final Color DEFAULT_color = Color.BLACK;
	Breed breed;

	/**
     * Creates a new Horse with the given name, maximum speed, acceleration,
     * and color
     * The Breed is set to THOROUGHBRED by default
     * @param name         the name of the Horse
     * @param maxSpeed     the maximum speed of the Horse
     * @param acceleration the acceleration of the Horse
     * @param color        the color of the Horse
     */
	public Horse(String name, double maxSpeed, double acceleration, Color color) {
		super(name, maxSpeed, acceleration, color);
		setBreed(Breed.THOROUGHBRED);
	}

	/**
     * Creates a new Horse with a default name, maximum speed, acceleration,
     * and color
     * The Breed is set to THOROUGHBRED by default
     */
	public Horse() {
		super(CLASS_NAME + " #" + getSerial(), DEFAULT_MAX_SPEED, DEFAULT_ACCELERATION, DEFAULT_color);
		setBreed(Breed.THOROUGHBRED);
	}

	/**
	 * Constructs a new Horse object by copying the attributes of another Horse
	 * @param other the Horse object to copy
	 */
	public Horse(Horse other) {
		super(other);
		setBreed(other.getBreed());
	}
	
	/**
	 * Creates and returns a deep copy of this Horse object
	 * @return a new Horse object that is a copy of this instance
	 */
	public Horse clone() {
		return new Horse(this);
	}
	
	/**
     * Returns a string that describes the specific details of the Horse, including the breed
	 * @return a string describing the specific details of the Horse
     */
	@Override
	public String describeSpecific() {
		return super.describeSpecific() + ", Breed: " + getBreed();
	}

	 /**
     * Returns the name of the Horse class
     * @return the name of the Horse class
     */
	@Override
	public String className() {
		return CLASS_NAME;
	}

	/**
     * Sets the breed of the Horse.
     * @param breed the breed of the Horse
     * @return true, since it's always set successfully
     */
	public boolean setBreed(Breed breed) {
		this.breed = breed;
		return true;
	}

	 /**
     * Returns the breed of the Horse
     * @return the breed of the Horse
     */
	private Breed getBreed() {
		return this.breed;
	}

}
