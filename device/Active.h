#ifndef ACTIVE_H
#define ACTIVE_H

#include <Device.h>

#define ACTIVE_FILENAME "files/active.txt"

/**
 *	Represents all devices which will be serving as data sources
 */
class Active : public Device
{
public:

	/**
	 *	Reads s specific char at a device and returns 0 in case of success or != 0 otherwise
	 */
	virtual int setData(unsigned char data) = 0;

	/**
	 *	Flush the current data to the device
	 */
	static int flush();
};

#endif