#pragma once
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"

class Car
{
public:
	Car();
	~Car();

private:
	float speed;
	float acceleration;
	float steerAngle;
	float health;
	//float weight;

};

