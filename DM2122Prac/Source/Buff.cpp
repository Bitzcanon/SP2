#include "Buff.h"

Buff::Buff()
{
	timer = 0;
	effect = 0;
}

Buff::~Buff()
{

}

void Buff::setTimer(float time)
{
	timer = time;
}

float Buff::returnTimer()
{
	return timer;
}

float Buff::returnEffect()
{
	return effect;
}

