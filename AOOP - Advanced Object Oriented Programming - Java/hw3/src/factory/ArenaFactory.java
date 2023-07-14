/**
 * @author Noam Karasso
 */
package factory;

import java.lang.reflect.InvocationTargetException;

import game.arenas.Arena;

public class ArenaFactory {
	/**
	 *Creates a default arena object of the specified type
	 *@param type The type of the arena ("Air", "Land", or "Naval")
	 *@return The created Arena object
	 *@throws ClassNotFoundException If the specified arena class cannot be found
	 *@throws NoSuchMethodException If the constructor of the specified arena class cannot be found
	 *@throws SecurityException If a security violation occurs while trying to access the constructor
	 *@throws InstantiationException If an instance of the specified arena class cannot be created
	 *@throws IllegalAccessException If access to the constructor is denied
	 *@throws IllegalArgumentException If an illegal argument is passed to the constructor
	 *@throws InvocationTargetException If an exception occurs while invoking the constructor
	 */
	public Arena createArena(String type) throws ClassNotFoundException, NoSuchMethodException, SecurityException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
		RaceBuilder builder = RaceBuilder.getInstance();
		Arena arena = null;
			switch (type) {
			case "Air":
				arena = builder.buildArena("game.arenas.air.AerialArena");
				break;
			case "Land":
				arena = builder.buildArena("game.arenas.land.LandArena");
				break;
			case "Naval":
				arena = builder.buildArena("game.arenas.naval.NavalArena");
			}
			return arena;	
	}
	
	/**
	 *Creates an arena object of the specified type with the given length and maximum number of racers
	 *@param type The type of the arena ("Air", "Land", or "Naval")
	 *@param length The length of the arena
	 *@param maxRacers The maximum number of racers allowed in the arena
	 *@return The created Arena object
	 *@throws ClassNotFoundException If the specified arena class cannot be found
	 *@throws NoSuchMethodException If the constructor of the specified arena class cannot be found
	 *@throws SecurityException If a security violation occurs while trying to access the constructor
	 *@throws InstantiationException If an instance of the specified arena class cannot be created
	 *@throws IllegalAccessException If access to the constructor is denied
	 *@throws IllegalArgumentException If an illegal argument is passed to the constructor
	 *@throws InvocationTargetException If an exception occurs while invoking the constructor
	 */
	public Arena createArena(String type, double length, int maxRacers) throws ClassNotFoundException, NoSuchMethodException, SecurityException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
		RaceBuilder builder = RaceBuilder.getInstance();
		Arena arena = null;
			switch (type) {
			case "Air":
				arena = builder.buildArena("game.arenas.air.AerialArena", length, maxRacers);
				break;
			case "Land":
				arena = builder.buildArena("game.arenas.land.LandArena", length, maxRacers);
				break;
			case "Naval":
				arena = builder.buildArena("game.arenas.naval.NavalArena", length, maxRacers);
			}
			return arena;	
	}
}