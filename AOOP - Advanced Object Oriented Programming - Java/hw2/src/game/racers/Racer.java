/**
 * @author Noam Karasso
 */
package game.racers;

import utilities.Point;

import java.awt.Image;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

import javax.swing.ImageIcon;

import game.arenas.Arena;
import utilities.EnumContainer.*;
import utilities.Fate;
import utilities.Mishap;

/**
 *this is an abstract class that represents a racer in a race game
 */
public abstract class Racer implements Runnable{
	private static int serial = 1;
	private static final int RACER_ICON_SIZE = 65;
	private int serialNumber;
	private String name;
	private Point currentLocation;
	private Point finish;
	private Arena arena;
	private double maxSpeed;
	private double acceleration;
	private double currentSpeed;
	private double failureProbability;
	private Color color;
	private Mishap mishap;
	private ImageIcon icon;
	private PropertyChangeSupport support; 
	private racerState state;
	
	/**
	 * constructor method that creates a new Racer object with the given name, maximum speed, acceleration, and color
	 * @param name: a private string field that represents the name of the racer
	 * @param maxSpeed: a private double field that represents the maximum speed of the racer
	 * @param acceleration: a private double field that represents the acceleration of the racer
	 * @param color: a private Color field that represents the color of the racer
	 */
	public Racer(String name, double maxSpeed, double acceleration, Color color) {
		setSerialNumber(serial++);
		setCurrentSpeed(0);
		setMishap(null);
		setName(name);
		setMaxSpeed(maxSpeed);
		setAcceleration(acceleration);
		setColor(color);
		setIcon();
		support = new PropertyChangeSupport(this);
	}
	
	/**
	 * Adds a property change listener to the underlying support object in a thread-safe manner
	 * @param pcl The property change listener to be added
	 */
	private void addPropertyChangeListener(PropertyChangeListener pcl){
			support.addPropertyChangeListener(pcl);
	} 
	
	/**
	 * Removes a property change listener from the underlying support object in a thread-safe manner
	 * @param pcl The property change listener to be removed
	 */
	private void removePropertyChangeListener(PropertyChangeListener pcl){ 
			support.removePropertyChangeListener(pcl);
	} 

	/**
	 *Sets the icon for the racer based on its class name and color
	 *@return True if the icon is successfully set, which is always
	 */
	private boolean setIcon() {
		this.icon = new ImageIcon(new ImageIcon("icons/"+ className() + 
				getColor() + ".png").getImage().getScaledInstance(RACER_ICON_SIZE,RACER_ICON_SIZE, Image.SCALE_DEFAULT));
		return true;
	}
	
	/**
	*Retrieves the icon of the racer
	*@return The ImageIcon representing the racer's icon
	*/
	public ImageIcon getIcon() {
		return this.icon;
	}
	
	/**
	 * a method that initializes the race by registering the arena, current location, and finish point of the racer
	 * @param arena: a private Arena field that represents the arena in which the racer is racing
	 * @param start: a private Point field that represents the start point of the race
	 * @param finish: a private Point field that represents the finish point of the race
	 */
	public void initRace(Arena arena, Point start, Point finish) {
		setState(racerState.ACTIVE);
		addPropertyChangeListener(arena);
		setArena(arena);
		setCurrentLocation(start);
		setFinish(finish);
	}
	
	/**
	 *a runnable interface method that lets us use multi threading
	 *it checks if the racer has not yet reached the finish line and calls move function
	 *with the arena's friction as parameter
	 *in each iteration it sleeps for 100 milliseconds
	 *when it reaches the finish line it calls notifyObservers function that notifies the arena
	 *that the racer has finished the race 
	 */
	public void run() {
		while(isRacing()) {
			move(arena.getFriction());
			try {
				Thread.sleep(100);
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		this.setCurrentLocation(new Point(arena.getLength(),currentLocation.getY()));
		
		racerState newState = racerState.COMPLETED; 
		support.firePropertyChange("racerState", getState(), newState); 
		setState(newState);
	}
	
	/**
	 *Determines whether the racer is still racing or has finished
	 *@return True if the racer has not crossed the finish line, false otherwise
	 */
	private boolean isRacing() {
		if(getCurrentLocation().getX() >= getFinish().getX())
			return false;
		return true;
	}
	
	/**
	 * a method that calculates the racer's new location based on its current speed, acceleration, and friction
	 * It also checks if the racer has a mishap and updates its current speed accordingly
	 * @param friction: The amount of friction on the surface of the arena that affects the racer's movement
	 * @return the current location of the racer after moving
	 */
	public Point move(double friction) {
		//first check if there is a mishap if not there is a chance to generate a new mishap 
		if (!hasMishap()) {
			setMishap(null);
			if (Fate.breakDown()) {
				setMishap(Fate.generateMishap());
				System.out.println(this.getName() + " Has a new mishap! "+mishap.toString());
			}
		}
		if (hasMishap()) {
			//if it has a mishap calculate the current speed accordingly
			setCurrentSpeed(getCurrentSpeed() + getAcceleration() * mishap.getReductionFactor() * friction);
			mishap.nextTurn();
		}
		else
			setCurrentSpeed(getCurrentSpeed() + getAcceleration() * friction);
		//make sure it doesn't pass max speed
		if (getCurrentSpeed() > getMaxSpeed()) {
			setCurrentSpeed(getMaxSpeed());
		}
		
		//update location according to speed
		currentLocation.setX(getCurrentLocation().getX() + getCurrentSpeed());
		return getCurrentLocation();
	}

	/**
	 * @return a string containing the racer's specific attributes (maxSpeed, acceleration, and color)
	 */
	public String describeSpecific() {
		return "maxSpeed: " + getMaxSpeed() + ", acceleration: " + getAcceleration() + ", color: " + getColor();
	}

	/**
	 * @return a string containing the racer's name, serial number, and specific attributes
	 */
	public String describeRacer() {
		return "name: " + getName() + ", " + "SerialNumber: " + getSerialNumber() + ", " + describeSpecific();
	}
	/**
	 * a method that prints out the racer's class name and description
	 */
	public void introduce() {
		System.out.println("[" + className() + "] " + describeRacer());
	}
	
	/**
	 *an abstract method that returns the name of the racer's class
	 */
	public abstract String className();

	/**
	 * a private method that checks if the racer has a mishap
	 * @return true if the racer has a mishap that is not fixable, false otherwise
	 */
	private boolean hasMishap() {
		if (mishap == null || (mishap.getFixable() && mishap.getTurnsToFix() == 0)) {
			return false;
		}
		return true;
	}
	
	/**
	 *Sets the state of the racer
	 *@param state: The racer state to be set
	 *@return True if the state is successfully set, which is always
	 */
	public boolean setState(racerState state) {
		this.state = state;
		return true;
	}
	
	/**
	 *Retrieves the state of the racer
	 *@return The current racer state
	 */
	public racerState getState() {
		return this.state;
	}
	
	/**
	 * a private method that sets the racer's serial number
	 * @param serialNumber: the serial number to assign to the racer
	 * @return true, since it's always set successfully
	 */
	private boolean setSerialNumber(int serialNumber) {
		this.serialNumber = serialNumber;
		return true;
	}

	/**
	 * a private method that sets the racer's name
	 * @param name: the name to assign to the racer
  	 * @return true, since it's always set successfully
	 */
	private boolean setName(String name) {
		this.name = name;
		return true;
	}

	/**
	 * a private method that sets the racer's current location
	 * @param currentLocation: the current location of the racer
  	 * @return true, since it's always set successfully
	 */
	private boolean setCurrentLocation(Point currentLocation) {
		this.currentLocation = currentLocation;
		return true;
	}
	/**
	 * a private method that sets the racer's finish point
	 * @param finish: the racer's finish line
  	 * @return true, since it's always set successfully
	 */
	private boolean setFinish(Point finish) {
		this.finish = finish;
		return true;
	}
	/**
	 * a private method that sets the racer's arena
	 * @param arena: the race's arena
     * @return true, since it's always set successfully
	 */
	private boolean setArena(Arena arena) {
		this.arena = arena;
		return true;
	}
	
	/**
	 * a private method that sets the racer's maximum speed
	 * @param maxSpeed: the maximum speed of the racer
     * @return true, since it's always set successfully
	 */
	private boolean setMaxSpeed(double maxSpeed) {
		this.maxSpeed = maxSpeed;
		return true;
	}

	/**
	 * a private method that sets the racer's acceleration
	 * @param acceleration: the acceleration of the racer
     * @return true, since it's always set successfully
	 */
	private boolean setAcceleration(double acceleration) {
		this.acceleration = acceleration;
		return true;
	}

	/**
	 * a private method that sets the racer's current speed
	 * @param currentSpeed: the current speed of the racer
     * @return true, since it's always set successfully
	 */
	private boolean setCurrentSpeed(double currentSpeed) {
		this.currentSpeed = currentSpeed;
		return true;
	}

	/**
	 * a private method that sets the racer's failure probability
	 * @param failureProbability: the failure probability of the racer
     * @return true, since it's always set successfully
	 */
	private boolean setFailureProbability(double failureProbability) {
		this.failureProbability = failureProbability;
		return true;
	}

	/**
	 * a private method that sets the racer's color
	 * @param color: the color of the racer
     * @return true, since it's always set successfully
	 */
	private boolean setColor(Color color) {
		this.color = color;
		return true;
	}

	/**
	 * a private method that sets the racer's mishap
	 * @param mishap: the mishap to assign to the racer
     * @return true, since it's always set successfully
	 */
	private boolean setMishap(Mishap mishap) {
		this.mishap = mishap;
		return true;
	}
	
	/**
	 * a public method that returns the racer's serial number
	 * @return the serial number of the racer
	 */
	public int getSerialNumber() {
		return this.serialNumber;
	}

	/**
	 * a public method that returns the racer's name
	 * @return a private string field that represents the name of the racer 
	 */
	public String getName() {
		return this.name;
	}

	/**
	 * a public method that returns the racer's current location
	 * @return a Point object representing the Racer's current location
	 */
	public Point getCurrentLocation() {
		return this.currentLocation;
	}

	/**
	 * a public method that returns the finish point of the racer
	 * @return a Point object representing the finish line of the Racer's current Arena
	 */
	public Point getFinish() {
		return this.finish;
	}

	/**
	 * a public method that returns the arena in which the racer is competing
	 * @return an Arena object representing the current Arena of the Racer
	 */
	public Arena getArena() {
		return this.arena;
	}

	/**
	 * a public method that returns the maximum speed of the racer
	 * @return a double representing the maximum speed of the Racer
	 */
	public double getMaxSpeed() {
		return this.maxSpeed;
	}

	/**
	 * a private method that returns the acceleration of the racer
	 * @return a double representing the acceleration of the Racer
	 */
	private double getAcceleration() {
		return this.acceleration;
	}

	/**
	 * a public method that returns the racer's current speed
	 * @return a double representing the current speed of the Racer
	 */
	public double getCurrentSpeed() {
		return this.currentSpeed;
	}

	/**
	 * a private method that returns the probability of the racer encountering a mishap.
	 * @return a double representing the probability that the Racer will experience a failure
	 */
	private double getFailureProbability() {
		return this.failureProbability;
	}

	/**
	 * a private method that returns the color of the racer's vehicle
	 * @return a Color object representing the color of the Racer
	 */
	private Color getColor() {
		return this.color;
	}

	/**
	 * a private method that returns the mishap associated with the racer
	 * @return a Mishap object representing the current mishap of the Racer
	 */
	private Mishap getMishap() {
		return this.mishap;
	}

	/**
	 * a protected method that returns the serial number of the racer
	 * @return: an integer representing the serial number of the Racer.
	 */
	protected static int getSerial() {
		return serial;
	}
}
