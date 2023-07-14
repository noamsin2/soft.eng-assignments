/**
 * @author Noam Karasso
 */

package game.arenas.air;

import game.arenas.Arena;
import game.arenas.exceptions.*;
import game.racers.Racer;
import game.racers.air.AerialRacer;
import utilities.EnumContainer.*;

/**
 * The AerialArena class extends the Arena class and represents an aerial racing arena
 */
public class AerialArena extends Arena {
	final static double DEFAULT_FRICTION = 0.4;
	final static int DEFAULT_MAX_RACERS = 6;
	final static int DEFAULT_LENGTH = 1500;
	Vision vision;
	Weather weather;
	Height height;
	Wind wind;
	
	/**
	 * AerialArena default constructor, initializes all fields with default values
	 * calls Arena's constructor
	 */
	public AerialArena(){
		super(DEFAULT_LENGTH,DEFAULT_MAX_RACERS,DEFAULT_FRICTION);
		setVision(Vision.SUNNY);
		setWeather(Weather.DRY);
		setHeight(Height.HIGH);
		setWind(Wind.HIGH);
	}
	
	/**
	 * AerialArena constructor, calls Arena's constructor
	 * initializes friction, vision, weather, height, wind with default values
	 * @param length: Arena's length (will use it for the racers' finish point)
	 * @param maxRacers: Arena's maximum racers (max activeRacers ArrayList size)
	 */
	public AerialArena(double length, int maxRacers){
		super(length,maxRacers,DEFAULT_FRICTION);
		setVision(Vision.SUNNY);
		setWeather(Weather.DRY);
		setHeight(Height.HIGH);
		setWind(Wind.HIGH);
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
		if(!(newRacer instanceof AerialRacer)) {
			throw new RacerTypeException(racerClass,"Aerial");
		}
		else {
			super.addRacer(newRacer);
		}
	}
	
	/**
	 * set the object's vision
	 * @param vision
	 * @return true, since it's always set successfully
	 */
	private boolean setVision(Vision vision) {
		this.vision = vision;
		return true;
	}
	
	/**
	 * set the object's weather
	 * @param weather
	 * @return true, since it's always set successfully
	 */
	private boolean setWeather(Weather weather) {
		this.weather = weather;
		return true;
	}
	
	/**
	 * set the object's height
	 * @param height
	 * @return true, since it's always set successfully
	 */
	private boolean setHeight(Height height) {
		this.height = height;
		return true;
	}
	
	/**
	 * set the object's wind
	 * @param wind
	 * @return true, since it's always set successfully
	 */
	private boolean setWind(Wind wind) {
		this.wind = wind;
		return true;
	}
	
	/**
	 * get the object's vision
	 * @return object's vision
	 */
	private Vision getVision() {
		return this.vision;
	}
	
	/**
	 * get the object's weather
	 * @return object's weather
	 */
	private Weather getWeather() {
		return this.weather;
	}
	
	/**
	 * get the object's height
	 * @return object's height
	 */
	private Height getHeight() {
		return this.height;
	}
	
	/**
	 * get the object's wind
	 * @return object's wind
	 */
	private Wind getWind() {
		return this.wind;
	}
}
