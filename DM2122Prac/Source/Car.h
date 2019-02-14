#ifndef CAR_H
#define CAR_H
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

	float returnMaxSpeed();

	float returnCarScale();
	void setCarScale(float);

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

	Location car;
};

#endif
