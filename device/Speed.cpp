#include <Speed.h>

int Speed::getData(double &data)
{
	data = Device::buffer[SPEED];
	return 0;
}
