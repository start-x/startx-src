#ifndef UNITY_H
#define UNITY_H

#include <fstream>

#define CURRENT_UNITY_BUILD "unity/currentBuild"

#define UNITY_INFO_FILE "files/unity_info.txt"
#define UNITY_ALTITUDE_FILE "files/unity_altitude.txt"
#define UNITY_ROTATION_FILE "files/unity_rotation.txt"
#define UNITY_POSITION_FILE "files/unity_speed.txt"

#define INFO_SIZE 256

class Unity
{

public:
	/**
	 *	In order to have the virtual build working, we need to create a 
	 *	whole new process for it, and this is its pid
	 */
	int buildPid;

	/**
	 *	Files in which we're gonna use to exchange some information with Unity app
	 */
	std::ifstream altitudeFile;
	std::ofstream infoFile;
	std::ofstream rotationFile;
	std::ofstream positionFile;

	Unity();
	~Unity();

	/**
	 *	Do necessary stuff to initialize Unity model
	 */
	void init();

	/**
	 *	Initialize build
	 */
	void initBuild();

	// ********************* Methods declared in UML *************************

	/**
	 *	Get y value from Player in the virtual world
	 */
	int getPlayerAltitude();

	/**
	 *	Set ONLY x and z positions, because y value is NOT GONNA BE SET BY US
	 */
	void setPlayerPosition(double speed);

	/**
	 *	Set x, y and z values for player rotation
	 */
	void setPlayerRotation(double rotation);

	/**
	 *	Set a text information of the screen
	 */
	void setInfo(const char * info, int chars_written);

	/**
	 *	Tells Unity that everything is ready for render next frames
	 */
	void render();
};

#endif
