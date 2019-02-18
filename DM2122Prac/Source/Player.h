#ifndef PLAYER_H
#define PLAYER_H

//Done by Winston, used Singleton Pattern to create only 1 instance of Player throughout the entire program

class Player
{
public:
	static Player* getInstance();

	int getCoinCount(void);
	void setCoinCount(int);

	bool getHealthUpgradeStatus(void);
	bool getMaxSpeedUpgradeStatus(void);
	bool getAccelerationUpgradeStatus(void);
	bool getMaxAccelerationUpgradeStatus(void);
	bool getSteerUpgradeStatus(void);

	void setHealthUpgradeStatus(bool);
	void setMaxSpeedUpgradeStatus(bool);
	void setAccelerationUpgradeStatus(bool);
	void setMaxAccelerationUpgradeStatus(bool);
	void setSteerUpgradeStatus(bool);
private:
	Player();
	~Player();
	static Player* instance;

	static int coinCount;

	static bool healthUpgrade;
	static bool maxSpeedUpgrade;
	static bool accelerationUpgrade;
	static bool maxAccelerationUpgrade;
	static bool steerUpgrade;

};
#endif // !PLAYER_H
