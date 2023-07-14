/**
 * @author Noam Karasso
 */

package game.racers.naval;

import game.racers.Racer;
import utilities.EnumContainer.*;

/**
 * SpeedBoat class is a subclass of Racer and implements the NavalRacer interface
 * and it represents a speed boat racer that races on naval arena
 */
public class SpeedBoat extends Racer implements NavalRacer {

	static final String CLASS_NAME = "SpeedBoat";
	static final double DEFAULT_MAX_SPEED = 170;
	static final double DEFAULT_ACCELERATION = 5;
	static final Color DEFAULT_color = Color.RED;
	BoatType type;
	Team team;

	 /**
     * Constructor that takes in the boat's name, maximum speed, acceleration, and color
     * Initializes the boat's type to "skulling" and team to "double"
     * @param name         The name of the speed boat
     * @param maxSpeed     The maximum speed of the speed boat
     * @param acceleration The acceleration of the speed boat
     * @param color        The color of the speed boat
     */
	public SpeedBoat(String name, double maxSpeed, double acceleration, Color color) {
		super(name, maxSpeed, acceleration, color);
		setType(BoatType.SKULLING);
		setTeam(Team.DOUBLE);
	}

	/**
     * Default constructor that initializes the speed boat's properties to default values
     * Initializes the boat's type to "skulling" and team to "double"
     */
	public SpeedBoat() {
		super(CLASS_NAME + " #" + getSerial(), DEFAULT_MAX_SPEED, DEFAULT_ACCELERATION, DEFAULT_color);
		setType(BoatType.SKULLING);
		setTeam(Team.DOUBLE);
	}

	/**
     * Returns a string that describes the speed boat's specific properties
     * @return A string that describes the speed boat's specific properties, including type and team
     */
	@Override
	public String describeSpecific() {
		return super.describeSpecific() + ", Type: " + getType() + ", Team: " + getTeam();
	}

	/**
     * Returns the class name of the speed boat
     * @return The class name of the speed boat
     */
	@Override
	public String className() {
		return CLASS_NAME;
	}

	/**
     * Sets the type of the speed boat
     * @param type The type of the speed boat
     * @return true, since it's always set successfully
     */
	public boolean setType(BoatType type) {
		this.type = type;
		return true;
	}

	/**
     * Returns the type of the speed boat
     * @return The type of the speed boat
     */
	private BoatType getType() {
		return this.type;
	}

	/**
     * Sets the team of the speed boat.
     *
     * @param team The team of the speed boat
     * @return true, since it's always set successfully
     */
	public boolean setTeam(Team team) {
		this.team = team;
		return true;
	}

	 /**
     * Returns the team of the speed boat
     * @return The team of the speed boat
     */
	private Team getTeam() {
		return this.team;
	}

}
