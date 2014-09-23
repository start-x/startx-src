#ifndef BREAK_H
#define BREAK_H

#include <Active.h>

class Break : public Active
{
public:
	int setData(unsigned char data);
};

#endif