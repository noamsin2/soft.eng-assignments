/**
 * @author Noam Karasso
 */

package utilities;

import java.util.Random;
/**
 * the Fate class represents the random events that can happen in the system
 * it provides methods for generating and managing mishaps that can occur
 */
public class Fate {

	private static Random rand = new Random();

	public static boolean disable() {
		return rand.nextInt(10) > 7;
	}
	
	public static boolean breakDown() {
		return rand.nextInt(10) > 7;
	}

	public static boolean generateFixable() {
		return rand.nextInt(10) > 7;
	}

	public static Mishap generateMishap() {
		return new Mishap(generateFixable(), generateTurns(), generateReduction());
	}

	private static float generateReduction() {
		return rand.nextFloat();
	}

	private static int generateTurns() {
		return rand.nextInt(5) + 1;
	}

	public static void setSeed(int seed) {
		rand.setSeed(seed);
	}

}
