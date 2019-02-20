#ifndef PLAYER_H
#define PLAYER_H
#include <string>

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

	static bool changeSomething; // boolean for changing of a car part.
	static std::string kart; // store kart address
	static std::string wheels; // store wheel address
	static std::string color; // store color address
private:
	Player();
	~Player();

	static Player* instance;
	int coinCount;

	bool healthUpgrade;
	bool maxSpeedUpgrade;
	bool accelerationUpgrade;
	bool maxAccelerationUpgrade;
	bool steerUpgrade;

};
#endif // !PLAYER_H
