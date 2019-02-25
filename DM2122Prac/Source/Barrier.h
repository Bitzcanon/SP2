#ifndef BARRIER_H
#define BARRIER_H

#include <vector>

//Barrier Class done by Winston, orignial logic done by Gary

class Barrier
{
public:
	Barrier();
	~Barrier();

	float returnxPos();
	float returnyPos();
	float returnzPos();

	void setxPos(float);
	void setyPos(float);
	void setzPos(float);

	float returnTimer();
	void setTimer(float);

	float returnBarrierRotation();
	void setBarrierRotation(float);

	float returnBarrierScale();
	void setBarrierScale(float);

	int returnBarrierQuantity(void);

	static float BarrierDelay;

private:
	int barrierCount;

	/*std::vector <float> rotateBy;
	std::vector <float> scaleBy;
	std::vector <float> xPos;
	std::vector <float> yPos;
	std::vector <float> zPos;*/

	float rotateBy;
	float scaleBy;
	float xPos;
	float yPos;
	float zPos;
};

#endif //! BARRIER_H