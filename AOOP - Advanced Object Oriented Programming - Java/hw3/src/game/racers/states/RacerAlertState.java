/**
 * @author Noam Karasso
 */
package game.racers.states;

import utilities.EnumContainer.racerState;

/**
 * The RacerAlertState interface represents a state of alert for a state
 * It provides methods to handle alerts and retrieve the current state
 */
public interface RacerAlertState {
	public void alert(State state, String msg);
	public racerState getState();
}
