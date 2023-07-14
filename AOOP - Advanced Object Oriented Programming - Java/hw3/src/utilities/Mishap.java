/**
 * @author Noam Karasso
 */

package utilities;

import java.text.DecimalFormat;

/**
 *the Mishap class represents a malfunction that can occur in vehicles
 *a mishap can be fixable or unfixable and may require a certain number of turns to fix
 *the mishap may also reduce the speed of the vehicle by a certain factor
 */
public class Mishap {
	private boolean fixable;
	private double reductionFactor;
	private int turnsToFix;
	
	/**
     * Constructor for Mishap class
     * @param fixable A boolean indicating whether the mishap is fixable
     * @param turnsToFix The number of turns required to fix the mishap
     * @param reductionFactor The factor by which the mishap reduces speed
     */
	Mishap(boolean fixable, int turnsToFix, double reductionFactor){
		setFixable(fixable);
		setTurnsToFix(turnsToFix);
		setReductionFactor(reductionFactor);
	}
	
	 /**
     * Decrements the number of turns required to fix the mishap by 1
     */
	public void nextTurn() {
		if(getFixable()) {
			setTurnsToFix(turnsToFix-1);
		}
	}
	
	/**
     * Returns a String representation of the Mishap object
     * @return A String representation of the Mishap object
     */
	public String toString() {
		DecimalFormat numberFormat = new DecimalFormat("#.##");
		return "(" + fixable + ", " + turnsToFix + ", " + numberFormat.format(reductionFactor) + ")";
	}
	
	/**
     * Sets the fixable attribute of the Mishap object
     * @param fixable A boolean indicating whether the mishap is fixable
     * @return A boolean indicating whether the operation was successful
     */
	private boolean setFixable(boolean fixable) {
		this.fixable = fixable;
		return true;
	}
	
	/**
     * Sets the reductionFactor attribute of the Mishap object
     * @param reductionFactor The factor by which the mishap reduces speed
     * @return A boolean indicating whether the operation was successful
     */
	private boolean setReductionFactor(double reductionFactor) {
		this.reductionFactor = reductionFactor;
		return true;
	}
	
	/**
     * Sets the turnsToFix attribute of the Mishap object
     * @param turnsToFix The number of turns required to fix the mishap
     * @return A boolean indicating whether the operation was successful
     */
	private boolean setTurnsToFix(int turnsToFix) {
		this.turnsToFix = turnsToFix;
		return true;
	}
	
	/**
     * Returns the fixable attribute of the Mishap object
     * @return A boolean indicating whether the mishap is fixable
     */
	public boolean getFixable() {
		return this.fixable;
	}
	
	 /**
     * Returns the reductionFactor attribute of the Mishap object
     * @return The factor by which the mishap reduces speed
     */
	public double getReductionFactor() {
		return this.reductionFactor;
	}
	
	/**
     * Returns the turnsToFix attribute of the Mishap object
     * @return The number of turns required to fix the mishap
     */
	public int getTurnsToFix() {
		return this.turnsToFix;
	}

}
