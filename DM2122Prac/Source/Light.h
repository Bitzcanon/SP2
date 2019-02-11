#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"

struct Light
{
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};

	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;

	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	// kC = Constant, kL = Linear, kQ = Quadratic == for attenuation use

	Light() //Constructor for light
	{
		color.Set(1.f, 1.f, 1.f);
		power = 1.f;
		kC = 1.f;
		kL = 0.f;
		kQ = 0.f;
	}
};

#endif // !LIGHT_H
