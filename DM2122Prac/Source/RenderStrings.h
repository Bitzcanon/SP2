#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class RenderStrings
{
public:
	RenderStrings();
	~RenderStrings();

	string returnKartString(int);
	string returnWheelsString(int);
	string returnWheelString(int);
	const char* returnColorString(int);

private:
	vector <const char*> ColorString;
	vector <string> KartString;
	vector <string> WheelsString;
	vector <string> WheelString;

};

