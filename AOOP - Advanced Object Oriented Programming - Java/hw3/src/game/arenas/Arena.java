/**
 * @author Noam Karasso
 */

package game.arenas;

import java.awt.Image;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.ArrayList;
import java.util.Collections;

import javax.swing.ImageIcon;

import game.racers.Racer;
import game.racers.states.*;
import utilities.Point;
import utilities.EnumContainer.racerState;
import game.arenas.exceptions.RacerLimitException;
import game.arenas.exceptions.RacerTypeException;

/**
 * this is an abstract class that represents a racing arena, where racers can compete against each other
 */
public abstract class Arena implements PropertyChangeListener{

	private ArrayList<Racer> activeRacers;
	private ArrayList<Racer> completedRacers;
	private ArrayList<Racer> disabledRacers;
	private final double FRICTION;
	private final int MAX_RACERS;
	private final static int MIN_Y_GAP = 50;
	private double length;
	private int height;
	private double y;
	private ImageIcon icon;
	private long startTime;
	
	/**
	 * Arena constructor initializes length, MAX_RACERS, FRICTION, as well as empty activeRacers,
	 * completedRacers ArrayLists
	 * @param length: arena's length (used as finish line for racers)
	 * @param height: arena's height (used to determine the window size)
	 * @param maxRacers: arena's max racers (will be active racers' max size)
	 * @param friction: arena's friction (will affect the racers' speed)
	 */
	public Arena(double length, int maxRacers, double friction) {
		activeRacers = new ArrayList<Racer>();
		completedRacers = new ArrayList<Racer>();
		disabledRacers = new ArrayList<Racer>();
		this.length = length;
		this.height = Math.max(maxRacers*55, 700);
		this.MAX_RACERS = maxRacers;
		this.FRICTION = friction;
		y = 0;
		setIcon();
	}

	/**
	 *Sets the icon for the arena based on its class name
	 *The icon is loaded from the "icons" directory with a file name matching the arena's class name
	 *@return True if the icon is successfully set which is always
	 */
	private boolean setIcon() {
		this.icon = new ImageIcon(new ImageIcon("icons/" + className() + ".jpg").getImage()
				.getScaledInstance((int)getLength()+80, getHeight(), Image.SCALE_DEFAULT));
		return true;
	}
	
	/**
	 *Retrieves the height of the arena
	 *@return The height of the arena
	 */
	public int getHeight() {
		return this.height;
	}

	/**
	 * Sorts the active racers by distance
	 * Note: This method is thread-safe and synchronized on the list of active racers
	 */
	public void sortActiveRacers() {
		synchronized(activeRacers) {
	        Collections.sort(getActiveRacers());
		}
	}
	/**
	 * Sorts the disabled racers by distance
	 * Note: This method is thread-safe and synchronized on the list of disabled racers
	 */
	public void sortDisabledRacers() {
		synchronized(disabledRacers) {
	        Collections.sort(getDisabledRacers());
		}
	}
	
	/**
	 *Retrieves the icon of the arena
	 *@return The ImageIcon representing the arena's icon
	 */
	public ImageIcon getIcon() {
		return this.icon;
	}

	/**
	 *Responds to a property change event
	 *This method is called when a property change event occurs
	 *determines the function based on the old property of the value and the new property of the value
	 *@param evt The property change event that triggered this method
	 */
	public void propertyChange(PropertyChangeEvent evt) {
		Racer racer = (Racer)evt.getSource();
		State state = racer.getState();
		if (evt.getOldValue() == racerState.ACTIVE && evt.getNewValue() == racerState.COMPLETED) {
			racer.getState().setState(new Completed());
	        crossFinishLine(racer);
	        state.alert("Racer " + racer.getName() + " finished the race!");
		}
		else if(evt.getOldValue() == racerState.ACTIVE && evt.getNewValue() == racerState.BROKEN) {
			racer.getState().setState(new Broken());
			state.alert("Racer " + racer.getName() + " broke after " + Long.toString((System.currentTimeMillis() - getStartTime())) + " milliseconds");
		}
		else if(evt.getOldValue() == racerState.BROKEN && evt.getNewValue() == racerState.ACTIVE) {
			racer.getState().setState(new Active());
			state.alert("Racer " + racer.getName() + " is active, current rank: " + Integer.toString(getActiveRacers().indexOf(racer) + 1 + getCompletedRacers().size()));	
		}
		else if(evt.getOldValue() == racerState.BROKEN && evt.getNewValue() == racerState.DISABLED) {
			racer.getState().setState(new Disabled());
			disableRacer(racer);
			state.alert("Racer " + racer.getName() + " is disabled and cannot continue the race!");
		}
		else if(evt.getOldValue() == racerState.BROKEN && evt.getNewValue() == racerState.COMPLETED) {
			racer.getState().setState(new Completed());
			crossFinishLine(racer);
			state.alert("Racer " + racer.getName() + " finished the race!");
		}
	}

	
	/**
	 * This method adds a racer to the activeRacers ArrayList and initializes it
	 * @param newRacer: Racer object
	 * @throws RacerLimitException: activeRacers size reached the limit(MAX_RACERS)
	 * @throws RacerTypeException: newRacer's type does not match the arena type
	 */
	public void addRacer(Racer newRacer) throws RacerLimitException, RacerTypeException {
		if (activeRacers.size() == MAX_RACERS) {
			throw new RacerLimitException(MAX_RACERS, newRacer.getSerialNumber());
		}
		newRacer.initRace(this, new Point(0, y), new Point(this.length, y));
		y += MIN_Y_GAP;
		activeRacers.add(newRacer);
	}

	/**
	 * This method initializes a race.
	 * giving all competitors a start point and finish point and this arena
	 */
	public void initRace() {
		int y = 0;
		for (Racer racer : activeRacers) {
			racer.initRace(this, new Point(0, y), new Point(this.length, y));
			y += MIN_Y_GAP;
		}
	}
	
	/**
	 * This method checks if there are active racers left
	 * @return true if there are, false if the ArrayList is empty
	 */
	public boolean hasActiveRacers() {
		if(activeRacers.isEmpty())
			return false;
		return true;
	}
	
	/**
	 *an abstract method that returns the name of the arena's class
	 */
	public abstract String className();
	
	
	/**
	 * This method removes a racer from activeRacers ArrayList
	 * and adds it to completedRacers ArrayList
	 * @param racer who crossed the finish line
	 */
	private void crossFinishLine(Racer racer) {
		//to avoid many data inconsistency and unexpected exceptions due to the remove function shifting objects in the arraylist
		synchronized(activeRacers) {
			//to avoid two racers adding at the same time resulting in only one being added
			synchronized(completedRacers) {
				this.completedRacers.add(racer);
			}
			this.activeRacers.remove(racer);
		}
	}
	
	/**
	 * This method removes a racer from activeRacers ArrayList
	 * and adds it to disabledRacers ArrayList
	 * @param racer who is disabled and cannot continue the race
	 */
	private void disableRacer(Racer racer) {
		//to avoid many data inconsistency and unexpected exceptions due to the remove function shifting objects in the arraylist
		synchronized(activeRacers) {
			//to avoid two racers adding at the same time resulting in only one being added and to not interrupt the sorting
			synchronized(disabledRacers) {
				this.disabledRacers.add(racer);
			}
			this.activeRacers.remove(racer);
		}
	}
	/**
	 * @return object's activeRacers
	 */
	public ArrayList<Racer> getActiveRacers(){
		return this.activeRacers;
	}
	
	/**
	* @return object's completedRacers
	*/
	public ArrayList<Racer> getCompletedRacers(){
		return this.completedRacers;
	}
	
	/**
	* @return object's disabledRacers
	*/
	public ArrayList<Racer> getDisabledRacers(){
		return this.disabledRacers;
	}
	
	
	/**
	 * @return object's friction
	 */
	public double getFriction() {
		return this.FRICTION;
	}

	/**
	 * @return object's max racers
	 */
	private int getMaxRacers() {
		return this.MAX_RACERS;
	}

	/**
	 * @return object's length
	 */
	public double getLength() {
		return this.length;
	}

	/**
	 * Gets the start time of the race
	 * @return the start time of the race in milliseconds
	 */
	public long getStartTime() {
		return startTime;
	}

	/**
	 * Sets the start time of the race
	 * @param startTime the start time of the race to set in milliseconds
	 * @return true if the start time was successfully set, false otherwise
	 */
	public boolean setStartTime(long startTime) {
		this.startTime = startTime;
		return true;
	}
}
