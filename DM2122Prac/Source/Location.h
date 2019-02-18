#ifndef LOCATION_H
#define LOCATION_H

#include "Vector3.h"

class Location
{
public:
	Location();
	~Location();

	float returnXPos() const;
	float returnYPos() const;
	float returnZPos() const;

	void setLocation(float x, float y, float z);

private:
	Vector3 position;

};

#endif // ! LOCATION_H