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
	string returnColorString(int);

private:
	vector <string> ColorString;

	vector <string> KartString;
	vector <string> WheelsString;

};

