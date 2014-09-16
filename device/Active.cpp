#include <stdio.h>
#include <iostream>
#include <fstream>
#include <Active.h>

int Active::flush()
{
	static std::ofstream file;
	file.open(ACTIVE_FILENAME);
	// Somehow write current data in buffer to a device
	for(int i = 0; i < BUFFER_SIZE; i++)
		file << buffer[i];
	file.close();
	return 0;
}