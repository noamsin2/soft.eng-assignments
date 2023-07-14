/**
 * @author Noam Karasso
 */

package game.arenas.land;

import game.arenas.Arena;
import game.arenas.exceptions.*;
import game.racers.Racer;
import game.racers.land.LandRacer;
import utilities.EnumContainer.*;

/**
 * The LandArena class extends the Arena class and represents a land racing arena
 */
public class LandArena extends Arena{
	static final String CLASS_NAME = "LandArena";
	final static double DEFAULT_FRICTION = 0.5;
	final static int DEFAULT_MAX_RACERS = 8;
	final static int DEFAULT_LENGTH = 800;
	Coverage coverage;
	LandSurface surface;
	
	/**
	 * LandArena default constructor, initializes all fields with default values
	 * calls Arena's constructor
	 */
	public LandArena() {
		super(DEFAULT_LENGTH,DEFAULT_MAX_RACERS,DEFAULT_FRICTION);
		setCoverage(Coverage.GRASS);
		setSurface(LandSurface.FLAT);
	}
	
	
	/**
	 * LandArena constructor, calls Arena's constructor
	 * initializes friction, coverage, surface with default values
	 * @param length: Arena's length (will use it for the racers' finish point)
	 * @param maxRacers: Arena's maximum racers (max activeRacers ArrayList size)
	 */
	public LandArena(double length, int maxRacers){
		super(length,maxRacers,DEFAULT_FRICTION);
		setCoverage(Coverage.GRASS);
		setSurface(LandSurface.FLAT);
	}
	
	/**
	 * first check if the racer class matches the arena type
	 * if it does, call Arena's addRacer
	 * @param newRacer: Racer object
	 * @throws RacerLimitException: activeRacers size reached the limit(MAX_RACERS)
	 * @throws RacerTypeException: newRacer's type does not match the arena type
	 */
	public void addRacer(Racer newRacer) throws RacerTypeException, RacerLimitException {
		String racerClass = newRacer.className();
		if(!(newRacer instanceof LandRacer)) {
			throw new RacerTypeException(racerClass,"Land");
		}
		else {
			super.addRacer(newRacer);
		}
	}
	
	/**
	 * set the object's coverage
	 * @param coverage
	 * @return true, since it's always set successfully
	 */
	private boolean setCoverage(Coverage coverage) {
		this.coverage = coverage;
		return true;
	}
	
	/**
	 * set the object's surface
	 * @param surface
	 * @return true, since it's always set successfully
	 */
	private boolean setSurface(LandSurface surface) {
		this.surface = surface;
		return true;
	}
	
	/**
	 * get the object's coverage
	 * @return object's coverage
	 */
	private Coverage getCoverage() {
		return this.coverage;
	}
	
	/**
	 * get the object's surface
	 * @return object's surface
	 */
	private LandSurface getSurface() {
		return this.surface;
	}
	
	/**
     * Returns the name of the class
     * @return the name of the class
     */
	@Override
	public String className() {
		return CLASS_NAME;
	}

}
