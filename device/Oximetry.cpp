#include <Oximetry.h>

int Oximetry::getData(char &data)
{
	data = buffer[OXIMETRY];
	return 0;
}