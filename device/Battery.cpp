#include <Battery.h>

int Battery::getData(unsigned char &data)
{
	data = buffer[BATTERY];
	return 0;
}