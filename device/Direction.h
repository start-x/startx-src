#ifndef DIRECTION_H
#define DIRECTION_H

#include <Passive.h>

class Direction : public Passive
{
public:
	int getData(unsigned char &data);
};

#endif