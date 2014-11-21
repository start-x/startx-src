#ifndef DEVICE_H
#define DEVICE_H

#include <DeviceType.h>

#define BUFFER_SIZE 256
#define PYTHON_PROGRAM "device/scripts/main.py"

class Device
{
public:
	/**
	 *	In order to have the python program working, we need to create a 
	 *	whole new process for it, and this is its pid
	 */
	static int pythonPid;

	/**
	 *	Make proper device initialization
	 */
	static void init();

	/**
	 *	Disconnect devices and ends python program
	 */
	static void destroy();

protected:
	static int buffer[BUFFER_SIZE];
};

#endif
