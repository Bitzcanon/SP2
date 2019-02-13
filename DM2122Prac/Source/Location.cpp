#include "Location.h"

Location::Location()
{

}

Location::~Location()
{

}

float Location::returnXPos() const
{
	return position.x;
}

float Location::returnYPos() const
{
	return position.y;
}

float Location::returnZPos() const
{
	return position.z;
}

void Location::setLocation(float x , float y , float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}