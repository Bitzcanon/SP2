#ifndef FPSCamera_H
#define FPSCamera_H

#include "Vector3.h"
#include "Mtx44.h"


class FPSCamera
{
public:

	Vector3 target;
	Vector3 up;
	Vector3 front;
	Vector3 position;

	FPSCamera();
	~FPSCamera();
	virtual void Init(const Vector3& pos);
	virtual void Reset();
	virtual void Update(double dt);

	Mtx44 LookAt();
	void Invert();

private:
	bool firstMouse;
	double lastX = 0.0;
	double lastY = 0.0;
	float sensitivity = 0.08f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	void UpdateMouse();
};

#endif