#ifndef COMPUTER_H
#define COMPUTER_H
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "MyMath.h"

#include "Location.h"
#include "Player.h"

class Computer
{
public:
	Computer();
	~Computer();

	Location com1;

	Vector3 newPosition;
	float steerAngle;
	void update(double dt);

private:
	static float carScale;

	float maxSpeed;
	float maxAcceleration;
	float speed;
	float acceleration;
	float accelerationFactor;
	float steerFactor;
};

#endif COMPUTER_H
