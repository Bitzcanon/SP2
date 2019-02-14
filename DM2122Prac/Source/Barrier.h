#ifndef BARRIER_H
#define BARRIER_H

#include <vector>

class Barrier
{
public:
	Barrier();
	~Barrier();

	float returnxPos(int);
	float returnyPos(int);
	float returnzPos(int);

	int returnBarrierRotation(int);
	int returnBarrierScale(int);

	int returnBarrierQuantity(void);

private:
	int barrierQuantity;

	std::vector <float> rotateBy;
	std::vector <float> scaleBy;
	std::vector <float> xPos;
	std::vector <float> yPos;
	std::vector <float> zPos;
};

#endif