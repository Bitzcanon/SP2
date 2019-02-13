#include "Location.h"

Location::Location()
{

}

Location::~Location()
{

}

float Location::returnXPos() const
{
	return xPos;
}

float Location::returnYPos() const
{
	return yPos;
}

float Location::returnZPos() const
{
	return zPos;
}

void Location::setLocation(float x , float y , float z)
{
	xPos = x;
	yPos = y;
	zPos = z;
}
