#ifndef WIN_CAMERA_H
#define WIN_CAMERA__H

#include "Camera.h"

class WinCamera : public Camera
{
public:

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	WinCamera();
	~WinCamera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
};

#endif