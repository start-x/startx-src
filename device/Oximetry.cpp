#include <Oximetry.h>

int Oximetry::getData(unsigned char &data)
{
	data = buffer[OXIMETRY];
	return 0;
}