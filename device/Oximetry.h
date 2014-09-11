#ifndef OXIMETRY_H
#define OXIMETRY_H

#include <Passive.h>

class Oximetry : public Passive
{
public:
	int getData(char &data);
};

#endif