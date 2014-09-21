#ifndef DEVICE_H
#define DEVICE_H

#include <DeviceType.h>

#define BUFFER_SIZE 256

class Device
{
protected:
	static char buffer[BUFFER_SIZE];
};

#endif