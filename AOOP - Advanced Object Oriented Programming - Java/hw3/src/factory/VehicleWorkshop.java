/**
 * @author Noam Karasso
 */
package factory;

import game.racers.Racer;
import utilities.EnumContainer.Color;

/**
 * The VehicleWorkshop class provides operations related to working with vehicles
 */
public class VehicleWorkshop {

	/**
     * Creates a clone of the specified vehicle
     * @param vehicle the vehicle to clone
     * @return the cloned vehicle
     */
	public Racer cloneVehicle(Racer vehicle) {
		Racer racer = vehicle.clone();
		changeSN(racer);
		return racer;
	}
	
	/**
     * Changes the color of the specified vehicle
     * @param vehicle the vehicle to paint
     * @param color   the new color of the vehicle
     */
	public void paintVehicle(Racer vehicle, Color color) {		
		vehicle.setColor(color);
		vehicle.setIcon();
	}
	
	/**
     * Changes the serial number of the specified vehicle to the static serial field in the Racer's class and increases it
     * @param vehicle the vehicle to update the serial number for
     * @param SN      the new serial number
     */
	public void changeSN(Racer vehicle) {
		vehicle.setSerialNumber(Racer.getSerial());
		Racer.increaseSerial();
	}
}
