#ifndef SPEEDBUFF_H
#define SPEEDBUFF_H

#include "Buff.h"
#include <vector>

class SpeedBuff : public Buff
{
public:
	SpeedBuff();
	~SpeedBuff();

	float returnxPos(int);
	float returnyPos(int);
	float returnzPos(int);

private:
	vector <float> xPos;
	vector <float> yPos;
	vector <float> zPos;
};

#endif