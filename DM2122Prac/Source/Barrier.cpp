#include "Barrier.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

float Barrier::BarrierDelay = 0;

Barrier::Barrier()
{
	rotateBy = 0;
	scaleBy = 0;
	xPos = 0;
	yPos = 0;
	zPos = 0;
	////Storing coordinates in text file over into vector found in 
	//ifstream myfile("TextFiles//BarrierCoordinates.txt"); //Open text file

	//vector <float> TextStorage; // tmp vector to store stuff from text file 

	//if (myfile.is_open()) // open text file
	//{
	//	int i = 0;
	//	float tmp;

	//	while (myfile.eof() == false)
	//	{
	//		myfile >> tmp;
	//		i++;
	//		TextStorage.push_back(tmp);
	//	}
	//	myfile.close();
	//}

	//int counter = 1;
	//for (size_t i = 0; i < TextStorage.size(); i++) // loop through the 9 different TextStorages.
	//{
	//	if (counter == 5)
	//	{
	//		scaleBy.push_back(TextStorage[i]);
	//		counter = 1;
	//	}
	//	else if (counter == 4) //if k = fourth number in the line
	//	{
	//		rotateBy.push_back(TextStorage[i]);
	//		counter += 1;
	//	}
	//	else if (counter == 3) // if k = third number in the line
	//	{
	//		zPos.push_back(TextStorage[i]);
	//		counter += 1;
	//	}
	//	else if (counter == 2) // if k = second number in line
	//	{
	//		yPos.push_back(TextStorage[i]);
	//		counter += 1;
	//	}
	//	else if (counter == 1) // if k = first number in line
	//	{
	//		xPos.push_back(TextStorage[i]);
	//		counter += 1;
	//	}
	//}

	//barrierQuantity = (TextStorage.size() / 5);
	//timer = 0;

	///* For testing purposes , prints out the values of x y and z
	//	for (int i = 0; i < TextStorage.size() / 3; i++)
	//	{
	//		cout << "X value : " << xPos[i] << " Y value : " << yPos[i] << " Z Value : " << zPos[i] << endl;
	//	}*/
}

Barrier::~Barrier()
{

}

int Barrier::returnBarrierRotation()
{
	return rotateBy;
}

void Barrier::setBarrierRotation(float angle)
{
	rotateBy = angle;
}

int Barrier::returnBarrierScale()
{
	return scaleBy;
}

void Barrier::setBarrierScale(int scaleFactor)
{
	scaleBy = scaleFactor;
}

int Barrier::returnBarrierQuantity()
{
	return barrierCount;
}

float Barrier::returnxPos()
{
	return xPos;
}

float Barrier::returnyPos()
{
	return yPos;
}

float Barrier::returnzPos()
{
	return zPos;
}

void Barrier::setxPos(float x)
{
	xPos = x;
}

void Barrier::setyPos(float y)
{
	yPos = y;
}

void Barrier::setzPos(float z)
{
	zPos = z;
}

void Barrier::setTimer(float time)
{
	BarrierDelay = time;
}

float Barrier::returnTimer()
{
	return BarrierDelay;
}
