/**
 * @author Noam Karasso
 */

package game.arenas.naval;

import game.arenas.Arena;
import game.arenas.exceptions.*;
import game.racers.Racer;
import game.racers.naval.NavalRacer;
import utilities.EnumContainer.*;


/**
 * The NavalArena class extends the Arena class and represents a naval racing arena
 */
public class NavalArena extends Arena{
	final static double DEFAULT_FRICTION = 0.7;
	final static int DEFAULT_MAX_RACERS = 5;
	final static int DEFAULT_LENGTH = 1000;
	Water water;
	WaterSurface surface;
	Body body;
	
	/**
	 * NavalArena default constructor, initializes all fields with default values
	 * calls Arena's constructor
	 */
	public NavalArena(){
		super(DEFAULT_LENGTH,DEFAULT_MAX_RACERS,DEFAULT_FRICTION);
		setWater(Water.SWEET);
		setSurface(WaterSurface.FLAT);
		setBody(Body.LAKE);
	}
	
	/**
	 * NavalArena constructor, calls Arena's constructor
	 * initializes friction, water, surface, body with default values
	 * @param length: Arena's length (will use it for the racers' finish point)
	 * @param maxRacers: Arena's maximum racers (max activeRacers ArrayList size)
	 */
	public NavalArena(double length, int maxRacers){
		super(length,maxRacers,DEFAULT_FRICTION);
		setWater(Water.SWEET);
		setSurface(WaterSurface.FLAT);
		setBody(Body.LAKE);
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
		if(!(newRacer instanceof NavalRacer)) {
			throw new RacerTypeException(racerClass,"Naval");
		}
		else {
			super.addRacer(newRacer);
		}
	}
	
	/**
	 * set the object's water
	 * @param water
	 * @return true, since it's always set successfully
	 */
	private boolean setWater(Water water) {
		this.water = water;
		return true;
	}
	
	/**
	 * set the object's surface
	 * @param surface
	 * @return true, since it's always set successfully
	 */
	private boolean setSurface(WaterSurface surface) {
		this.surface = surface;
		return true;
	}
	
	/**
	 * set the object's body
	 * @param body
	 * @return true, since it's always set successfully
	 */
	private boolean setBody(Body body) {
		this.body = body;
		return true;
	}
	
	/**
	 * get the object's water
	 * @return object's water
	 */
	private Water getWater() {
		return this.water;
	}
	
	/**
	 * get the object's surface
	 * @return object's surface
	 */
	private WaterSurface getSurface() {
		return this.surface;
	}
	
	/**
	 * get the object's body
	 * @return object's body
	 */
	private Body getBody() {
		return this.body;
	}
}
