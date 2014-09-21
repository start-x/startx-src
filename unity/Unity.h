#ifndef UNITY_H
#define UNITY_H

#define CURRENT_UNITY_BUILD "unity/currentBuild"

class Unity
{

public:
	/**
	 *	In order to have the virtual build working, we need to create a 
	 *	whole new process for it, and this is its pid
	 */
	int buildPid;

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
	void setPlayerPosition(float x, float z);

	/**
	 *	Set x, y and z values for player rotation
	 */
	void setPlayerRotation(float x, float y, float z);

	/**
	 *	Set a text information of the screen
	 */
	void setInfo(const char * info);

	/**
	 *	Tells Unity that everything is ready for render next frames
	 */
	void render();
};

#endif