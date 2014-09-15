#include <Bikex.h>
#include <Battery.h>
#include <Break.h>
#include <Direction.h>
#include <Oximetry.h>
#include <Speed.h>
#include <Ovr.h>
#include <Unity.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace std;


Bikex::Bikex()
{
	cout << "Initiating Bikex" << endl;
	Battery bat;
	Break br;
	Direction dir;
	Oximetry oxi;
	Speed sp;
	Ovr ovr;
	Unity unity;
}

Bikex::~Bikex()
{
	cout << "Termination Bikex" << endl;
}

void Bikex::calculatePlayerPosition()
{
	// TODO: check how the values are gonna come and check the relation between them
	// TODO: calculate the change of angle
	this->currAngle = 90;

	// TODO: check the case when the player is in a curve: depends on the angle
	this->currPosition.x = this->currPosition.x + (this->currSpeed * this->dt);

	// TODO: how are we gonna set the turn ? it also has to come as speed ?
	this->currPosition.z = this->currPosition.z + (this->currDirection * this->dt);

	// Note, DO NOT set position.y, it'll be totally responsability of the simulation
}

void Bikex::calculatePlayerRotation()
{
	// NOTE: it's probably not like this how we do, again let's check the values
	double garbage;
	ovr.getXYZW(&this->currRotation.x, &this->currRotation.y, &this->currRotation.z, &garbage);
}

void Bikex::setBreakIntensity()
{
	// TODO: do some calculations to set right amount of intensity
	int altitude = unity.getPlayerAltitude();
	_break.setData(altitude);
}

int Bikex::writeDevices()
{
	static char info[256];

	// First, common sensors
	Active::flush();

	// Now Unity stuff
	sprintf(info, "Speed: %i | Heart: %i | Dist: %i | Batt: %i", 
		this->currSpeed, this->currHearBeat, this->currDistance, this->currBattery);
	unity.setInfo(info);
	unity.setPlayerPosition(this->currPosition.x, this->currPosition.z);
	unity.setPlayerRotation(this->currRotation.x, this->currRotation.x, this->currRotation.z);

	return 0;
}

int Bikex::readDevices()
{
	// Make all comon readings
	Passive::flush();
	speed.getData(this->currSpeed);
	direction.getData(this->currDirection);
	oximetry.getData(this->currHearBeat);
	battery.getData(this->currBattery);

	return 0;
}

void Bikex::play()
{
	bool keepGoing = true;
	while(keepGoing)
	{
		// Read all sensors 
		this->readDevices();

		// Calculate and set player's position and rotation based on sensors readings
		this->calculatePlayerPosition();
		this->calculatePlayerRotation();

		// Before rendering frame, write to all devices
		this->writeDevices();

		// Finally tells unity it can render the frame
		unity.render();

		/*
		However if you use this fps value directly and just display it to the screen, you'll find it's rather irratic. The amount of time it takes to complete a frame will typically vary a bit from frame to frame, and this will make it hard to read and not so useful. To get around this, you can filter your result a bit taking a bunch of samples and averaging the result.



		static const int NUM_FPS_SAMPLES = 64;

		float fpsSamples[NUM_FPS_SAMPLES]

		int currentSample = 0;



		float CalcFPS(int dt)

		{

		    fpsSamples[currentSample % NUM_FPS_SAMPLES] = 1.0f / dt;

		    float fps = 0;

		    for (int i = 0; i < NUM_FPS_SAMPLES; i++)

		        fps += fpsSamples[i];

		    fps /= NUM_FPS_SAMPLES;

		    return fps;

		}
		*/

		// Now we sleep
		usleep(calcFPS(0));
	}

}

float Bikex::calcFPS(int dt)
{
	return 0.0;
}
