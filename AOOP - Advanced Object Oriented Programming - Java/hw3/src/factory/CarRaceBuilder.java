/**
 * @author Noam Karasso
 */
package factory;

import java.lang.reflect.InvocationTargetException;
import game.race.Race;
import game.racers.Racer;
import game.racers.land.Car;

/**
 * The CarRaceBuilder class implements the BuilderRace interface to build a car race
 * It constructs a very specific car race with land arena and 'N' racers
 */
public class CarRaceBuilder implements BuilderRace{
	private Race race;
	
	/**
     * Constructs a new CarRaceBuilder object and initializes the race
     */
	public CarRaceBuilder() {
		this.race = new Race();
	}
	
	/**
     * Builds the arena for the race
     * @throws ClassNotFoundException    if the specified class is not found
     * @throws NoSuchMethodException     if the specified method is not found
     * @throws SecurityException         if a security violation occurs
     * @throws InstantiationException    if an instance of the class cannot be created
     * @throws IllegalAccessException  if the access to a class, field, or method is denied
     * @throws IllegalArgumentException if an illegal argument is provided
     * @throws InvocationTargetException if an exception occurs during method invocation
     */
	public void buildArena() throws ClassNotFoundException, NoSuchMethodException, SecurityException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
		ArenaFactory AF = new ArenaFactory();
		race.setArena(AF.createArena("Land"));
	}

	/**
     * Builds the racers for the race by cloning
     * @param N the number of racers to build
     */
	@Override
	public void buildRacers(int N) {
		VehicleWorkshop vehicleWS = new VehicleWorkshop();
		for(int i =0;i<N;i++) {
			Racer racer = vehicleWS.cloneVehicle(new Car());
			race.getRacers().add(racer);
		}
	}

	/**
     * Retrieves the race object
     * @return the race object
     */
	@Override
	public Race getRace() {
		return this.race;
	}

}
