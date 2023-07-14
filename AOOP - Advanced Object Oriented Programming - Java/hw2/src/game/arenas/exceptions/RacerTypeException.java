/**
 * @author Noam Karasso
 */

package game.arenas.exceptions;
/**
 * RacerTypeException is a type of RacerException that is thrown
 * when a racer is incompatible with the arena it is added to
 */
public class RacerTypeException extends RacerException {
	String vehicleType;
	String arenaType;
	
	/**
     * Constructs a new RacerTypeException with the given vehicleType and arenaType
     * @param vehicleType the type of the racer that is incompatible with the arena
     * @param arenaType the type of arena the racer is being added to
     */
	public RacerTypeException(String vehicleType,String arenaType){
		super("Invalid Racer of type " +vehicleType+" for "+arenaType+" arena.");
		this.vehicleType = vehicleType;
		this.arenaType = arenaType;
	}
}
