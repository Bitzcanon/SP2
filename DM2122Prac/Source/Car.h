#pragma once
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "MyMath.h"

#include "Location.h"
class Car
{
public:
	Car();
	~Car();

	void Update(double dt);
	float getXpos(void);
	float getYpos(void);
	float getZpos(void);

	float returnSpeed();
	void setSpeed(float);

	float returnCarScale();
	void setCarScale(float);

	float velocityX;
	float velocityZ;

	float newXpos;
	float newYpos;
	float newZpos;
	float steerAngle;

private:
	float carScale;

	float speed;
	float acceleration;
	float health;
	//float weight;

	Location position;
};

