#include "Coins.h"



Coins::Coins()
{
	x = 0.f; z = 0.f; taken = false;
}


Coins::~Coins()
{
}

void Coins::CoinCollision(float playerx, float playerz)
{
	if (playerx > x - 10.f && playerx < x + 10.f)
	{
		if (playerz > z - 10.f && playerz < z + 10.f)
		{
			taken = true;
		}
	}
}

bool Coins::CheckTaken()
{
	return taken;
}

void Coins::SetCoinCoords(float coinx, float coinz)
{
	x = coinx; z = coinz;
}

float Coins::getX()
{
	return x;
}

float Coins::getZ()
{
	return z;
}