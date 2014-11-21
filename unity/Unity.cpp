#include <Unity.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

using namespace std;

#define MOCK_SIZE 513 // number of lines with mocked values

static double mockData[MOCK_SIZE];

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

	if(!this->infoFile.is_open())
		this->infoFile.close();

	if(!this->altitudeFile.is_open())
		this->altitudeFile.close();

	if(!this->rotationFile.is_open())
		this->rotationFile.close();

	if(!this->positionFile.is_open())
		this->positionFile.close();

	cout << "Terminating Unity" << endl;
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
	// First forks this process do load the heavy unity application
	this->initBuild();

	// Now open some useful files
	this->altitudeFile.open(UNITY_ALTITUDE_FILE, std::ios::in | std::ios::binary | std::ios::ate);
	this->infoFile.open(UNITY_INFO_FILE);
	this->rotationFile.open(UNITY_ROTATION_FILE);
	this->positionFile.open(UNITY_POSITION_FILE);

	if(!this->infoFile.is_open() || !this->altitudeFile.is_open() || 
	   !this->rotationFile.is_open() || this->positionFile.is_open())
	{
		cout << "Couldn't open unity communication files";
	}
}

int Unity::getPlayerAltitude()
{
	static std::ifstream file;
	int returned = -1;

	#ifdef MOCK_DATA
		std::cout << "Mocaaaando" << std::endl;
		static int mockIndex = 0;

		// First time
		if(MOCK_SIZE == 0)
		{
			file.open("files/unity_altitude_mock.txt", std::ios::in | std::ios::binary | std::ios::ate);
			if(file.is_open())
			{
				for(int i = 0; i < MOCK_SIZE; i++)
					file >> mockData[i];
				file.close();
				std::cout << "Unity mockData loaded: " << MOCK_SIZE * sizeof(double) << " bytes long" << std::endl;
			}
			else
			{
				std::cout << "Failed to load unity mockData" << std::endl;
				mockData[0] = -1.0;
			}
		}

		if(mockIndex >= MOCK_SIZE)
			mockIndex = 0;

		returned = (int)mockData[mockIndex];
		mockIndex++;

	#else
		if(this->altitudeFile.is_open())
		{
			// Make sure to read new data
			this->altitudeFile.sync();

			this->altitudeFile >> returned;

			// Rewinds it, so next time it will read from the beginning again
			this->altitudeFile.seekg(0, ios_base::beg);
		}
		else
			std::cout << "Failed to load unity altitude" << std::endl;

	#endif

	return returned;
}

void Unity::setPlayerPosition(double speed)
{
	if(this->positionFile.is_open())
	{
		// Rewinds it, so it will write to the beginning again
		// TODO: how to come back to the beginning of the output file?
		// this->positionFile.seekg(0);

		this->positionFile << speed;

		// Make sure to write new data
		this->positionFile.flush();
	}
	else
		std::cout << "Failed to write unity position" << std::endl;
}

void Unity::setPlayerRotation(double rotation)
{
	if(this->rotationFile.is_open())
	{
		// Rewinds it, so it will write to the beginning again
		// TODO: how to come back to the beginning of the output file?
		//this->rotationFile.seekg(0);
    
		this->rotationFile << rotation;

		// Make sure to write new data
		this->rotationFile.flush();
	}
	else
		std::cout << "Failed to write unity rotation" << std::endl;
}

void Unity::setInfo(const char * info, int chars_written)
{
	if(this->infoFile.is_open())
	{
		// Rewinds it, so it will write to the beginning again
		// TODO: how to come back to the beginning of the output file?
		//this->infoFile.seekg(0);

		this->infoFile << info;

		// Make sure to write new data
		this->infoFile.flush();
	}
	else
		std::cout << "Failed to write unity information" << std::endl;
}

void Unity::render()
{
	// TODO: somehow tell unity to keep rendering the frames
}
