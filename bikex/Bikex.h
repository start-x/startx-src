#ifndef BIKEX_H
#define BIKEX_H

class Bikex
{
public:
	Bikex();
	~Bikex();

	// ********************* Methods declared in UML *************************

	/**
	 *	Calculate the next x and z values for Player position
	 */
	void calculatePlayerPosition();

	/**
	 *	Calculate the next x, y and z values for Player rotation
	 */
	void calculatePlayerRotation();

	/**
	 *	Based on y value from unity, set the intensity on the break
	 */
	void setBreakIntensity();

	/**
	 *	Write all necessary data to active devices
	 *	Return 0 if success != otherwise
	 */
	int writeDevices();

	/**
	 *	Read all necessary data from passive devices
	 *	Return 0 if success != otherwise
	 */
	int readDevices();
};

#endif