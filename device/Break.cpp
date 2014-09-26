#include <Break.h>

int Break::setData(unsigned char data)
{
	buffer[BREAK] = data;
	return 0;
}