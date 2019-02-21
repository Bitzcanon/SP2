#include "SP2_ChaseEnemyScene.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"
#include "Computer.h"

#include <random>
#include <time.h>

Computer::Computer()
{
	com1.setLocation(0, 0, 0);
	newPosition = (0.f, 0.f, 0.f);

	//initialize values as 0
	maxSpeed = 0.4f;
	speed = 0;

	accelerationFactor = 0.005f;
	acceleration = 0;
	maxAcceleration = 0.5f;

	steerFactor = 1.8f;
	steerAngle = 0;


}

Computer::~Computer()
{
}


void Computer::update(double dt)
{
	if (Application::IsKeyPressed(VK_UP))
	{
		for (int section = 0; section < 20; section++)
		{
			switch (section)
			{
			case(0):
				//steerAngle += steerFactor;
				//steerFactor = 2.2f;
				accelerationFactor = 0.01f;
				acceleration += accelerationFactor;
				speed += (float)(acceleration * dt);
				newPosition.x += (sin(Math::DegreeToRadian(steerAngle)) * speed);
				newPosition.y = com1.returnYPos();
				newPosition.z += (cos(Math::DegreeToRadian(steerAngle)) * speed);
				com1.setLocation(newPosition.x, com1.returnYPos(), newPosition.z);
				if (newPosition.x == 20, newPosition.z == 20)
				{
					break;
				}
			case(1):
				break;
			case(2):
				break;
			case(3):
				break;
			case(4):
				break;
			case(5):
				break;
			case(6):
				break;
			case(7):
				break;
			case(8):
				break;
			case(9):
				break;
			case(10):
				break;
			case(11):
				break;
			case(12):
				break;
			case(13):
				break;
			default:
				break;
			}
		}
	}
}