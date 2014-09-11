#include <Speed.h>

int Speed::getData(char &data)
{
	data = buffer[SPEED];
	return 0;
}