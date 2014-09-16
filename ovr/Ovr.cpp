#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <Ovr.h>

/**
 *	Data source in case we need to mock Ovr values
 */
static char * mockData = NULL;
static int MOCK_SIZE = 0;

Ovr::Ovr()
{
	if(DEBUG)
		std::cout << "Initializing Ovr" << std::endl;

	this->ovrInitiated = false;
	this->mock = false;
}

Ovr::~Ovr()
{ 
	if(DEBUG)
		std::cout << "Destroying Ovr" << std::endl;

	if(ovrInitiated)
	{
		ovrHmd_Destroy(this->hmd);
		ovr_Shutdown();
	}

	if(mock)
	{
		delete[] mockData;
	}
}

bool Ovr::init()
{
	// Initializes LibOVR.
	ovr_Initialize();

	// Creates a OVR device
	this->hmd = ovrHmd_Create(0);
	if (this->hmd)
	{
		// Get more details about the HMD
		ovrHmd_GetDesc(this->hmd, &this->hmdDesc);
		this->ovrInitiated = true;
		std::cout << "OVR detected" << std::endl;
		return true;
	}

	std::cout << "No OVR detected!!!" << std::endl;
	std::cout << "Creating a Debug version of DK1" << std::endl;
	this->hmd = ovrHmd_CreateDebug(ovrHmd_DK1);
	mock = true;

	if(!this->hmd)
	{
		std::cout << "Something really wrong just happened!" << std::endl;
		exit(-1);
	}

	ovrHmd_GetDesc(this->hmd, &this->hmdDesc);
	this->ovrInitiated = true;

	// If we got here, let's build mockData, dataset to be used as Ovr readings
	std::ifstream file ("files/ovr_mock.txt", std::ios::in | std::ios::binary | std::ios::ate);
	if(file.is_open())
	{
		std::streampos size = file.tellg();
		mockData = new char[size];
		MOCK_SIZE = size;
		file.seekg(0, std::ios::beg);
		file.read(mockData, size);
		file.close();
		std::cout << "Ovr mockData loaded: " << size << " bytes long" << std::endl;
	}
	else
	{
		std::cout << "Failed to load Ovr mockData" << std::endl;
		mockData = new char[1];
		*mockData = '0';
	}

	return this->ovrInitiated;
}

bool Ovr::startSensor()
{
	// Start the sensor which provides the Rift’s pose and motion.
	bool success =  ovrHmd_StartSensor(this->hmd, ovrSensorCap_Orientation | ovrSensorCap_YawCorrection |
		ovrSensorCap_Position | ovrHmdCap_LowPersistence,
		ovrSensorCap_Orientation);

	if(!success)
	{
		std::cout << "The required capabilities are not present!" << std::endl;
		exit(-2);
	}
	return false;
}

void Ovr::getXYZW(double * x, double * y, double * z, double * w)
{
	static int mockIndex = 0;
	// If mock is true, means it's time to mock data
	if(mock)
	{
		if(!mockData)
		{
			std::cout << "No mockData" << std::endl;
			*x = 0.0;
			*y = 0.0;
			*z = 0.0;
			*w = 0.0;
			return;
		}

		if(mockIndex >= MOCK_SIZE)
			mockIndex = 0;

		sscanf(&mockData[mockIndex], "%lf %lf %lf %lf", x, y, z, w);
		//std::cout << "Reading mockData" << std::endl;
		while(mockData[mockIndex] != '\n' && mockIndex++ < MOCK_SIZE); // skip line break
		mockIndex++;
		return;
	}
	// Query the HMD for the sensor state at a given time. "0.0" means "most recent time".
	ovrSensorState ss = ovrHmd_GetSensorState(this->hmd, 0.0);

	int attempts = 10000;

	while(attempts && !(ss.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)))
		attempts--;

	if(attempts)
	{
		ovrPosef pose = ss.Predicted.Pose;

		ovrQuatf orientation = pose.Orientation;
    	ovrVector3f position = pose.Position;

		*x = (double)orientation.x;
		*y = (double)orientation.y;
		*z = (double)orientation.z;
		*w = (double)orientation.w;
		
		//std::cout << "x = " << x << ", y = " << y << ", z = " << z << ", w = " << w << std::endl;

		return;
	}

	*x = 0.0;
	*y = 0.0;
	*z = 0.0;
	*w = 0.0;
}

std::ostream& operator<<(std::ostream& os, const Ovr& sxovr)
{
	os << "***** Ovr ******" << std::endl;
	os << "\tovrInitiated: " << (sxovr.ovrInitiated ? "true" : "false")  << std::endl;

	if(sxovr.ovrInitiated)
	{
		os << "\tType: " << sxovr.hmdDesc.Type << " ";
		switch(sxovr.hmdDesc.Type)
		{
			case ovrHmd_None: os <<  "ovrHmd_None" ; break;
    		case ovrHmd_DK1: os <<   "ovrHmd_DK1"  ; break;
    		case ovrHmd_DKHD: os <<  "ovrHmd_DKHD" ; break;
    		case ovrHmd_DK2: os <<   "ovrHmd_DK2"  ; break;
    		case ovrHmd_Other: os << "ovrHmd_Other"; break;
    		case ovrHmd_CrystalCoveProto: os << "ovrHmd_CrystalCoveProto"; break;
		}	
		os << std::endl;
	}

	os << "\tProduct Name: " << sxovr.hmdDesc.ProductName << std::endl;
	os << "\tManufacturer: " << sxovr.hmdDesc.Manufacturer << std::endl;
	os << "\tHmdCaps: " << sxovr.hmdDesc.HmdCaps << std::endl;
	os << "\tSensorCaps: " << sxovr.hmdDesc.SensorCaps << std::endl;
	os << "\tDistortionCaps: " << sxovr.hmdDesc.DistortionCaps << std::endl;
	os << "\tResolution: h=" << sxovr.hmdDesc.Resolution.w << ", h=" << sxovr.hmdDesc.Resolution.h << std::endl;
	os << "\tWindowsPos: x=" << sxovr.hmdDesc.WindowsPos.x << ", y=" << sxovr.hmdDesc.WindowsPos.x << std::endl;

	os << "\tDefaultEyeFov: " << std::endl <<
		"\t\t[left]UpTan = " << sxovr.hmdDesc.DefaultEyeFov[ovrEye_Left].UpTan << std::endl <<
		"\t\t[left]DownTan = " << sxovr.hmdDesc.DefaultEyeFov[ovrEye_Left].DownTan << std::endl <<
		"\t\t[left]LeftTan = " << sxovr.hmdDesc.DefaultEyeFov[ovrEye_Left].LeftTan << std::endl <<
		"\t\t[left]RightTan = " << sxovr.hmdDesc.DefaultEyeFov[ovrEye_Left].RightTan << std::endl <<
		"\t\t[right]UpTan = " << sxovr.hmdDesc.DefaultEyeFov[ovrEye_Right].UpTan << std::endl <<
		"\t\t[right]DownTan = " << sxovr.hmdDesc.DefaultEyeFov[ovrEye_Right].DownTan << std::endl <<
		"\t\t[right]LeftTan = " << sxovr.hmdDesc.DefaultEyeFov[ovrEye_Right].LeftTan << std::endl <<
		"\t\t[right]RightTan = " << sxovr.hmdDesc.DefaultEyeFov[ovrEye_Right].RightTan << std::endl;

	os << "\tMaxEyeFov: " << std::endl <<
		"\t\t[left]UpTan = " << sxovr.hmdDesc.MaxEyeFov[ovrEye_Left].UpTan << std::endl <<
		"\t\t[left]DownTan = " << sxovr.hmdDesc.MaxEyeFov[ovrEye_Left].DownTan << std::endl <<
		"\t\t[left]LeftTan = " << sxovr.hmdDesc.MaxEyeFov[ovrEye_Left].LeftTan << std::endl <<
		"\t\t[left]RightTan = " << sxovr.hmdDesc.MaxEyeFov[ovrEye_Left].RightTan << std::endl <<
		"\t\t[right]UpTan = " << sxovr.hmdDesc.MaxEyeFov[ovrEye_Right].UpTan << std::endl <<
		"\t\t[right]DownTan = " << sxovr.hmdDesc.MaxEyeFov[ovrEye_Right].DownTan << std::endl <<
		"\t\t[right]LeftTan = " << sxovr.hmdDesc.MaxEyeFov[ovrEye_Right].LeftTan << std::endl <<
		"\t\t[right]RightTan = " << sxovr.hmdDesc.MaxEyeFov[ovrEye_Right].RightTan << std::endl;

	//os << "\tEyeRenderOrder: " << sxovr.hmdDesc.EyeRenderOrder << std::endl;
	os << "\tDisplayDeviceName: " << sxovr.hmdDesc.DisplayDeviceName << std::endl;
	os << "\tDisplayId: " << sxovr.hmdDesc.DisplayId << std::endl;

	os << "*** END-Ovr ****" << std::endl;
	return os;
}
