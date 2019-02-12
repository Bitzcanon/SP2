#include "Car.h"


Car::Car()
{
	//initialize values as 0
	speed = 0;
	acceleration = 0;
	steerAngle = 0;
	health = 0;
}

Car::~Car()
{
}

//float Car::UpdateSpeedBackward(double dt)
//{
//	if (Application::IsKeyPressed(VK_UP))
//	{
//		speed *= (float)(acceleration * dt);
//	}
//	if (Application::IsKeyPressed(VK_DOWN))
//	{
//		speed *= (float)(acceleration * dt);
//	}
//	return speed;
//}