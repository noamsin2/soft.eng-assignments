/**
 * @author Noam Karasso
 */
package factory;

import java.lang.reflect.InvocationTargetException;

import game.race.Race;

/**
 * The RaceEngineer class is responsible for constructing a race using the provided BuilderRace implementation
 */
public class RaceEngineer {
	private BuilderRace builderRace; 
	
	/**
     * Constructs a RaceEngineer object with the specified BuilderRace implementation
     * @param builderRace the BuilderRace implementation to use
     */
	public RaceEngineer(BuilderRace builderRace){ 
		this.builderRace = builderRace; 
	} 
	
	/**
     * Retrieves the constructed race
     * @return the constructed race
     */
	public Race getRace() { 
		return this.builderRace.getRace(); 
	} 
	
	/**
     * Constructs the race with the specified number of racers in a specific order
     * @param N the number of racers to include in the race
     * @throws ClassNotFoundException    if the specified class is not found
     * @throws NoSuchMethodException     if the specified method is not found
     * @throws SecurityException         if a security violation occurs
     * @throws InstantiationException    if an instance of the class cannot be created
     * @throws IllegalAccessException    if the access to a class, field, or method is denied
     * @throws IllegalArgumentException  if an illegal argument is provided
     * @throws InvocationTargetException if an exception occurs during method invocation
     */
	public void constructRace(int N) throws ClassNotFoundException, NoSuchMethodException, SecurityException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException { 
		this.builderRace.buildArena(); 
		this.builderRace.buildRacers(N);
	} 
}
