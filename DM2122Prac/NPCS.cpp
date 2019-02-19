#include "NPCS.h"



NPCS::NPCS()
{
}


NPCS::~NPCS()
{
}

void NPCS::MoveNPC(double dt, int index)
{
	switch (index)
	{
	case 0:
		if (!close)
		{
			switch ((int)direction)
			{
			case 0:
				if (x < 20.f)
				{
					x += (float)dt * 5.f;
				}
				else
				{
					direction = 1.f;
				}
				break;
			case 1:
				if (z > -20.f)
				{
					z -= (float)dt * 5.f;
				}
				else
				{
					direction = 2.f;
				}
				break;
			case 2:
				if (x > -20.f)
				{
					x -= (float)dt * 5.f;
				}
				else
				{
					direction = 3.f;
				}
				break;
			case 3:
				if (z < 20.f)
				{
					z += (float)dt * 5.f;
				}
				else
				{
					direction = 0.f;
				}
				break;
			}
		}
		break;
	case 1:
		if (!close)
		{
			switch ((int)direction)
			{
			case 0:
				if (x < 10.f)
				{
					x += (float)dt * 5.f;
				}
				else
				{
					direction = 1.f;
				}
				break;
			case 1:
				if (x > -10.)
				{
					x -= (float)dt * 5.f;
				}
				else
				{
					direction = 0.f;
				}
				break;
			}
		}
		break;
	}
}

bool NPCS::CloseToNPC(float playerx, float playerz)
{
	if (playerx >= x * 5.f - 40.f && playerx <= x * 5.f + 40.f)
	{
		if (playerz >= z * 5.f - 40.f && playerz <= z * 5.f + 40.f)
		{
			close = true;
			return true;
		}
	}

	close = false;
	return false;
}

void NPCS::setCoordsNPC(float npcx, float npcz)
{
	x = npcx; z = npcz;
}

float NPCS::getx()
{
	return x;
}

float NPCS::getz()
{
	return z;
}