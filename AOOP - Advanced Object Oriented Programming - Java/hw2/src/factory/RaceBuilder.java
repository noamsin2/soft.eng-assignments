/**
 * @author Noam Karasso
 */

package factory;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import game.arenas.Arena;
import game.racers.Racer;

/**
 * this class builds an arena with competitors using dynamic loading
 */
public class RaceBuilder {
	private static RaceBuilder instance = null;
	private ClassLoader classLoader;
	private Class<?> classObject;
	private Constructor<?> constructor;

	/**
	 * private constructor which is accessible only from the "getInstance()" method
	 * to make sure only one instance is made from this class
	 */
	private RaceBuilder() {
		classLoader = ClassLoader.getSystemClassLoader();
	}

	/**
	 * if an instance of the class doesn't exist we make a new one
	 * activating the function several times doesn't make more instances
	 * and it always returns the same instance
	 * @return instance
	 */
	public static RaceBuilder getInstance() {
		if (instance == null)
			instance = new RaceBuilder();
		return instance;
	}

	/**
	 * builds the arena using user's input as parameters
	 * @param arenaType: type of arena (NavalArena, LandArena, AerialArena, etc..)
	 * @param length: length of the arena(we'll use that for the racer's finish point)
	 * @param maxRacers: maximum racers in an arena, the activeRacers cannot exceed that value 
	 * @return Arena object
	 * @throws ClassNotFoundException: invalid class
	 * @throws NoSuchMethodException: invalid method
	 * @throws SecurityException
	 * @throws InstantiationException
	 * @throws IllegalAccessException
	 * @throws IllegalArgumentException
	 * @throws InvocationTargetException
	 */
	public Arena buildArena(String arenaType, double length, int maxRacers)
			throws ClassNotFoundException, NoSuchMethodException, SecurityException, InstantiationException,
			IllegalAccessException, IllegalArgumentException, InvocationTargetException {
		this.classObject = classLoader.loadClass(arenaType);
		this.constructor = classObject.getConstructor(double.class, int.class);
		return (Arena) this.constructor.newInstance(length, maxRacers);

	}
	/**
	 * builds the non wheeled racer using user's input as parameters
	 * @param racerType: type of racer(horse, helicopter, rowboat, etc..)
	 * @param name: racer's (person) name
	 * @param maxSpeed: the vehicle's maximum speed
	 * @param acceleration: the vehicle's acceleration
	 * @param color: the vehicle's color
	 * @return Racer object
	 * @throws ClassNotFoundException: invalid class
	 * @throws NoSuchMethodException: invalid method
	 * @throws SecurityException
	 * @throws InstantiationException
	 * @throws IllegalAccessException
	 * @throws IllegalArgumentException
	 * @throws InvocationTargetException
	 */
	public Racer buildRacer(String racerType, String name, double maxSpeed, double acceleration,
			utilities.EnumContainer.Color color)
			throws ClassNotFoundException, NoSuchMethodException, SecurityException, InstantiationException,
			IllegalAccessException, IllegalArgumentException, InvocationTargetException {
		this.classObject = classLoader.loadClass(racerType);
		this.constructor = classObject.getConstructor(String.class, double.class, double.class,
				utilities.EnumContainer.Color.class);
		return (Racer) this.constructor.newInstance(name, maxSpeed, acceleration, color);
	}
	/**
	 * builds the wheeled racer using user's input as parameters
	 * @param racerType: type of racer(car, bicycle,airplane, etc..)
	 * @param name: racer's (person) name
	 * @param maxSpeed: the vehicle's maximum speed
	 * @param acceleration: the vehicle's acceleration
	 * @param color: the vehicle's color
	 * @param numOfWheels: the vehicle's number of wheels
	 * @return Racer object
	 * @throws ClassNotFoundException: invalid class
	 * @throws NoSuchMethodException: invalid method
	 * @throws SecurityException
	 * @throws InstantiationException
	 * @throws IllegalAccessException
	 * @throws IllegalArgumentException
	 * @throws InvocationTargetException
	 */
	public Racer buildWheeledRacer(String racerType, String name, double maxSpeed, double
			acceleration, utilities.EnumContainer.Color color, int numOfWheels) throws ClassNotFoundException, NoSuchMethodException, SecurityException,
			InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
		this.classObject = classLoader.loadClass(racerType);
		this.constructor = classObject.getConstructor(String.class, double.class, double.class,
				utilities.EnumContainer.Color.class, int.class);
		return (Racer) this.constructor.newInstance(name, maxSpeed, acceleration, color, numOfWheels);
	}

}