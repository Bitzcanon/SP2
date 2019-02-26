#include "Coins.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Coins::Coins()
{
	taken = false; appeared = false;
	//x = (float)(rand() % 990 - 495);
	//z = (float)(rand() % 990 - 495);

	x = (float)((rand() % 7) * 50 - 150);
	z = (float)((rand() % 15) * 25 - 175);
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
			if (appeared)
			{
				music.stopMusic();
				music.playInstantSound(1);
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