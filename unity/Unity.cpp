#include <Unity.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

Unity::Unity()
{
	cout << "Initiating Unity" << endl;
}

Unity::~Unity()
{
	cout << "Termination Unity" << endl;
}

/**
 *	Runs current unity build in a separated thread
 */
static void * runCurrentUnityBuild(void * params)
{

	execl(CURRENT_UNITY_BUILD, "currentBuild",NULL);
}

void Unity::init()
{
	// Create a thread 
	pthread_t unity_th;

	// TODO: for now, we're leaving the thread run on its own
	pthread_create(& unity_th, NULL, runCurrentUnityBuild, NULL);
}

int Unity::getPlayerAltitude()
{
	return 0;
}

void Unity::setPlayerPosition(float x, float z)
{

}

void Unity::setPlayerRotation(float x, float y, float z)
{

}

void Unity::setInfo(const char * info)
{

}

void Unity::render()
{

}
