/**
 * @author Noam Karasso
 */

package game.racers.land;

import game.racers.Racer;
import game.racers.Wheeled;
import utilities.EnumContainer.*;

/**
 * Represents a bicycle racer that can race on land
 * Inherits from Racer and implements LandRacer
 */
public class Bicycle extends Racer implements LandRacer {

	static final String CLASS_NAME = "Bicycle";
	static final int DEFAULT_WHEELS = 2;
	static final double DEFAULT_MAX_SPEED = 270;
	static final double DEFAULT_ACCELERATION = 10;
	static final Color DEFAULT_color = Color.GREEN;
	Wheeled wheeled;
	BicycleType type;

	/**
     * Constructs a bicycle racer with the given parameters
     * @param name the name of the bicycle racer
     * @param maxSpeed the maximum speed of the bicycle racer
     * @param acceleration the acceleration of the bicycle racer
     * @param color the color of the bicycle racer
     * @param numOfWheels the number of wheels the bicycle racer has
     */
	public Bicycle(String name, double maxSpeed, double acceleration, Color color, int numOfWheels) {
		super(name, maxSpeed, acceleration, color);
		wheeled = new Wheeled(numOfWheels);
		setType(BicycleType.MOUNTAIN);
	}

	/**
     * Constructs a default bicycle racer with default values
     * Uses the constants defined in the class for default values
     */
	public Bicycle() {
		super(CLASS_NAME + " #" + getSerial(), DEFAULT_MAX_SPEED, DEFAULT_ACCELERATION, DEFAULT_color);
		wheeled = new Wheeled(DEFAULT_WHEELS);
		setType(BicycleType.MOUNTAIN);
	}

	/**
     * Returns a string that describes the specific properties of the bicycle racerת
     * including the number of wheels and the type of bicycle
     * @return a string that describes the specific properties of the bicycle racer
     */
	@Override
	public String describeSpecific() {
		return super.describeSpecific() + ", " + wheeled.describeSpecific() + ", Bycicle Type: " + getType();
	}

	/**
     * Returns the name of the class
     * @return the name of the class
     */
	@Override
	public String className() {
		return CLASS_NAME;
	}

	/**
     * Sets the type of the bicycle racer
     * @param type the type of the bicycle racer
     * @return true, since it's always set successfully
     */
	public boolean setType(BicycleType type) {
		this.type = type;
		return true;
	}

	/**
     * Returns the type of the bicycle racer
     * This method is private, since the type should not be accessible outside of the class
     * @return the type of the bicycle racer
     */
	private BicycleType getType() {
		return this.type;
	}
}
