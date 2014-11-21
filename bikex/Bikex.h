#ifndef BIKEX_H
#define BIKEX_H

#include <Battery.h>
#include <Oximetry.h>
#include <Speed.h>
#include <Direction.h>
#include <Break.h>
#include <Unity.h>

#define MAX_DT 100 // 100 == (1/10) * 1000
#define MIN_DT 33 // 33 == (1/30) * 1000
#define SAMPLES_FPS 128
#define POTENTIOMETER_RANGE 1024
#define MAX_ANGLE 60.0
#define NUM_OBSTRUCTIONS 4
#define CIRCUMFERENCE 2.0

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
	float FRAME_RATE;

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
	double currBattery;

	/**
	 *	Current player's heart beat rate
	 */
	double currHearBeat;

	/**
	 *	Current player's distance already biked, in meters
	 */
	int currDistance;

	/**
	 *	Current player's speed (intensity of going forward)
	 */
	double currSpeed;

	/**
	 *	Current player's direction, if turning to the right or to the left, to the left
	 */
	double currDirection;

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
	Unity * unity;

	/**
	 *	Our own reference to Battery
	 */
	Battery * battery;

	/**
	 *	Our own reference to Break
	 */
	Break * _break;

	/**
	 *	Our own reference to Direction
	 */
	Direction * direction;

	/**
	 *	Our own reference to Oximetry
	 */
	Oximetry * oximetry;

	/**
	 *	Our own reference to Speed
	 */
	Speed * speed;

	Bikex();
	~Bikex();

	/**
	 *	Initialize Bikex
	 */
	void init();

	/**
	 *	Print current Bikex state values
	 */
	void printCurrState();

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
};

#endif
