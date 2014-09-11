#ifndef PASSIVE_H
#define PASSIVE_H

#include <Device.h>

class Passive : public Device
{
public:

	/**
	 *	Writes a char at a device and returns 0 in case of success or != 0 otherwise
	 */
	virtual int getData(char &data) = 0;

	/**
	 *	Read the data from a device to buffer
	 */
	int readData(void * buffer);
};

#endif