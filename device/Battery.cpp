#include <Battery.h>

int Battery::getData(char &data)
{
	data = buffer[BATTERY];
	return 0;
}