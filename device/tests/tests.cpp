#include <iostream>
#include <Battery.h>
#include <Oximetry.h>
#include <Speed.h>
#include <Direction.h>
#include <Break.h>

using namespace std;

void test_initAllPassiveDevices()
{
	Battery b;
	Oximetry o;
	Speed s;
	Direction d;
	char data;

	// Get the data
	Passive::flush();

	b.getData(data);
	std::cout << "Battery '" << data << "' " << std::endl;

	o.getData(data);
	std::cout << "Oximetry '" << data << "' " << std::endl;

	s.getData(data);
	std::cout << "Speed '" << data << "' " << std::endl;

	d.getData(data);
	std::cout << "Direction '" << data << "' " << std::endl;
}

void test_initAllActiveDevices()
{
	Break b;
	char data = 'a';
	b.setData(data);
}

int main()
{
	cout << "Testing sensors" << endl;
	return 0;
}