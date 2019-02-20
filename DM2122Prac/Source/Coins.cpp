#include "Coins.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Coins::Coins()
{
	taken = false;
	x = rand() % 990 - 495;
	z = rand() % 990 - 495;
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