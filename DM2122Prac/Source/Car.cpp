#include "Car.h"

Car::Car()
{
	//Set default position of Car to 0,0,0
	car.setLocation(0, 0, 0);
	newPosition = (0.f, 0.f, 0.f);

	//initialize values as 0
	maxSpeed = 0.4f;
	speed = 0;

	accelerationFactor = 0.005f;
	acceleration = 0;
	maxAcceleration = 0.5f;

	steerFactor = 1.2f;
	steerAngle = 0;

	health = 30;
	isDrivingForward = false;
	isDrivingBackward = false;
	isCollidedWithBarrier = false;

	isInversedControlled = false;

	init = false;

	playerInstance = Player::getInstance();
}

float Car::carScale = 20;

Car::Car(float x, float y, float z, float maxSpeedCar, float accelerationFactorCar, float maxAccelerationCar, float steerFactorCar)
{
	car.setLocation(x, y, z);
	newPosition = (x, y, z);

	maxSpeed = maxSpeedCar;
	accelerationFactor = accelerationFactorCar;
	maxAcceleration = maxAccelerationCar;
	steerFactor = steerFactorCar;

	speed = 0;
	acceleration = 0;
	steerAngle = 0;
	health = 30;
	isDrivingBackward = false;
	isDrivingForward = false;
	isCollidedWithBarrier = false;
	isInversedControlled = false;

	init = false;

	playerInstance = Player::getInstance();
}

Car::~Car()
{
}

void Car::setInverseControls(bool x)
{
	isInversedControlled = x;
}

bool Car::returnInverseControls()
{
	return isInversedControlled;
}

int Car::returnHealth(void)
{
	return health;
}

void Car::setHealth(int input)
{
	health = input;
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

	if (playerInstance->getHealthUpgradeStatus() == true && init == false)
	{
		health = 40;
		init = true;
	}

	if (isInversedControlled == false)
	{
		if (Application::IsKeyPressed(VK_UP) && isDrivingBackward == false)
		{
			if (playerInstance->getAccelerationUpgradeStatus() == true)
			{
				accelerationFactor = 0.01f;
			}
			isDrivingForward = true;
			isDrivingBackward = false;
			acceleration += accelerationFactor;
			speed += (float)(acceleration * dt);

			newPosition.x += (sin(Math::DegreeToRadian(steerAngle)) * speed);
			newPosition.y = car.returnYPos();
			newPosition.z += (cos(Math::DegreeToRadian(steerAngle)) * speed);
			car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);


			if (playerInstance->getMaxAccelerationUpgradeStatus() == true)
			{
				maxAcceleration = 0.7f;
			}
			if (acceleration > maxAcceleration)
			{
				acceleration = maxAcceleration;
			}

			if (playerInstance->getMaxSpeedUpgradeStatus() == true)
			{
				maxSpeed = 0.5f;
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
			if (playerInstance->getAccelerationUpgradeStatus() == true)
			{
				accelerationFactor = 0.01f;
			}
			isDrivingForward = false;
			isDrivingBackward = true;
			acceleration -= accelerationFactor;
			speed += (float)(acceleration * dt);

			newPosition.x += (sin(Math::DegreeToRadian(steerAngle)) * speed);
			newPosition.y = newPosition.y;
			newPosition.z += (cos(Math::DegreeToRadian(steerAngle)) * speed);
			car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

			if (playerInstance->getMaxAccelerationUpgradeStatus() == true)
			{
				maxAcceleration = 0.7f;
			}
			if (acceleration < -maxAcceleration)
			{
				acceleration = -maxAcceleration;
			}

			if (playerInstance->getMaxSpeedUpgradeStatus() == true)
			{
				maxSpeed = 0.5f;
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
			if (playerInstance->getSteerUpgradeStatus() == true)
			{
				steerFactor = 1.8f;
			}
			if (isDrivingForward)
			{
				steerAngle -= steerFactor;
				//speed *= 0.96f;
			}
			if (isDrivingBackward)
			{
				steerAngle += steerFactor;
				//speed *= 0.96f;
			}
			speed *= 0.97f;
		}
		if (Application::IsKeyPressed(VK_LEFT))
		{
			if (playerInstance->getSteerUpgradeStatus() == true)
			{
				steerFactor = 1.8f;
			}
			if (isDrivingForward)
			{
				steerAngle += steerFactor;
			}
			if (isDrivingBackward)
			{
				steerAngle -= steerFactor;
			}
			speed *= 0.97f;
		}
	}

	if (isInversedControlled == true)
	{
		if (Application::IsKeyPressed(VK_DOWN) && isDrivingBackward == false)
		{
			if (playerInstance->getAccelerationUpgradeStatus() == true)
			{
				accelerationFactor = 0.01f;
			}
			isDrivingForward = true;
			isDrivingBackward = false;
			acceleration += accelerationFactor;
			speed += (float)(acceleration * dt);

			newPosition.x += (sin(Math::DegreeToRadian(steerAngle)) * speed);
			newPosition.y = car.returnYPos();
			newPosition.z += (cos(Math::DegreeToRadian(steerAngle)) * speed);
			car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);


			if (playerInstance->getMaxAccelerationUpgradeStatus() == true)
			{
				maxAcceleration = 0.7f;
			}
			if (acceleration > maxAcceleration)
			{
				acceleration = maxAcceleration;
			}

			if (playerInstance->getMaxSpeedUpgradeStatus() == true)
			{
				maxSpeed = 0.5f;
			}
			if (speed > maxSpeed)
			{
				speed = maxSpeed;
			}
		}
		if (isDrivingForward)
		{
			if (!Application::IsKeyPressed(VK_DOWN))
			{
				decelerateCar(dt);
			}
		}
		if (Application::IsKeyPressed(VK_UP) && isDrivingForward == false)
		{
			if (playerInstance->getAccelerationUpgradeStatus() == true)
			{
				accelerationFactor = 0.01f;
			}
			isDrivingForward = false;
			isDrivingBackward = true;
			acceleration -= accelerationFactor;
			speed += (float)(acceleration * dt);

			newPosition.x += (sin(Math::DegreeToRadian(steerAngle)) * speed);
			newPosition.y = newPosition.y;
			newPosition.z += (cos(Math::DegreeToRadian(steerAngle)) * speed);
			car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

			if (playerInstance->getMaxAccelerationUpgradeStatus() == true)
			{
				maxAcceleration = 0.7f;
			}
			if (acceleration < -maxAcceleration)
			{
				acceleration = -maxAcceleration;
			}

			if (playerInstance->getMaxSpeedUpgradeStatus() == true)
			{
				maxSpeed = 0.5f;
			}
			if (speed < -maxSpeed) //negative because it is moving in the opposite direction
			{
				speed = -maxSpeed;
			}
		}
		if (isDrivingBackward)
		{
			if (!Application::IsKeyPressed(VK_UP))
			{
				decelerateCar(dt);
			}
		}
		if (Application::IsKeyPressed(VK_LEFT))
		{
			if (playerInstance->getSteerUpgradeStatus() == true)
			{
				steerFactor = 1.8f;
			}
			if (isDrivingForward)
			{
				steerAngle -= steerFactor;
			}
			if (isDrivingBackward)
			{
				steerAngle += steerFactor;
			}
			speed *= 0.97f;
		}
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			if (playerInstance->getSteerUpgradeStatus() == true)
			{
				steerFactor = 1.8f;
			}
			if (isDrivingForward)
			{
				steerAngle += steerFactor;
			}
			if (isDrivingBackward)
			{
				steerAngle -= steerFactor;
			}
			speed *= 0.97f;
		}
	}
}

void Car::decelerateCar(double dt)
{
	if (isDrivingForward)
	{
		if (acceleration >= 0)
		{
			acceleration = 0;
		}
		acceleration -= 0.025f;
		speed += (float)(acceleration * dt);
		newPosition.x = car.returnXPos() + (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newPosition.y = car.returnYPos();
		newPosition.z = car.returnZPos() + (cos(Math::DegreeToRadian(steerAngle)) * speed);
		car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

		if (acceleration < 0.f)
		{
			acceleration = 0.f;
			speed -= 0.01f;
		}
		if (speed < 0.f)
		{
			speed = 0.f;
			isDrivingForward = false;
		}
	}
	if (isDrivingBackward)
	{
		if (acceleration <= 0)
		{
			acceleration = 0;
		}
		acceleration += 0.025f;
		speed += (float)(acceleration * dt);
		newPosition.x = car.returnXPos() + (sin(Math::DegreeToRadian(steerAngle)) * speed);
		newPosition.y = car.returnYPos();
		newPosition.z = car.returnZPos() + (cos(Math::DegreeToRadian(steerAngle)) * speed);
		car.setLocation(newPosition.x, car.returnYPos(), newPosition.z);

		if (acceleration > 0.f)
		{
			acceleration = 0.f;
			speed += 0.01f;
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