#ifndef OVR_H
#define OVR_H

#ifndef DEBUG
	#define DEBUG 1
#endif

#include <ostream>
#include <OVR_CAPI.h>

/**
 *	Try to put everything related to OVR in this class
 *	This way, other parts of StartX project will only need to call this class
 */
class Ovr 
{
public:
	// ******************* Attributes *********************************
	/**
	 *	Flag to inform the class when to create and destroy OVR devices
	 */
	bool ovrInitiated;

	/**
	 *	This is the object holder for the OVR
	 */
	ovrHmd hmd;

	/**
	 *	Holds the description of the OVR
	 */
	ovrHmdDesc hmdDesc;

	// ******************* Methods (constructors first) **************
	/**
	 *	Some useful initialization process
	 */
	Ovr();

	/**
	 *	Destroys any previous OVR objects create by initOVR
	 */
	~Ovr();

	/**
	 *	Creates a OVR device
	 */
	bool initOVR();

	/**
	 *	Print all the information about this class
	 */
	friend std::ostream& operator<<(std::ostream&, const Ovr&);

	/**
	 *	Start the HMD so the next step begins the tracking
	 */
	bool startSensor();

	// ********************* Methods declared in UML *************************

	/**
	 *	Get current state from OVR
	 */
	void getXYZW(float * x, float * y, float * z, float * w);
};

#endif