#ifndef DEVICE_H
#define DEVICE_H

typedef enum _deviceType
{
	BREAK,
	OXIMETRY,
	DIRECTION,
	SPEED
} deviceType;

class Device
{
protected:
	void setType(deviceType type);
	deviceType type;
};

#endif