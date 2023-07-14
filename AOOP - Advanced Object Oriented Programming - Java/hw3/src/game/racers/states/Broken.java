/**
 * @author Noam Karasso
 */
package game.racers.states;

import utilities.EnumContainer.racerState;

/**
 * The Broken class represents the "Broken" state of a racer
 * It implements the RacerAlertState interface
 */
public class Broken implements RacerAlertState {

	/**
     * Alerts the state with a specific message
     * @param state the State object associated with the state
     * @param msg   the message to be alerted
     */
	@Override
	public void alert(State state, String msg) {
		System.out.println(msg);
		
	}

	/**
     * Retrieves the state as a racerState enum value
     * @return the state as a racerState enum value
     */
	@Override
	public racerState getState() {
		return racerState.BROKEN;
	}
	
}
