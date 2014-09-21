#include <Unity.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

using namespace std;

Unity::Unity()
{
	this->buildPid = 0;
	cout << "Initiating Unity" << endl;
}

Unity::~Unity()
{
	if(this->buildPid > 0)
	{
		cout << "Killing unity process: " << this->buildPid << endl;
		kill(this->buildPid, SIGTERM);
	}
	cout << "Termination Unity" << endl;
}

void Unity::initBuild()
{
	// Creates a whole new process
	this->buildPid = fork();
	if(this->buildPid == -1)
	{
		cout << "Problems while initiazing a new process!!!" << endl;
		perror("Reason");
		exit(-1);
	}

	// pid > 0 means this is still parent process
	if(this->buildPid > 0)
	{
		cout << "Initiating unity build with the process: " << this->buildPid << endl;
		return; // so we just keep doing our amazing job
	}

	// If we got here, from the line bellow until exit(0) means totaly the child process
	cout << "$ " << CURRENT_UNITY_BUILD << endl;
	int rc = execl(CURRENT_UNITY_BUILD, "currentBuild", NULL);
	if(rc == -1)
	{
		cout << "Error while initiating unity build" << endl;
		perror("Reason");
	}
	exit(0);
}

void Unity::init()
{
	this->initBuild();
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
