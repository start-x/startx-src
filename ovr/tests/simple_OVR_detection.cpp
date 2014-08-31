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

	// Initializes LibOVR.
	ovr_Initialize();

	// Creates a OVR device
	ovrHmd hmd = ovrHmd_Create(0);

	// Allocate space for some info
	ovrHmdDesc hmdDesc;
	if (hmd)
	{
		// Get more details about the HMD
		ovrHmd_GetDesc(hmd, &hmdDesc);
		cout << "OVR detected!!!" << endl;
	}
	else
	{
		cout << "No OVR detected!!!" << endl;
	}
	// do something with the hmd
	
	ovr_Shutdown();

	cout << "Working fine!" << endl;

	return 0;
}
