#include <Passive.h>

int Passive::readData(void * buffer)
{
	*(char *)buffer = 'a';
	return 0;
}