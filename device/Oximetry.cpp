#include <Oximetry.h>

int Oximetry::getData(double &data)
{
	data = buffer[OXIMETRY];
	return 0;
}
