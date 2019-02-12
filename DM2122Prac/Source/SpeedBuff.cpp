#include "SpeedBuff.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

SpeedBuff::SpeedBuff()
{
	effect = 10;
	timer = 4;

	//Storing coordinates in text file over into vector found in 
	string line;
	ifstream myfile("TextFiles//SpeedBuffCoordinates.txt");

	vector <float> TextStorage;

	if (myfile.is_open())
	{
		int i = 0;
		float tmp;

		while (myfile.eof() == false)
		{
			myfile >> tmp;
			i++;
			TextStorage.push_back(tmp);
		}
		myfile.close();
	}
	//think of a for loop algorithm that loops through 3 coordinates at a time.

	int counter = 1;
	for (int i = 0; i < TextStorage.size(); i++) // loop through the 9 different TextStorages.
	{
		if (counter == 3) // if k = third number in the line
		{
			zPos.push_back(TextStorage[i]);
			counter = 1;
		}
		else if (counter == 2) // if k = second number in line
		{
			yPos.push_back(TextStorage[i]);
			counter += 1;
		}
		else if (counter == 1) // if k = first number in line
		{
			xPos.push_back(TextStorage[i]);
			counter += 1;
		}
	}

	for (int i = 0; i < TextStorage.size() / 3; i++)
	{
		cout << "X value : " << xPos[i] << " Y value : " << yPos[i] << " Z Value : " << zPos[i] << endl;
	}
}

SpeedBuff::~SpeedBuff()
{
	
}

float SpeedBuff::returnxPos(int location)
{
	return xPos[location];
}

float SpeedBuff::returnyPos(int location)
{
	return yPos[location];
}

float SpeedBuff::returnzPos(int location)
{
	return zPos[location];
}
