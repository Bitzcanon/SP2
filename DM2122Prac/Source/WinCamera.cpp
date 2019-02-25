#include "WinCamera.h"
#include "Application.h"
#include "Mtx44.h"

WinCamera::WinCamera()
{
}

WinCamera::~WinCamera()
{
}

void WinCamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	this->up = defaultUp = up;
}

void WinCamera::Update(double dt)
{
	static const float CAMERA_SPEED = 50.f;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void WinCamera::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}