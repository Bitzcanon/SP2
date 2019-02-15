#include "Car.h"

Car::Car()
{
	//initialize values as 0
	speed = 0;
	maxSpeed = 0.2f;

	acceleration = 0;
	accelerationFactor = 0.005f;

	steerFactor = 3.f;

	acceleration = 0;
	steerAngle = 0;
	health = 0;
	isDrivingForward = false;
	isDrivingBackward = false;
	isCollidedWithBarrier = false;

	newPosition = (0, 0, 0);

	carScale = 10;

	//Set default position of Car to 0,0,0
	car.setLocation(0, 0, 0);
}


Car::~Car()
{
}

float Car::getXpos(void)
{
	return car.returnXPos();
}

float Car::getYpos(void)
{
	return car.returnYPos();
}

float Car::getZpos(void)
{
	return car.returnZPos();
}

void Car::Update(double dt)
{
	if (Application::IsKeyPressed(VK_UP) && isDrivingBackward == false)
	{
		isDrivingForward = true;
		isDrivingBackward = false;
		acceleration += accelerationFactor;
		speed += (float)(acceleration * dt);

		newPosition.x += (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newPosition.y = car.returnYPos();
		newPosition.z += (cos(Math::DegreeToRadian(steerAngle)) * speed);
		car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

		if (acceleration > 0.5f)
		{
			acceleration = 0.5f;
		}
		if (speed > maxSpeed)
		{
			speed = maxSpeed;
		}
	}
	if (isDrivingForward)
	{
		if (!Application::IsKeyPressed(VK_UP))
		{
			decelerateCar(dt);
		}
	}
	if (Application::IsKeyPressed(VK_DOWN) && isDrivingForward == false)
	{
		isDrivingForward = false;
		isDrivingBackward = true;
		acceleration -= accelerationFactor;
		speed += (float)(acceleration * dt);

		newPosition.x += (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newPosition.y = newPosition.y;
		newPosition.z += (cos(Math::DegreeToRadian(steerAngle)) * speed);
		car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

		if (acceleration < -0.5f)
		{
			acceleration = -0.5f;
		}
		if (speed < -maxSpeed) //negative because it is moving in the opposite direction
		{
			speed = -maxSpeed;
		}
	}
	if (isDrivingBackward)
	{
		if (!Application::IsKeyPressed(VK_DOWN))
		{
			decelerateCar(dt);
		}
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		if (isDrivingForward)
		{
			steerAngle -= steerFactor;
		}
		if (isDrivingBackward)
		{
			steerAngle += steerFactor;
		}
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		if (isDrivingForward)
		{
			steerAngle += steerFactor;
		}
		if (isDrivingBackward)
		{
			steerAngle -= steerFactor;
		}
	}
}

void Car::decelerateCar(double dt)
{
	if (isDrivingForward)
	{
		acceleration -= 0.1f;
		speed += (float)(acceleration * dt);
		newPosition.x = car.returnXPos() + (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newPosition.y = car.returnYPos();
		newPosition.z = car.returnZPos() + (cos(Math::DegreeToRadian(steerAngle)) * speed);
		car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

		if (acceleration < 0.f)
		{
			acceleration = 0.f;
			speed -= 0.025f;
		}
		if (speed < 0.f)
		{
			speed = 0.f;
			isDrivingForward = false;
		}
	}
	if (isDrivingBackward)
	{
		acceleration += 0.1f;
		speed += (float)(acceleration * dt);
		newPosition.x = car.returnXPos() + (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newPosition.y = car.returnYPos();
		newPosition.z = car.returnZPos() + (cos(Math::DegreeToRadian(steerAngle)) * speed);
		car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

		if (acceleration > 0.f)
		{
			acceleration = 0.f;
			speed += 0.025f;
		}
		if (speed > 0.f)
		{
			speed = 0.f;
			isDrivingBackward = false;
		}
	}
}
	
void Car::setSpeed(float speedVal)
{
	speed = speedVal;
}

void Car::setAcceleration(float accelerationVal)
{
	acceleration = accelerationVal;
}

float Car::returnSpeed()
{
	return speed;
}

float Car::returnMaxSpeed()
{
	return maxSpeed;
}

float Car::returnCarScale()
{
	return carScale;
}

void Car::setCarScale(float scale)
{
	carScale = scale;
}

void Car::setIsCollided(bool input)
{
	isCollidedWithBarrier = input;
}

bool Car::returnIsCollided(void)
{
	return isCollidedWithBarrier;
}