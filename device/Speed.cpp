#include <Speed.h>

int Speed::getData(char &data)
{
	data = Device::buffer[SPEED];
	return 0;
}