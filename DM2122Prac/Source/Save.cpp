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

	if (saveFile.is_open())
	{
		for (size_t i = 0; i < 6; i++)
		{
			saveFile >> row;
			tmp = stoi(row);
			dataStorage[i] = tmp;
		}
		saveFile.close();
	}
	else
	{
		cout << "Impossible to open save file!" << endl;
	}
}

void Save::writeTo(int coinCount, int healthUpgrade, int maxSpeedUpgrade, int accelerationUpgrade, int maxAccelerationUpgrade, int steerUpgrade)
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
		saveFile << steerUpgrade;
		saveFile.close();
	}
}

int Save::getDataStorage()
{
	return *dataStorage;
}