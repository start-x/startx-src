#include <Bikex.h>
#include <Battery.h>
#include <Break.h>
#include <Direction.h>
#include <Oximetry.h>
#include <Speed.h>
#include <Ovr.h>
#include <Unity.h>
#include <iostream>

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