/**
 * @author Noam Karasso
 */

package game.racers.land;

import game.racers.Racer;
import game.racers.Wheeled;
import utilities.EnumContainer.*;

/**
 * Represents a car racer that can race on land
 * Inherits from Racer and implements LandRacer
 */
public class Car extends Racer implements LandRacer {

	static final String CLASS_NAME = "Car";
	static final int DEFAULT_WHEELS = 4;
	static final double DEFAULT_MAX_SPEED = 400;
	static final double DEFAULT_ACCELERATION = 20;
	static final Color DEFAULT_color = Color.RED;
	Wheeled wheeled;
	Engine engine;

	/**
	 * Creates a Car with the specified name, max speed, acceleration, color, and number of wheels
	 * @param name the name of the Car
	 * @param maxSpeed the maximum speed of the Car
	 * @param acceleration the acceleration of the Car
	 * @param color the color of the Car
	 * @param numOfWheels the number of wheels the Car has
	 */
	public Car(String name, double maxSpeed, double acceleration, Color color, int numOfWheels) {
		super(name, maxSpeed, acceleration, color);
		wheeled = new Wheeled(numOfWheels);
		setEngine(Engine.FOURSTROKE);
	}

	/**
	 * Creates a default Car with a generated name and default values for max speed, acceleration, color, and number of wheels
	 */
	public Car() {
		super(CLASS_NAME + " #" + getSerial(), DEFAULT_MAX_SPEED, DEFAULT_ACCELERATION, DEFAULT_color);
		wheeled = new Wheeled(DEFAULT_WHEELS);
		setEngine(Engine.FOURSTROKE);
	}

	/**
	 * Constructs a new Car object by copying the attributes of another Car
	 * @param other the Car object to copy
	 */
	public Car(Car other) {
		super(other);
		wheeled = new Wheeled(other.wheeled.getNumOfWheels());
		setEngine(other.getEngine());
	}
	
	/**
	 * Creates and returns a deep copy of this Car object
	 * @return a new Car object that is a copy of this instance
	 */
	public Car clone() {
		return new Car(this);
	}
	
	/**
	 * Returns a string that describes the specific details of the Car, including the type of engine and wheels
	 * @return a string describing the specific details of the Car
	 */
	@Override
	public String describeSpecific() {
		return super.describeSpecific() + ", " + wheeled.describeSpecific() + ", Engine Type: " + getEngine();
	}

	/**
	 * Returns the name of the Car class
	 * @return the name of the Car class
	 */
	@Override
	public String className() {
		return CLASS_NAME;
	}

	/**
	 * Sets the type of engine for the Car.
	 * @param engine the type of engine to set for the Car
	 * @return true, since it's always set successfully
	 */
	public boolean setEngine(Engine engine) {
		this.engine = engine;
		return true;
	}

	/**
	 * Returns the type of engine that the Car has.
	 * @return the type of engine that the Car has
	 */
	private Engine getEngine() {
		return this.engine;
	}
}
