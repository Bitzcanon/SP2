#include "Location.h"

Location::Location()
{

}

Location::~Location()
{

}

float Location::returnXPos()
{
	return xPos;
}

float Location::returnYPos()
{
	return yPos;
}

float Location::returnZPos()
{
	return zPos;
}

void Location::setLocation(float x , float y , float z)
{
	xPos = x;
	yPos = y;
	zPos = z;
}
