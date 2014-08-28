#include <bikex.h>
#include <breaks.h>
#include <ovr.h>
#include <sensors.h>
#include <unity.h>
#include <iostream>

using namespace std;

bikex::bikex()
{
	cout << "Initiating bikex" << endl;

	// Initiating other modules
	breaks 	b;
	ovr 	o;
	sensors s;
	unity 	u;
}

bikex::~bikex()
{
	cout << "Termination bikex" << endl;
}