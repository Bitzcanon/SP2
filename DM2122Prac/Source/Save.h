#ifndef SAVE_H
#define SAVE_H

#include "Definitions.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Save
{
public:
	Save();
	~Save();
	void readFrom();
	void writeTo(int coinCount, int healthUpgrade, int maxSpeedUpgrade, int accelerationUpgrade, int maxAccelerationUpgrade, int steerUpgrade, string kart, string wheels, string color);

	int getDataStorage(void);
	int dataStorage[6];
	string dataStorageStrings[3];

private:
};

#endif // ! SAVE_H