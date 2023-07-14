/**
 * @author Noam Karasso
 */
package factory;


import java.lang.reflect.InvocationTargetException;
import game.race.Race;

/**
 * The BuilderRace interface defines the contract for building a race
 * It provides methods to build racers, arenas, and retrieve the race object
 */
public interface BuilderRace {
	public void buildRacers(int N);
	public void buildArena() throws ClassNotFoundException, NoSuchMethodException, SecurityException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException; 
	public Race getRace();
	
}
