#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <Bikex.h>

Bikex::Bikex()
{
	std::cout << "Creating Bikex" << std::endl;

	this->unity = new Unity();
	this->ovr = new Ovr();
	this->battery = new Battery();
	this->_break = new Break();
	this->direction = new Direction();
	this->oximetry = new Oximetry();
	this->speed = new Speed();

	this->currPosition.x = 0.0;
	this->currPosition.y = 0.0;
	this->currPosition.z = 0.0;
	this->currRotation.x = 0.0;
	this->currRotation.y = 0.0;
	this->currRotation.z = 0.0;

	dt = 0;
	FRAME_RATE = 0;
	currBattery = 0;
	currHearBeat = 0;
	currDistance = 0;
	currSpeed = 0;
	currDirection = 0;
	currAngle = 0;
}

Bikex::~Bikex()
{
	std::cout << "Termination Bikex" << std::endl;
	delete unity;
	delete ovr;
	delete battery;
	delete _break;
	delete direction;
	delete oximetry;
	delete speed;

	// Termination Devices
	Device::destroy();
}

void Bikex::init()
{
	std::cout << "Initiating Bikex" << std::endl;

	// Ovr initialization
	ovr->init();
	ovr->startSensor();

	// Unity initialization
	unity->init();

	// Devices initialization
	Device::init();
}

void Bikex::printCurrState()
{
	std::cout << "Bikex state" << std::endl;
	std::cout << "dt = " << dt << std::endl;
	std::cout << "FRAME_RATE = " << FRAME_RATE << std::endl;
	std::cout << "currPosition = [" << currPosition.x << ", " << currPosition.y << ", " << currPosition.z << "]" << std::endl;
	std::cout << "currRotation = [" << currRotation.x << ", " << currRotation.y << ", " << currRotation.z << "]" << std::endl;
	std::cout << "currBattery = " << (int)currBattery << std::endl;
	std::cout << "currHearBeat = " << (int)currHearBeat << std::endl;
	std::cout << "currDistance = " << (int)currDistance << std::endl;
	std::cout << "currSpeed = " << (int)currSpeed << std::endl;
	std::cout << "currDirection = " << (int)currDirection << std::endl;
	std::cout << "currAngle = " << currAngle << std::endl;
}

void Bikex::calculatePlayerPosition()
{
	std::cout << "Calculating player position" << std::endl;
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
	std::cout << "Calculating player rotation" << std::endl;
	// NOTE: it's probably not like this how we do, again let's check the values
}

void Bikex::setBreakIntensity()
{
	std::cout << "Setting break intensity" << std::endl;
	// TODO: do some calculations to set right amount of intensity
	int altitude = unity->getPlayerAltitude();
	currPosition.y = (char)altitude;
	_break->setData(altitude);
}

int Bikex::writeDevices()
{
	std::cout << "Writting devices" << std::endl;
	static char info[256];

	// First, common sensors
	Active::flush();

	// Now Unity stuff
	sprintf(info, "Speed: %i | Heart: %i | Dist: %i | Batt: %i", 
		this->currSpeed, this->currHearBeat, this->currDistance, this->currBattery);
	unity->setInfo(info);
	unity->setPlayerPosition(this->currPosition.x, this->currPosition.z);
	unity->setPlayerRotation(this->currRotation.x, this->currRotation.x, this->currRotation.z);

	return 0;
}

int Bikex::readDevices()
{
	std::cout << "Reading devices" << std::endl;
	// Make all comon readings
	Passive::flush();
	speed->getData(this->currSpeed);
	direction->getData(this->currDirection);
	oximetry->getData(this->currHearBeat);
	battery->getData(this->currBattery);

	// Read from Ovr
	double garbage;
	ovr->getXYZW(&this->currRotation.x, &this->currRotation.y, &this->currRotation.z, &garbage);

	return 0;
}

void Bikex::play()
{
	std::cout << "Playing" << std::endl;
	bool keepGoing = true;
	int i = 0;
	while(i++ < 1002)
	{
		// Read all sensors 
		this->readDevices();

		// Calculate and set player's position and rotation based on sensors readings
		this->calculatePlayerPosition();
		this->calculatePlayerRotation();
		this->setBreakIntensity();

		// Before rendering frame, write to all devices
		this->writeDevices();

		// Finally tells unity it can render the frame
		unity->render();

		this->printCurrState();

		/*
		However if you use this fps value directly and just display it to the screen, 
		you'll find it's rather irratic. The amount of time it takes to complete a frame 
		will typically vary a bit from frame to frame, and this will make it hard to read 
		and not so useful. To get around this, you can filter your result a bit taking a 
		bunch of samples and averaging the result.



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
		std::cout << "Playing TODO" << std::endl;
		keepGoing = false;
	}
}

float Bikex::calcFPS(int dt)
{
	std::cout << "Calculating FPS" << std::endl;
	return 1.0;
}
