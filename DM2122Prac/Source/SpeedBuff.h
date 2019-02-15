#ifndef SPEEDBUFF_H
#define SPEEDBUFF_H

#include "Buff.h"
#include <vector>

//Logic and Speedbuff class done by Gary

class SpeedBuff : public Buff
{
public:
	SpeedBuff();
	~SpeedBuff();

	float returnxPos(int);
	float returnyPos(int);
	float returnzPos(int);

	bool returnCondition();
	void setCondition(bool);
	
	int returnSpeedBuffRotation(int);

	int returnSpeedBuffQuantity();
	

private:
	int speedBuffQuantity;
	bool condition;

	std::vector <float> rotateBy;
	std::vector <float> xPos;
	std::vector <float> yPos;
	std::vector <float> zPos;
};

#endif