#include "Checkpoint.h"

using namespace std;

Checkpoint::Checkpoint()
{
	rotateBy = 0;
	scaleBy = 0;
	xPos = 0;
	yPos = 0;
	zPos = 0;
}

Checkpoint::~Checkpoint()
{

}

int Checkpoint::returnCheckpointRotation()
{
	return rotateBy;
}

void Checkpoint::setCheckpointRotation(float angle)
{
	rotateBy = angle;
}

int Checkpoint::returnCheckpointScale()
{
	return scaleBy;
}

void Checkpoint::setCheckpointScale(int scaleFactor)
{
	scaleBy = scaleFactor;
}

int Checkpoint::returnCheckpointQuantity()
{
	return barrierCount;
}

float Checkpoint::returnxPos()
{
	return xPos;
}

float Checkpoint::returnyPos()
{
	return yPos;
}

float Checkpoint::returnzPos()
{
	return zPos;
}

void Checkpoint::setxPos(float x)
{
	xPos = x;
}

void Checkpoint::setyPos(float y)
{
	yPos = y;
}

void Checkpoint::setzPos(float z)
{
	zPos = z;
}
