/**
	I'm trying to run a simple OVR detection here
	compile with: 
		g++ -I../sdk/src simple_OVR_detection.cpp ../sdk/lib/linux/Release/x86_64/libovr.a -lGL -ludev -lXrandr
*/
#include <iostream>
#include "OVR_CAPI.h"

using namespace std;

int main()
{
	

	cout << "Working fine!" << endl;
	return 0;
}
