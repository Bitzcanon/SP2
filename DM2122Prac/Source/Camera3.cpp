#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	this->up = defaultUp = up;
}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 50.f;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);

	if (Application::IsKeyPressed('A'))
	{
		position = position - right;
		target = position + view;
	}
	if (Application::IsKeyPressed('D'))
	{
		position = position + right;
		target = position + view;
	}
	if (Application::IsKeyPressed('Q'))
	{
		position = position + up;
		target = position + view;
	}
	if (Application::IsKeyPressed('E'))
	{
		position = position - up;
		target = position + view;
	}
	if (Application::IsKeyPressed('W'))
	{
		position = position + view;
		target = target + view;
	}
	if (Application::IsKeyPressed('S'))
	{
		position = position - view;
		target = target - view;
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		Mtx44 rotation;
		float yaw = (float)((CAMERA_SPEED) * dt);
		rotation.SetToRotation(yaw, up.x, up.y, up.z);

		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		Mtx44 rotation;
		float yaw = (float)((CAMERA_SPEED) * dt);
		rotation.SetToRotation(-yaw, up.x, up.y, up.z);

		view = rotation * view;
		target = position + view;
	}
	
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}