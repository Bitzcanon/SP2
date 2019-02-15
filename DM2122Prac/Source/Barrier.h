#ifndef BARRIER_H
#define BARRIER_H

#include <vector>

//Barrier Class done by Winston, orignial logic done by Gary

class Barrier
{
public:
	Barrier();
	~Barrier();

	float returnxPos(int);
	float returnyPos(int);
	float returnzPos(int);

	float returnTimer();
	void setTimer(float);

	int returnBarrierRotation(int);
	int returnBarrierScale(int);

	int returnBarrierQuantity(void);

private:
	int barrierQuantity;
	float timer;

	std::vector <float> rotateBy;
	std::vector <float> scaleBy;
	std::vector <float> xPos;
	std::vector <float> yPos;
	std::vector <float> zPos;
};

#endif