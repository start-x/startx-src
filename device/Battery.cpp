#include <Battery.h>

int Battery::getData(char &data)
{
	readData(&data);
	return 0;
}