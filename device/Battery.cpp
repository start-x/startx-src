#include <Battery.h>

int Battery::getData(double &data)
{
	data = buffer[BATTERY];
	return 0;
}
