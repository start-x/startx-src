#include <Speed.h>

int Speed::getData(unsigned char &data)
{
	data = Device::buffer[SPEED];
	return 0;
}