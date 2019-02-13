#ifndef BUFF_H
#define BUFF_H

#include "Location.h"

class Buff
{
public:
	Buff();
	~Buff();

	float returnEffect();
	float returnTimer();

	void setTimer(float);


	//Store the location of where the buff is located at [boundary] 
	Location pos;

protected:
	float timer; // how long the buff lasts for
	float effect; // effect that the buf creats


	

};

#endif
