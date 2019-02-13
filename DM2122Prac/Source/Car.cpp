#include "Car.h"

Car::Car()
{
	//initialize values as 0
	speed = 0.f;
	acceleration = 0.f;
	steerAngle = 0;
	health = 0;
	isDrivingForward = false;
	isDrivingBackward = false;

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
		acceleration += 0.005;
		speed += (float)(acceleration * dt);

		newPosition.x += (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newPosition.y = car.returnYPos();
		newPosition.z += (cos(Math::DegreeToRadian(steerAngle)) * speed);
		car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

		if (acceleration > 0.5f)
		{
			acceleration = 0.5f;
		}
		if (speed > 0.3f)
		{
			speed = 0.3f;
		}
	}
	if (isDrivingForward)
	{
		if (!Application::IsKeyPressed(VK_UP))
		{
			acceleration -= 0.1f;
			speed += (float)(acceleration * dt);
			newPosition.x = car.returnXPos() + (sin(Math::DegreeToRadian(steerAngle)) * speed);
			newPosition.y = car.returnYPos();
			newPosition.z = car.returnZPos() + (cos(Math::DegreeToRadian(steerAngle)) * speed);
			car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

			if(acceleration < 0.f)
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
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		isDrivingForward = false;
		isDrivingBackward = true;
		acceleration -= 0.005f;
		speed += (float)(acceleration * dt);

		newPosition.x += (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newPosition.y = newPosition.y;
		newPosition.z += (cos(Math::DegreeToRadian(steerAngle)) * speed);
		car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

		if (acceleration < -0.5f)
		{
			acceleration = -0.5f;
		}
		if (speed < -0.3f)
		{
			speed = -0.3f;
		}
	}
	if (isDrivingBackward)
	{
		if (!Application::IsKeyPressed(VK_DOWN) && isDrivingForward == false)
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
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		if (isDrivingForward)
		{
			steerAngle -= 3.f;
		}
		if (isDrivingBackward)
		{
			steerAngle += 3.f;
		}
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		if (isDrivingForward)
		{
			steerAngle += 3.f;
		}
		if (isDrivingBackward)
		{
			steerAngle -= 3.f;
		}
	}
}
	
void Car::setSpeed(float speedVal)
{
	speed = speedVal;
}

float Car::returnSpeed()
{
	return speed;
}

float Car::returnCarScale()
{
	return carScale;
}

void Car::setCarScale(float scale)
{
	carScale = scale;
}