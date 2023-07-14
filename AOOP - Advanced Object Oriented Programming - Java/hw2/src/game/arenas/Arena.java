/**
 * @author Noam Karasso
 */

package game.arenas;

import java.awt.Image;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.ArrayList;

import javax.swing.ImageIcon;

import game.racers.Racer;
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
	private final double FRICTION;
	private final int MAX_RACERS;
	private final static int MIN_Y_GAP = 50;
	private double length;
	private int height;
	private double y;
	private ImageIcon icon;
	
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
		if (evt.getOldValue() == racerState.ACTIVE && evt.getNewValue() == racerState.COMPLETED);
	          crossFinishLine((Racer)evt.getSource());
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
	 * This method makes all racers play a turn (move each one of the active racers)
	 * check if any crossed the finish line
	 */
	public void playTurn() {
		for(int i = 0; i < activeRacers.size();i++) {
			Racer racer = activeRacers.get(i);
			racer.move(this.FRICTION);
			if(racer.getCurrentLocation().getX() >= racer.getFinish().getX()) {
				crossFinishLine(racer);
				i--;
			}
		}
	}
	
	/**
	 * This method removes a racer from activeRacers ArrayList
	 * and adds it to completedRacers ArrayList
	 * @param racer who crossed the finish line
	 */
	private void crossFinishLine(Racer racer) {
		synchronized(completedRacers) {
			System.out.println(racer);
			this.completedRacers.add(racer);
			this.activeRacers.remove(racer);
			System.out.println(racer);
		}
	}
	
	/**
	 * This method shows results at the end of the race ordered by placement
	 */
	public void showResults() {
		int x = 0;
		for(Racer racer:completedRacers) {
			System.out.println("#"+x+++" -> "+racer.describeRacer());
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
}
