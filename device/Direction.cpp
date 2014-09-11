#include <Direction.h>

int Direction::getData(char &data)
{
	data = buffer[DIRECTION];
	return 0;
}