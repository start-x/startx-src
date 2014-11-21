#ifndef DEVICE_TYPE_H
#define DEVICE_TYPE_H

/**
 *	Shared (msp and bikex) enum to define the order of sensors in the buffer
 */
typedef enum _deviceType
{
	DIRECTION	= 0,
	OXIMETRY 	= 1,
	SPEED 		= 2,
	BATTERY 	= 3,
	BREAK 		= 4
} deviceType;

#endif
