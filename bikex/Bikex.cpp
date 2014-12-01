#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <Bikex.h>

/**
 *	degrees of a circumference
 */
#define CIRC_ANGLE 360.0

/**
 *	Constant to transfer meters per second to kilometer per hour
 */
#define MPS_TO_KMH 3.6

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

// /**	
//  *	Node for cyclic list
//  */
// struct _node
// {
// 	double value;
// 	_node * next;
// } node;

// /**
//  *	Cyclic list
//  */
// class ciclList
// {
// public:
// 	node * head;

// 	ciclList(int numNodes)
// 	{
// 		this->head = new node;
// 		this->head->value = 0.0;

// 		node * prev, curr;
// 		prev = this->head;
// 		for(int i = 0; i < numNodes; i++)
// 		{
// 			curr = new node;
// 			curr->value = 0.0;
// 			prev->next = curr;
// 			prev = curr;
// 		}
// 		curr->next = this->head;
// 	}

// 	double average()
// 	{
// 		node * tmp = this->head->next;
// 		double total = this->head->value;
// 		int numNodes = 1;

// 		while(tmp != this->head)
// 		{
// 			total += tmp->value;
// 			numNodes++;
// 			tmp = tmp->next;
// 		}
// 	}

// 	double add(double value)
// 	{
// 		this->head->value = value;
// 		this->head = this->head->next;
// 	}
// };

/**
 *	Represents the range of angles according to the range sent by the potenciometer
 */
double angles[POTENTIOMETER_RANGE];

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

  int jump = (POTENTIOMETER_RANGE/2)/MAX_ANGLE;
  int tmpAngles = -MAX_ANGLE;

  for(int i = 0; i < POTENTIOMETER_RANGE; i+=jump)
  {
    for(int j = 0; j < jump; j++)
    {
      angles[i+j] = (((double)tmpAngles/10.0) + (j/100.0));
    }
    tmpAngles++;
  }
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

void Bikex::calculatePlayerSpeed()
{
	//std::cout << "Calculating player speed" << std::endl;
	// double angle = CIRC_ANGLE / (double)NUM_OBSTRUCTIONS;
	// double distance = (angle * CIRCUMFERENCE) / (double)(90 * 4);
	// this->currSpeed = distance / (this->currSpeed / 100.0);
	// this->currSpeed *= MPS_TO_KMH;
	this->currSpeed *= 1.35;
}

void Bikex::calculatePlayerRotation()
{
	//std::cout << "Calculating player rotation" << std::endl;
	static double previousDirection = 0.0;
	this->currDirection = ((double)angles[(int)this->currDirection] + previousDirection)/2.0;
	previousDirection = this->currDirection;
}

void Bikex::setBreakIntensity()
{
	//std::cout << "Setting break intensity" << std::endl;
	// TODO: do some calculations to set right amount of intensity
	int altitude = unity->getPlayerAltitude();
	currPosition.y = (unsigned char)altitude;
	_break->setData(altitude);
}

int Bikex::writeDevices()
{
	//std::cout << "Writting devices" << std::endl;
	static char info[256];
	static int chars_written;

	// First, common sensors
	Active::flush();

	// Now Unity stuff
	chars_written = sprintf(info, "\rSpeed: %lf | Heart: %lf | Dist: %d | Batt: %lf", 
		this->currSpeed, this->currHearBeat, this->currDistance, this->currBattery);
	unity->setInfo(info, chars_written);
	unity->setPlayerSpeed(this->currSpeed);
	unity->setPlayerRotation(this->currDirection);

	return 0;
}

int Bikex::readDevices()
{
	//std::cout << "Reading devices" << std::endl;
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
        // Begin time count
		gettimeofday(&before , NULL);

		// Read all sensors 
		this->readDevices();

		// Calculate and set player's position and rotation based on sensors readings
		this->calculatePlayerSpeed();
		this->calculatePlayerRotation();
		this->setBreakIntensity();

		// Before rendering frame, write to all devices
		this->writeDevices();

		printf("\rSpeed: %.2f km/h, Angle: %.2f °", this->currSpeed, this->currDirection);

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
