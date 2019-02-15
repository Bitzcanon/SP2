#include "Barrier.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Barrier::Barrier()
{
	//Storing coordinates in text file over into vector found in 
	ifstream myfile("TextFiles//BarrierCoordinates.txt"); //Open text file

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
		if (counter == 5)
		{
			scaleBy.push_back(TextStorage[i]);
			counter = 1;
		}
		else if (counter == 4) //if k = fourth number in the line
		{
			rotateBy.push_back(TextStorage[i]);
			counter += 1;
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

	barrierQuantity = (TextStorage.size() / 4);
	timer = 0;

	/* For testing purposes , prints out the values of x y and z
		for (int i = 0; i < TextStorage.size() / 3; i++)
		{
			cout << "X value : " << xPos[i] << " Y value : " << yPos[i] << " Z Value : " << zPos[i] << endl;
		}*/
}

Barrier::~Barrier()
{

}

int Barrier::returnBarrierRotation(int angleNumber)
{
	return rotateBy[angleNumber];
}

int Barrier::returnBarrierScale(int scaleNumber)
{
	return scaleBy[scaleNumber];
}

int Barrier::returnBarrierQuantity()
{
	return barrierQuantity;
}

float Barrier::returnxPos(int locationNumber)
{
	return xPos[locationNumber];
}

float Barrier::returnyPos(int locationNumber)
{
	return yPos[locationNumber];
}

float Barrier::returnzPos(int locationNumber)
{
	return zPos[locationNumber];
}

void Barrier::setTimer(float time)
{
	timer = time;
}

float Barrier::returnTimer()
{
	return timer;
}
