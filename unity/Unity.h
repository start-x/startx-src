#ifndef UNITY_H
#define UNITY_H

class Unity
{
public:
	Unity();
	~Unity();

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