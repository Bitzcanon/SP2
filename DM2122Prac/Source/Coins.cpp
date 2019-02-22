#include "Coins.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Coins::Coins()
{
	taken = false; appeared = false;
	x = rand() % 990 - 495;
	z = rand() % 990 - 495;
}

Coins::~Coins()
{
}

void Coins::CoinCollision(float playerx, float playerz)
{
	if (playerx > x - 20.f && playerx < x + 20.f)
	{
		if (playerz > z - 20.f && playerz < z + 20.f)
		{
			if (appeared)
			{
				taken = true;
			}
		}
	}
}

void Coins::appears()
{
	appeared = true;
}

bool Coins::CheckTaken()
{
	return taken;
}

bool Coins::hasAppeared()
{
	return appeared;
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