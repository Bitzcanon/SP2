#include "Buff.h"

Buff::Buff()
{
	rotateBy = 0;
	xPos = 0;
	yPos = 0;
	zPos = 0;
}

Buff::Buff(float x , float y , float z) // not used
{
	xPos = x, yPos = y, zPos = z;
}

Buff::~Buff()
{

}

//init static buffcount = 0;
float::Buff::timer = 0;
int::Buff::BuffCount = 0;
bool::Buff::activateYet = false;

void Buff::setxPos(float x)
{
	xPos = x;
}

void Buff::setyPos(float y)
{
	yPos = y;
}

void Buff::setzPos(float z)
{
	zPos = z;
}

void Buff::setRotateBy(float angle)
{
	rotateBy = angle;
}

void Buff::setTimer(float time)
{
	timer = time;
}

float Buff::returnTimer()
{
	return timer;
}

int Buff::returnBuffRotation()
{
	return rotateBy;
}

int Buff::returnBuffQuantity()
{
	return BuffCount;
}

float Buff::returnxPos()
{
	return xPos;
}

float Buff::returnyPos()
{
	return yPos;
}

float Buff::returnzPos()
{
	return zPos;
}