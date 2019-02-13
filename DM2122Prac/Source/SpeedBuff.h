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
	int returnSpeedBuffRotation(int);

	int returnSpeedBuffQuantity();
	

private:
	int speedBuffQuantity;
	
	std::vector <float> rotateBy;
	std::vector <float> xPos;
	std::vector <float> yPos;
	std::vector <float> zPos;
};

#endif