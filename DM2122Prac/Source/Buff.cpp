#include "Buff.h"

Buff::Buff()
{
	rotateBy = 0;
	xPos = 0;
	yPos = 0;
	zPos = 0;
}

Buff::~Buff()
{

}

//init static buffcount = 0;


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

float Buff::returnBuffRotation()
{
	return rotateBy;
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