#include <sensors.h>
#include <iostream>

using namespace std;

sensors::sensors()
{
	cout << "Initiating sensors" << endl;
}

sensors::~sensors()
{
	cout << "Termination sensors" << endl;
}

char sensor_ox()
{
	return 'a';
}
