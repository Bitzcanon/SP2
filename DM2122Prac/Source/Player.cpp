#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

Player::Player()
{
	saveFile.readFrom();
	coinCount = saveFile.dataStorage[0];
	healthUpgrade = saveFile.dataStorage[1];
	maxSpeedUpgrade = saveFile.dataStorage[2];
	accelerationUpgrade = saveFile.dataStorage[3];
	maxAccelerationUpgrade = saveFile.dataStorage[4];
	steerUpgrade = saveFile.dataStorage[5];

	coinsEarned = 0;

	//store into string array
	kart = saveFile.dataStorageStrings[0];
	wheels = saveFile.dataStorageStrings[1];
	color = saveFile.dataStorageStrings[2];

	//
	changeSomething = false;
}

Player::~Player()
{

}

Player* Player::instance = nullptr;

Player* Player::getInstance()
{
	if (!instance)
	{
		instance = new Player();
	}
	return instance;
}
void Player::resetSaveFile()
{
	saveFile.resetSave();
	setCoinCount(0);
	setHealthUpgradeStatus(false);
	setMaxSpeedUpgradeStatus(false);
	setAccelerationUpgradeStatus(false);
	setMaxAccelerationUpgradeStatus(false);
	setSteerUpgradeStatus(false);
}

void Player::setCoinsEarned(int input)
{
	coinsEarned = input;
}

int Player::getCoinsEarned(void)
{
	return coinsEarned;
}

//
void Player::setColor(string x)
{
	color = x;
}


string Player::returnColor()
{
	return color;
}

void Player::setChangeSomething(bool x)
{
	changeSomething = x;
}

bool Player::returnChangeSomething()
{
	return changeSomething;
}

//
void Player::setKart(string x)
{
	kart = x;
}

string Player::returnKart()
{
	return kart;
}

string Player::returnWheels()
{
	return wheels;
}

void Player::setWheels(string x)
{
	wheels = x;
}
//
void Player::loadSave()
{
	saveFile.readFrom();
}

void Player::writeSave()
{
	saveFile.writeTo(coinCount, healthUpgrade, maxSpeedUpgrade, accelerationUpgrade, maxAccelerationUpgrade, steerUpgrade , kart , wheels , color);
}

int Player::getCoinCount(void)
{
	return coinCount;
}

void Player::setCoinCount(int input)
{
	coinCount = input;
}

bool Player::getHealthUpgradeStatus(void)
{
	return healthUpgrade;
}

bool Player::getMaxSpeedUpgradeStatus(void)
{
	return maxSpeedUpgrade;
}

bool Player::getAccelerationUpgradeStatus(void)
{
	return accelerationUpgrade;
}

bool Player::getMaxAccelerationUpgradeStatus(void)
{
	return maxAccelerationUpgrade;
}

bool Player::getSteerUpgradeStatus(void)
{
	return steerUpgrade;
}

void Player::setHealthUpgradeStatus(bool input)
{
	healthUpgrade = input;
}

void Player::setMaxSpeedUpgradeStatus(bool input)
{
	maxSpeedUpgrade = input;
}

void Player::setAccelerationUpgradeStatus(bool input)
{
	accelerationUpgrade = input;
}

void Player::setMaxAccelerationUpgradeStatus(bool input)
{
	maxAccelerationUpgrade = input;
}

void Player::setSteerUpgradeStatus(bool input)
{
	steerUpgrade = input;
}
