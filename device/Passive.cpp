#include <Passive.h>

int Passive::flush()
{
	// Somehow erase old data in buffer and get new information
	// read(buffer)
	buffer[0] = 's';
	buffer[1] = 'o';
	buffer[2] = 'm';
	buffer[3] = 'e';
	buffer[4] = 'd';
	buffer[5] = 'a';
	buffer[6] = 't';
	buffer[7] = 'a';
	return 0;
}