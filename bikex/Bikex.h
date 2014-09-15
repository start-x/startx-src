#ifndef BIKEX_H
#define BIKEX_H

#include <Battery.h>
#include <Oximetry.h>
#include <Speed.h>
#include <Direction.h>
#include <Break.h>
#include <Unity.h>
#include <Ovr.h>

class Bikex
{
public:

	/**
	 *	How many frames per second
	 */
	int FRAME_RATE;

	/**
	 *	Our own reference to Unity
	 */
	Unity unity;

	/**
	 *	Our own reference to Ovr
	 */
	Ovr ovr;

	/**
	 *	Our own reference to Battery
	 */
	Battery battery;

	/**
	 *	Our own reference to Break
	 */
	Break _break;

	/**
	 *	Our own reference to Direction
	 */
	Direction direction;

	/**
	 *	Our own reference to Oximetry
	 */
	Oximetry oximetry;

	/**
	 *	Our own reference to Speed
	 */
	Speed speed;

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

	/**
	 *	Method that is going to be executed 30 times a second
	 */
	void play();

	/**
	 *	Calculate how long to sleep before building next frame
	 *	it should return time in u_seconds to wait for the next frame to be built
	 */
	float calcFPS(int dt);
};

#endif