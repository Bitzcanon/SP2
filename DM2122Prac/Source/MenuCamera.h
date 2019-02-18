#ifndef MENU_CAMERA_H
#define MENU_CAMERA__H

#include "Camera.h"

class MenuCamera : public Camera
{
public:

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	MenuCamera();
	~MenuCamera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
};

#endif