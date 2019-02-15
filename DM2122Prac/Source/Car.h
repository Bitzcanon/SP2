#ifndef CAR_H
#define CAR_H
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "MyMath.h"

#include "Location.h"

//Logic and Car class done by Winston

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
	void setAcceleration(float);

	float returnMaxSpeed();

	float returnCarScale();
	void setCarScale(float);

	void decelerateCar(double dt);

	void setIsCollided(bool);
	bool returnIsCollided(void);

	Vector3 newPosition;
	float steerAngle;

private:
	float carScale;

	float maxSpeed;
	float speed;
	float acceleration;
	float health;
	//float weight;

	bool isDrivingForward;
	bool isDrivingBackward;

	bool isCollidedWithBarrier;

	Location car;
};

#endif
