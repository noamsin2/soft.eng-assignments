/**
 * @author Noam Karasso
 */

package game.arenas.exceptions;

/**
 * Exception class for Racer related exceptions
 */
public class RacerException extends Exception {
	/**
	 * Constructor for RacerException with message
	 * @param msg the message to be displayed with the exception
	 */
	public RacerException(String msg){
		super(msg);
	}
	
	/**
	 * Default constructor for RacerException
	 * Uses a default message
	 */
	public RacerException(){
		super("General RacerException: failed to add a racer!");
	}
}
