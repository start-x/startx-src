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

}

void Bikex::calculatePlayerRotation()
{

}

void Bikex::setBreakIntensity()
{

}

int Bikex::writeDevices()
{
	return 0;
}

int Bikex::readDevices()
{
	return 0;
}

void Bikex::play()
{
	bool keepGoing = true;
	while(keepGoing)
	{

		unity;
		ovr;
		battery;
		_break;
		direction;
		oximetry;
		speed;

		calculatePlayerPosition();
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

		usleep(calcFPS(0));
	}

}

float Bikex::calcFPS(int dt)
{
	return 0.0;
}
