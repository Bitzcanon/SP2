#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

Player::Player()
{
	coinCount = 0;
	healthUpgrade = false;
	maxSpeedUpgrade = false;
	accelerationUpgrade = false;
	maxAccelerationUpgrade = false;
	steerUpgrade = false;
	//Change constructor to read from text file from save file so as to make sure progress is saved
}

Player::~Player()
{

}

bool Player::changeSomething = false;
string Player::kart = "OBJ//Kart1.obj";
string Player::wheels = "OBJ//Wheels1.obj";
string Player::color = "Image/Colors/Red.tga";
//

Player* Player::instance = nullptr;

Player* Player::getInstance()
{
	if (!instance)
	{
		instance = new Player();
	}
	return instance;
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
