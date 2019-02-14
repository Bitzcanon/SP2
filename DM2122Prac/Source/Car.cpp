#include "Car.h"

Car::Car()
{
	//initialize values as 0
	speed = 0.1f;
	maxSpeed = 1;

	acceleration = 0.01f;
	steerAngle = 0;
	health = 0;

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
	if (Application::IsKeyPressed(VK_UP))
	{
		speed += (float)(acceleration * dt);

		newPosition.x = car.returnXPos() + (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newPosition.y = car.returnYPos();
		newPosition.z = car.returnZPos() + (cos(Math::DegreeToRadian(steerAngle)) * speed);
		car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		speed += (float)(acceleration * dt);

		newPosition.x = car.returnXPos() - (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newPosition.y = car.returnYPos();
		newPosition.z = car.returnZPos() - (cos(Math::DegreeToRadian(steerAngle)) * speed);
		car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		steerAngle -= 2.f;
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		steerAngle += 2.f;
	}
	/*if (Application::IsKeyPressed(VK_UP) && isDrivingBackward == false)
	{
		isDrivingForward = true;
		accelerationX += 0.1f;
		velocityX += (float)(accelerationX * dt);
	}
	if (isDrivingForward)
	{
		if (!Application::IsKeyPressed(VK_UP))
		{
			accelerationX -= 0.7f;
			velocityX += (float)(accelerationX * dt);
			if (accelerationX < 0)
			{
				accelerationX = 0;
				isDrivingForward = false;
			}
		}
	}
	if (Application::IsKeyPressed(VK_DOWN) && isDrivingForward == false)
	{
		isDrivingBackward = true;
		accelerationX -= 0.1f;
		velocityX += (float)(accelerationX * dt);
	}
	if (isDrivingBackward)
	{
		if (!Application::IsKeyPressed(VK_DOWN))
		{
			accelerationX += 0.7f;
			velocityX += (float)(accelerationX * dt);
			if (accelerationX > 0)
			{
				accelerationX = 0;
				isDrivingBackward = false;
			}
		}
	}
	if (accelerationX > 10)
	{
		accelerationX = 10;
	}

	if (Application::IsKeyPressed(VK_LEFT) && isDrivingRight == false)
	{
		isDrivingLeft = true;
		accelerationZ -= 0.1f;
		velocityZ += (float)(accelerationZ * dt);
	}
	if (isDrivingLeft)
	{
		if (!Application::IsKeyPressed(VK_LEFT))
		{
			accelerationZ += 0.7f;
			velocityZ += (float)(accelerationZ * dt);
			if (accelerationZ > 0)
			{
				accelerationZ = 0;
				isDrivingLeft = false;
			}
		}
	}

	if (Application::IsKeyPressed(VK_RIGHT) && isDrivingLeft == false)
	{
		isDrivingRight = true;
		accelerationZ += 0.1f;
		velocityZ += (float)(accelerationZ * dt);
	}
	if (isDrivingRight)
	{
		if (!Application::IsKeyPressed(VK_RIGHT))
		{
			accelerationZ -= 0.7f;
			velocityZ += (float)(accelerationZ * dt);
			if (accelerationZ < 0)
			{
				accelerationZ = 0;
				isDrivingRight = false;
			}
		}
	}
	if (accelerationZ > 10)
	{
		accelerationZ = 10;
	}*/
}
	
void Car::setSpeed(float speedVal)
{
	speed = speedVal;
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