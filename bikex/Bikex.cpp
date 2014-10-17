#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <Bikex.h>

/**
 *	Get time difference between two timestamps
 */
static int time_diff(struct timeval x , struct timeval y)
{
    int x_ms , y_ms , diff;
     
    x_ms = x.tv_sec*1000 + x.tv_usec/1000;
    y_ms = y.tv_sec*1000 + y.tv_usec/1000;
     
    diff = y_ms - x_ms;
     
    return diff;
}

Bikex::Bikex()
{
	std::cout << "Creating Bikex" << std::endl;

	this->unity = new Unity();
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
	currPosition.y = (unsigned char)altitude;
	_break->setData(altitude);
}

int Bikex::writeDevices()
{
	std::cout << "Writting devices" << std::endl;
	static char info[256];
	static int chars_written;

	// First, common sensors
	Active::flush();

	// Now Unity stuff
	chars_written = sprintf(info, "\rSpeed: %i | Heart: %i | Dist: %i | Batt: %i", 
		this->currSpeed, this->currHearBeat, this->currDistance, this->currBattery);
	unity->setInfo(info, chars_written);
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

	return 0;
}

void Bikex::play()
{

	std::cout << "Playing" << std::endl;
    int samples[SAMPLES_FPS], i_samples = 0;
    int diff = 0, total = 0, average = 0, i = 0;
    struct timeval before , after;

    for(i = 0; i < SAMPLES_FPS; i++)
        samples[i] = 30;
    
	while(1)
	{
        printf("\rmedia: %d", average);

        // Begin time count
		gettimeofday(&before , NULL);

		// Read all sensors 
		this->readDevices();

		// Calculate and set player's position and rotation based on sensors readings
		this->calculatePlayerPosition();
		this->calculatePlayerRotation();
		this->setBreakIntensity();

		// Before rendering frame, write to all devices
		this->writeDevices();

		// Finally tells unity it can render the frame
		// TODO: checks how to make unity wait until next frame rendering
		unity->render();

		gettimeofday(&after , NULL);

        // Time taking task
        for(i = total = 0; i < SAMPLES_FPS; i++)
            total += samples[i];

        diff = time_diff(before , after);
        samples[i_samples++] = diff;
        if(i_samples == SAMPLES_FPS) 
        	i_samples = 0;

        average = total/SAMPLES_FPS;
        if(average < MIN_DT) 
        	average = MIN_DT;

        if(diff < average)
            usleep((average - diff)*1000);
	}
}
