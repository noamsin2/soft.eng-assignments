/**
 * @author Noam Karasso
 */

package game.arenas.exceptions;

/**
 *RacerLimitException is a specific exception class which is thrown
 *when trying to add a racer to a full arena
 *Extends RacerException class
 */
public class RacerLimitException extends RacerException {
	int nofRacers;
	int racerID;
	
	/**
	 *Constructor for RacerLimitException
	 *@param nofRacers The number of active racers in the arena
	 *@param racerID The serial number of the racer that wasn't added
	 */
	public RacerLimitException(int nofRacers,int racerID){
		super("Arena is full! (" +nofRacers+ " active racers exist). racer #"+racerID+" was not added");
		this.nofRacers = nofRacers;
		this.racerID = racerID;
	}
}
