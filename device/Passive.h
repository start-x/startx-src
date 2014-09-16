#ifndef PASSIVE_H
#define PASSIVE_H

#include <Device.h>

#define PASSIVE_FILENAME "files/passive.txt"

/**
 *	Represents all devices which will be serving as data sources
 */
class Passive : public Device
{
public:

	/**
	 *	Reads specific char at from a device and returns 0 in case of success or != 0 otherwise
	 */
	virtual int getData(char &data) = 0;

	/**
	 *	Flush the old data and get the new one
	 */
	static int flush();
};

#endif