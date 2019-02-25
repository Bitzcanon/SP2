#include "NPCS.h"



NPCS::NPCS()
{
	x = 0.f; z = 0.f; close = false; interacting = false; direction = 0;
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
	if (playerx >= x * 5.f - 60.f && playerx <= x * 5.f + 60.f)
	{
		if (playerz >= z * 5.f - 60.f && playerz <= z * 5.f + 60.f)
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

void NPCS::setDirection(float i)
{
	direction = i;
}

float NPCS::getx()
{
	return x;
}

float NPCS::getz()
{
	return z;
}

float NPCS::getDirection()
{
	return direction;
}

bool NPCS::IsInteracting()
{
	return interacting;
}

void NPCS::Interacts(int i)
{
	switch (i)
	{
	case 0:
		interacting = false;
		break;
	case 1:
		interacting = true;
		break;
	}
}