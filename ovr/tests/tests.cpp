#include <Ovr.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

void test_Ovr()
{
	Ovr sxovr;
	float x, y, z, w;

	sxovr.initOVR();
	sxovr.startSensor();
	sxovr.getXYZW(&x, &y, &z, &w);
	cout << sxovr;

	// DON'T RUN THIS READING UNLESS YOU HAVE THE OVR CONNECTED
	// OTHERWISE THE REAL DATA IS GONNA BE ERASED
	// ofstream out;
	// out.open("readings_.out");
	// out << "Reads 100 times per second during 10 seconds (10000 readings)\n";
	// int readings_per_second = 100;
	// int one_second = 1000000;
	// int seconds_of_reading = 10;
	// int readings = seconds_of_reading * readings_per_second;
	// unsigned int microseconds = one_second / readings_per_second; // 1000000 is one second

	/**
		for this reading please do (like I did):
		1. Rotate on X axis, first go down and then go up, finish at the original position
		2. Rotate on Y axis, first go left and then go right, finish at the original position
		3. Rotate on Z axis, first turn it like it was to touch your right shoulder, then do the
			same for the left shoulder, finish at the original position
	*/

	// // Try to get 10000 readings
	// for(int i = 0; i < readings; i++)
	// {
	// 	usleep(microseconds);
	// 	sxovr.getXYZW(&x, &y, &z, &w);
	// 	out << "x = " << x << ", y = " << y << ", z = " << z << ", w = " << w << std::endl;
	// }
	// out.close();
}

int main()
{
	test_Ovr();
	cout << "Testing ovr" << endl;
	return 0;
}