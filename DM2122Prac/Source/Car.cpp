#include "Car.h"


Car::Car()
{
	//initialize values as 0
	speed = 0.1f;
	acceleration = 0.01f;
	steerAngle = 0;
	health = 0;

	newXpos = 0;
	newYpos = 0;
	newZpos = 0;

	//Set default position of Car to 0,0,0
	position.setLocation(0, 0, 0);
}

Car::~Car()
{
}

float Car::getXpos(void)
{
	return position.returnXPos();
}

float Car::getYpos(void)
{
	return position.returnYPos();
}

float Car::getZpos(void)
{
	return position.returnZPos();
}

void Car::Update(double dt)
{

	if (Application::IsKeyPressed(VK_UP))
	{
		speed += (float)(acceleration * dt);

		newXpos = position.returnXPos() + (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newYpos = position.returnYPos();
		newZpos = position.returnZPos() + (cos(Math::DegreeToRadian(steerAngle)) * speed);
		position.setLocation(newXpos, position.returnYPos(), newZpos);
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		speed += (float)(acceleration * dt);

		newXpos = position.returnXPos() - (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newYpos = position.returnYPos();
		newZpos = position.returnZPos() - (cos(Math::DegreeToRadian(steerAngle)) * speed);
		position.setLocation(newXpos, position.returnYPos(), newZpos);
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