#ifndef BATTERY_H
#define BATTERY_H

#include <Passive.h>

class Battery : public Passive
{
public:
	int getData(unsigned char &data);
};

#endif