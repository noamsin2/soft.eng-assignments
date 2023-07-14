/**
 * @author Noam Karasso
 */
package game.race;

import java.util.ArrayList;

import game.arenas.Arena;
import game.racers.Racer;

/**
 * The Race class represents a race
 */
public class Race {
	private Arena arena;
	private ArrayList<Racer> racers;
	
	/**
     * Constructs a new Race object
     */
	public Race() {
		arena = null;
		racers = new ArrayList<Racer>();;
	}

	/**
     * Gets the arena for the race
     * @return the arena for the race
     */
	public Arena getArena() {
		return arena;
	}

	/**
     * Sets the arena for the race
     * @param arena the arena to set
     */
	public void setArena(Arena arena) {
		this.arena = arena;
	}

	/**
     * Gets the list of racers participating in the race
     * @return the list of racers
     */
	public ArrayList<Racer> getRacers() {
		return racers;
	}

	/**
     * Sets the list of racers participating in the race
     * @param racers the list of racers to set
     */
	public void setRacers(ArrayList<Racer> racers) {
		this.racers = racers;
	}
}
