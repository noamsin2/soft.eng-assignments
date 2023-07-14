/**
 * @author Noam Karasso
 */
package utilities;

/**
 * the Point class represents a coordinate in a two-dimensional axis 
 */
public class Point {
	private static final int MAX_X = 1000000;
	private static final int MIN_X = 0;
	private static final int MAX_Y = 1000;
	private static final int MIN_Y = 0;
	private double x;
	private double y;

	/**
     * Constructs a new Point with the specified x and y coordinates
     * If the specified x or y value is out of range, sets it to the min boundary value
     * @param x the x coordinate of the point
     * @param y the y coordinate of the point
     */
	public Point(double x, double y) {
		if (!setX(x)) {
			setX(MIN_X);
		}
		if (!setY(y)) {
			setY(MIN_Y);
		}
	}

	 /**
     * Constructs a new Point with x and y coordinates set to 0
     */
	public Point() {
		setX(MIN_X);
		setY(MIN_Y);
	}

	/**
     * Constructs a new Point with the same x and y coordinates as the specified point
     * @param other the point to copy the x and y coordinates from
     */
	Point(Point other) {
		setX(other.getX());
		setY(other.getY());
	}

	/**
     * Sets the x coordinate of this point
     * If the specified value is out of range, returns false and doesn't modify the x coordinate
     * @param x the new x coordinate value
     * @return true if the new x coordinate value is within the valid range; false otherwise
     */
	public boolean setX(double x) {
		if (x >= MIN_X && x <= MAX_X) {
			this.x = x;
			return true;
		}
		return false;
	}

	/**
     * Sets the y coordinate of this point
     * If the specified value is out of range, returns false and doesn't modify the y coordinate
     * @param y the new y coordinate value
     * @return true if the new y coordinate value is within the valid range; false otherwise
     */
	private boolean setY(double y) {
		if (y >= MIN_Y && y <= MAX_Y) {
			this.y = y;
			return true;
		}
		return false;
	}

	/**
     * Returns the x coordinate of this point
     * @return the x coordinate value
     */
	public double getX() {
		return this.x;
	}

	/**
     * Returns the y coordinate of this point
     * @return the y coordinate value
     */
	public double getY() {
		return this.y;
	}
	
	/**
     * Returns a string representation of this point in the form "Point{x: x, y: y}"
     * @return a string representation of this point
     */
	public String toString() {
		return "Point{x: "+ this.x + ", y: " + this.y +"}";
	}

}
