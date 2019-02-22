#ifndef CAR_H
#define CAR_H
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "MyMath.h"

#include "Location.h"
#include "Player.h"

//Logic and Car class done by Winston

class Car
{
public:
	Car();
	Car(float x, float y, float z, float maxSpeedCar, float accelerationFactorCar, float maxAccelerationCar, float steerFactorCar);
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

	void setInverseControls(bool);
	bool returnInverseControls();
	

	void setIsCollided(bool);
	bool returnIsCollided(void);

	int returnHealth(void);
	void setHealth(int);

	Vector3 newPosition;
	float steerAngle;

private:
	static float carScale;

	float maxSpeed;
	float maxAcceleration;
	float speed;
	float acceleration;
	float accelerationFactor;
	float steerFactor;

	int health;

	bool isDrivingForward;
	bool isDrivingBackward;

	bool isCollidedWithBarrier;
	bool isInversedControlled;

	bool init;

	Location car;
	Player *playerInstance;
};

#endif
