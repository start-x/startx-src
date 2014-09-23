#include <Direction.h>

int Direction::getData(unsigned char &data)
{
	data = buffer[DIRECTION];
	return 0;
}