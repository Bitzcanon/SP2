#include "Barrier.h"

using namespace std;

float Barrier::BarrierDelay = 0;

Barrier::Barrier()
{
	rotateBy = 0;
	scaleBy = 0;
	xPos = 0;
	yPos = 0;
	zPos = 0;
}

Barrier::~Barrier()
{

}

int Barrier::returnBarrierRotation()
{
	return rotateBy;
}

void Barrier::setBarrierRotation(float angle)
{
	rotateBy = angle;
}

int Barrier::returnBarrierScale()
{
	return scaleBy;
}

void Barrier::setBarrierScale(int scaleFactor)
{
	scaleBy = scaleFactor;
}

int Barrier::returnBarrierQuantity()
{
	return barrierCount;
}

float Barrier::returnxPos()
{
	return xPos;
}

float Barrier::returnyPos()
{
	return yPos;
}

float Barrier::returnzPos()
{
	return zPos;
}

void Barrier::setxPos(float x)
{
	xPos = x;
}

void Barrier::setyPos(float y)
{
	yPos = y;
}

void Barrier::setzPos(float z)
{
	zPos = z;
}

void Barrier::setTimer(float time)
{
	BarrierDelay = time;
}

float Barrier::returnTimer()
{
	return BarrierDelay;
}
