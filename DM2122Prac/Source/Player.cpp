#include "Player.h"

Player::Player()
{
	//Change constructor to read from text file from save file so as to make sure progress is saved

	healthUpgrade = false;
	maxSpeedUpgrade = false;
	accelerationUpgrade = false;
	maxAccelerationUpgrade = false;
	steerUpgrade = false;
}

Player::~Player()
{

}

Player* Player::instance = nullptr;

int Player::coinCount = 0;

bool Player::healthUpgrade = false;

bool Player::maxSpeedUpgrade = false;

bool Player::accelerationUpgrade = false;

bool Player::maxAccelerationUpgrade = false;

bool Player::steerUpgrade = false;


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