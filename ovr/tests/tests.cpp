#include <StartXOVR.h>
#include <iostream>

using namespace std;

bool test_StartXOVR()
{
	StartXOVR sxovr;
	sxovr.initOVR();
	sxovr.startSensor();
	cout << sxovr;

	return false;
}

int main()
{
	test_StartXOVR();
	cout << "Testing ovr" << endl;
	return 0;
}