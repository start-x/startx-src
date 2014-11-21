#include <iostream>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <Device.h>

using namespace std;

int Device::pythonPid;
double Device::buffer[BUFFER_SIZE];

/**
 *	Initialize python program, because we need to give it our pid
 */
static void initPython()
{
	int parentPid = getpid();

	// Creates a whole new process
	Device::pythonPid = fork();
	if(Device::pythonPid == -1)
	{
		cout << "Problems while initiazing a new process!!!" << endl;
		perror("Reason");
		exit(-1);
	}

	// pid > 0 means this is still parent process
	if(Device::pythonPid > 0)
	{
		cout << "Initiating python program with pid: " << Device::pythonPid << endl;
		return; // so we just keep doing our amazing job
	}

	// If we got here, from the line bellow until exit(0) means totaly the child process
	cout << "$ " << PYTHON_PROGRAM << " " << parentPid << endl;
	char strPid[16]; // Gotta convert pid into a string
	sprintf(strPid, "%i", parentPid);
	int rc = execl(PYTHON_PROGRAM, "main.py", strPid, NULL);
	if(rc == -1)
	{
		cout << "Error while initiating python program: " << rc << endl;
		perror("Reason");
	}
	exit(0);
}

void Device::init()
{
	Device::pythonPid = 0;
	initPython();
}

void Device::destroy()
{
	if(Device::pythonPid > 0)
	{
		cout << "Killing python process: " << Device::pythonPid << endl;
		kill(Device::pythonPid, SIGTERM);
	}
}
