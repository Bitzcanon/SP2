#pragma once
class Coins
{
public:
	Coins();
	~Coins();
	void CoinCollision(float playerx, float playerz);
	void appears();
	bool CheckTaken();
	bool hasAppeared();
	void SetCoinCoords(float coinx, float coinz);
	float getX();
	float getZ();
private:
	float x, z;
	bool taken;
	bool appeared;
};

