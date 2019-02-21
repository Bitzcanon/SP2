#include "Save.h"

Save::Save()
{
}	

Save::~Save()
{
}

void Save::readFrom()
{
	ifstream saveFile("TextFiles//save.txt"); //Open text file to read
	string row;
	int tmp;
	string tmp2;

	if (saveFile.is_open())
	{
		for (size_t i = 0; i < 6; i++)
		{
			saveFile >> row;
			tmp = stoi(row);
			dataStorage[i] = tmp;
		}

		for (size_t i = 0; i < 3; i++)
		{
			saveFile >> tmp2;
			dataStorageStrings[i] = tmp2;
		}
		saveFile.close();
	}
	else
	{
		cout << "Impossible to open save file!" << endl;
	}
}

void Save::writeTo(int coinCount, int healthUpgrade, int maxSpeedUpgrade, int accelerationUpgrade, int maxAccelerationUpgrade, int steerUpgrade , string kart , string wheels , string color)
{
	ofstream saveFile("TextFiles//save.txt"); //Open text file to read
	string row;
	int tmp;

	if (saveFile.is_open())
	{
		saveFile << coinCount << endl;
		saveFile << healthUpgrade << endl;
		saveFile << maxSpeedUpgrade << endl;
		saveFile << accelerationUpgrade << endl;
		saveFile << maxAccelerationUpgrade << endl;
		saveFile << steerUpgrade << endl;

		saveFile << kart << endl;
		saveFile << wheels << endl;
		saveFile << color;

		saveFile.close();
	}
}

int Save::getDataStorage()
{
	return *dataStorage;
}