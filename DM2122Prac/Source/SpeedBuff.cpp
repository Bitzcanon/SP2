#include "SpeedBuff.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

SpeedBuff::SpeedBuff()
{
	effect = 10;
	timer = 0;
	condition = false;

	//Storing coordinates in text file over into vector found in 
	ifstream myfile("TextFiles//SpeedBuffCoordinates.txt"); // open text file

	vector <float> TextStorage; // tmp vector to store stuff from text file 

	if (myfile.is_open()) // open text file
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

	int counter = 1;
	for (int i = 0; i < TextStorage.size(); i++) // loop through the 9 different TextStorages.
	{
		if (counter == 4)
		{
			rotateBy.push_back(TextStorage[i]);
			counter = 1;
		}
		else if (counter == 3) // if k = third number in the line
		{
			zPos.push_back(TextStorage[i]);
			counter += 1;
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

	speedBuffQuantity = (TextStorage.size() / 4);

/* For testing purposes , prints out the values of x y and z
	for (int i = 0; i < TextStorage.size() / 3; i++)
	{
		cout << "X value : " << xPos[i] << " Y value : " << yPos[i] << " Z Value : " << zPos[i] << endl;
	}*/
}

SpeedBuff::~SpeedBuff()
{
	
}
void SpeedBuff::setCondition(bool x)
{
	condition = x;
}

bool SpeedBuff::returnCondition()
{
	return condition;
}

int SpeedBuff::returnSpeedBuffRotation(int angleNumber)
{
	return rotateBy[angleNumber];
}

int SpeedBuff::returnSpeedBuffQuantity()
{
	return speedBuffQuantity;
}

float SpeedBuff::returnxPos(int locationNumber)
{
	return xPos[locationNumber];
}

float SpeedBuff::returnyPos(int locationNumber)
{
	return yPos[locationNumber];
}

float SpeedBuff::returnzPos(int locationNumber)
{
	return zPos[locationNumber];
}
