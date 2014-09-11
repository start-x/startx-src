#ifndef DEVICE_H
#define DEVICE_H

typedef enum _deviceType
{
	BATTERY 	= 0,
	OXIMETRY 	= 1,
	SPEED 		= 2,
	DIRECTION 	= 3,
	BREAK 		= 4
} deviceType;

class Device
{
protected:
	static char buffer[256];
};

#endif