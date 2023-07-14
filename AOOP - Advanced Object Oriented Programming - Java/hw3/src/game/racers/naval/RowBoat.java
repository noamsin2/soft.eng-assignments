/**
 * @author Noam Karasso
 */

package game.racers.naval;

import game.racers.Racer;
import utilities.EnumContainer.*;

/**
 * RowBoat class is a subclass of Racer and implements the NavalRacer interface
 * and it represents a row boat racer that races on naval arena
 */
public class RowBoat extends Racer implements NavalRacer {

	static final String CLASS_NAME = "RowBoat";
	static final double DEFAULT_MAX_SPEED = 75;
	static final double DEFAULT_ACCELERATION = 10;
	static final Color DEFAULT_color = Color.RED;
	BoatType type;
	Team team;

	/**
	 * Constructor for RowBoat that takes arguments for name, maxSpeed, acceleration, and color
	 * Initializes type to Skulling and team to Double
	 *
	 * @param name         a String representing the name of the RowBoat
	 * @param maxSpeed     a double representing the maximum speed of the RowBoat
	 * @param acceleration a double representing the acceleration of the RowBoat
	 * @param color        a Color representing the color of the RowBoat
	 */
	public RowBoat(String name, double maxSpeed, double acceleration, Color color) {
		super(name, maxSpeed, acceleration, color);
		setType(BoatType.SKULLING);
		setTeam(Team.DOUBLE);
	}

	/**
	 * Default constructor for creating a new instance of the RowBoat class with default values
	 */
	public RowBoat() {
		super(CLASS_NAME + " #" + getSerial(), DEFAULT_MAX_SPEED, DEFAULT_ACCELERATION, DEFAULT_color);
		setType(BoatType.SKULLING);
		setTeam(Team.DOUBLE);
	}

	/**
	 * Constructs a new RowBoat object by copying the attributes of another RowBoat
	 * @param other the RowBoat object to copy
	 */
	public RowBoat(RowBoat other) {
		super(other);
		setType(other.getType());
		setTeam(other.getTeam());
	}
	
	/**
	 * Creates and returns a deep copy of this RowBoat object
	 * @return a new RowBoat object that is a copy of this instance
	 */
	public RowBoat clone() {
		return new RowBoat(this);
	}
	
	/**
	 * Overrides the describeSpecific method from the superclass to add the type and team of the RowBoat
	 * @return A string representing the specific details of the RowBoat
	 */
	@Override
	public String describeSpecific() {
		return super.describeSpecific() + ", Type: " + getType() + ", Team: " + getTeam();
	}

	/**
	 * Overrides the className method from the superclass to return the name of the RowBoat class
	 * @return A string representing the name of the RowBoat class
	 */
	@Override
	public String className() {
		return CLASS_NAME;
	}

	/**
	 * Sets the type of the RowBoat to the given type
	 * @param type The type of the RowBoat
	 * @return true, since it's always set successfully
	 */
	public boolean setType(BoatType type) {
		this.type = type;
		return true;
	}

	/**
	 * Gets the type of the RowBoat
	 * @return The type of the RowBoat
	 */
	private BoatType getType() {
		return this.type;
	}

	/**
	 * Sets the team of the RowBoat to the given team
	 * @param team The team of the RowBoat
	 * @return true, since it's always set successfully
	 */
	public boolean setTeam(Team team) {
		this.team = team;
		return true;
	}

	/**
	 * Gets the team of the RowBoat
	 * @return The team of the RowBoat
	 */
	private Team getTeam() {
		return this.team;
	}
}
