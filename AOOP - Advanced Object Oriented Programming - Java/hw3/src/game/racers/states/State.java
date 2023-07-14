/**
 * @author Noam Karasso
 */
package game.racers.states;

import utilities.EnumContainer.racerState;

/**
 * The State class represents the state of a racer and provides methods to set and get the current state as well as alert
 */
public class State {
	private RacerAlertState currentState;
	
	/**
     * Constructs a State object with an initial state of "Active"
     */
	public State() {
		currentState = new Active();
	}
	
	 /**
     * Sets the current state of the racer
     * @param state the RacerAlertState representing the new state
     */
	public void setState(RacerAlertState state) {
		this.currentState = state;
	}
	/**
     * Alerts the racer with a specific message based on the current state
     * @param msg the message associated with the alert
     */
	public void alert(String msg) {
		currentState.alert(this, msg);
	}
	
	/**
     * Retrieves the current state of the racer
     * @return the current state of the racer as a racerState enum value
     */
	public racerState getState() {
		return currentState.getState();
	}
}
