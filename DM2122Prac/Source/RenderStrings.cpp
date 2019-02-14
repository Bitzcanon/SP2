#include "RenderStrings.h"
#include <stdio.h>

RenderStrings::RenderStrings()
{
	ifstream Karts("TextFiles//KartString.txt");	// open text file
	ifstream Wheels("TextFiles//WheelsString.txt"); // open text file
	ifstream Wheel("TextFiles//WheelString.txt");	// open text file
	ifstream Color("TextFiles//ColorString.txt");	// open text file
	
	string tmp; //tmp string var

	//store kart strings
	if (Karts.is_open()) // open text file
	{
		int i = 0;
		
		while (Karts.eof() == false)
		{
			Karts >> tmp;
			i++;
			KartString.push_back(tmp);
		}
		Karts.close();
	}
	//store wheels strings
	if (Wheels.is_open()) // open text file
	{
		int i = 0;

		while (Wheels.eof() == false)
		{
			Wheels >> tmp;
			i++;
			WheelsString.push_back(tmp);
		}
		Wheels.close();
	}
	//store wheel strings
	if (Wheel.is_open()) // open text file
	{
		int i = 0;

		while (Wheel.eof() == false)
		{
			Wheel >> tmp;
			i++;
			WheelString.push_back(tmp);
		}
		Wheel.close();
	}

	const char * temp;

	if (Color.is_open()) // open text file
	{
		int i = 0;

		while (Color.eof() == false)
		{
			Color >> tmp;
			temp = tmp.c_str();
			i++;
			ColorString.push_back(temp);
		}
		Color.close();
	}
}

RenderStrings::~RenderStrings()
{

}

string RenderStrings::returnKartString(int x)
{
	return KartString[x];
}

string RenderStrings::returnWheelsString(int x)
{
	return WheelsString[x];
}

string RenderStrings::returnWheelString(int x)
{
	return WheelsString[x];
}

const char * RenderStrings::returnColorString(int x)
{
	return ColorString[x];
}