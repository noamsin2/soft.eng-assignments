/**
 * @author Noam Karasso
 */

package game.racers;
/**
 * This class describes a wheeled vehicle with a specific number of wheels
 */
public class Wheeled {
	int numOfWheels;
	
	/**
	 * Constructor that initializes the number of wheels for the wheeled vehicle
	 * @param numOfWheels: number of wheels for the wheeled vehicle
	 */
	public Wheeled(int numOfWheels){
		setNumOfWheels(numOfWheels);
	}
	
	/**
	 * Default constructor that initializes the number of wheels to 0
	 */
	Wheeled(){
		setNumOfWheels(0);
	}
	
	/**
	 * Sets the number of wheels for the wheeled vehicle
	 * @param numOfWheels: number of wheels for the wheeled vehicle
	 * @return true, since the it's always set successfully
	 */
	private boolean setNumOfWheels(int numOfWheels) {
		this.numOfWheels = numOfWheels;
		return true;
	}
	
	/**
	 * Gets the number of wheels for the wheeled vehicle
	 * @return the number of wheels for the wheeled vehicle
	 */
	private int getNumOfWheels() {
		return numOfWheels;
	}
	
	/**
	 * Describes the specific attributes of the wheeled vehicle
	 * @return a string that describes the specific attributes of the wheeled vehicle (in this case, the number of wheels)
	 */
	public String describeSpecific() {
		return "Number of Wheels: " + getNumOfWheels();
	}

}
