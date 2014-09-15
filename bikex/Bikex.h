#ifndef BIKEX_H
#define BIKEX_H

#include <Battery.h>
#include <Oximetry.h>
#include <Speed.h>
#include <Direction.h>
#include <Break.h>
#include <Unity.h>
#include <Ovr.h>

typedef struct _position
{
	double x, y, z;
} xyz;

class Bikex
{
public:

	/**
	 *	Time difference, it meas the time window until the next frame
	 *	it's very useful to determine the next position by the speed
	 *	dt is in seconds (will be very small)
	 */
	float dt;

	/**
	 *	How many frames per second
	 */
	int FRAME_RATE;

	/**
	 *	Current player's position
	 */
	xyz currPosition;

	/**
	 *	Current player's rotation
	 */
	xyz currRotation;

	/**
	 *	Current battery status
	 */
	char currBattery;

	/**
	 *	Current player's heart beat rate
	 */
	char currHearBeat;

	/**
	 *	Current player's distance already biked, in meters
	 */
	int currDistance;

	/**
	 *	Current player's speed (intensity of going forward)
	 */
	char currSpeed;

	/**
	 *	Current player's direction, if turning to the right or to the left, to the left
	 */
	char currDirection;

	/**
	 *	Current player's angle referred to the origin point [0, 0]
	 *	it's going to be helpful when the player is making a curve
	 *	speed and direction will vary depending on wich angle the player is
	 *	turning to
	 *	The angle is in degress: from 0 to 360
	 */
	float currAngle;

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

	/**
	 *	Writes 
	 */
};

#endif