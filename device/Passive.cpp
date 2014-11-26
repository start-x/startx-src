#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <Passive.h>

static unsigned char * mockData = 0;
static int MOCK_SIZE = 0;

int Passive::flush()
{
	static std::ifstream file;

	#ifdef MOCK_DATA
		std::cout << "Mocaaaando" << std::endl;
		static int mockIndex = 0;

		// First time
		if(MOCK_SIZE == 0)
		{
			file.open("files/passive_mock.txt", std::ios::in | std::ios::binary | std::ios::ate);
			if(file.is_open())
			{
				std::streampos size = file.tellg();
				MOCK_SIZE = size;
				// TODO: free this memory later
				mockData = new unsigned char[MOCK_SIZE];
				file.seekg(0, std::ios::beg);
				file.read(mockData, MOCK_SIZE);
				file.close();
				std::cout << "Passive mockData loaded: " << size << " bytes long" << std::endl;
			}
			else
			{
				std::cout << "Failed to load passive mockData" << std::endl;
				mockData = unsigned new char[1];
				*mockData = '0';
			}
			file.close();
		}

		// Just get next mockData line and we're good
		if(!mockData)
		{
			std::cout << "No mockData" << std::endl;
			return -1;
		}

		if(mockIndex >= MOCK_SIZE)
			mockIndex = 0;

		for(int i = 0; i < BUFFER_SIZE && mockIndex < MOCK_SIZE; i++, mockIndex++)
			buffer[i] = mockData[mockIndex];
		mockIndex++; // Skip line break

	#else
		std::cout << "killando o processo " << Device::pythonPid << std::endl;
		kill(Device::pythonPid, 30);
		file.open(PASSIVE_FILENAME);
		if(file.is_open())
		{
			int value;
			std::stringstream ss;
			ss << file.rdbuf();
			ss >> buffer[DIRECTION];
			//ss >> buffer[SPEED];
			buffer[SPEED] = 30.0;
			file.close();
		}
		else
			std::cout << "****** Failed to load passive file ******" << std::endl;
		file.close();
	#endif
	return 0;
}
