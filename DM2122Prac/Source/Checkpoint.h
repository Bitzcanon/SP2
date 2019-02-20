#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <vector>

//Barrier Class done by Winston, orignial logic done by Gary

class Checkpoint
{
public:
	Checkpoint();
	~Checkpoint();

	float returnxPos();
	float returnyPos();
	float returnzPos();

	void setxPos(float);
	void setyPos(float);
	void setzPos(float);

	int returnCheckpointRotation();
	void setCheckpointRotation(float);

	int returnCheckpointScale();
	void setCheckpointScale(int);

	int returnCheckpointQuantity(void);

private:
	int barrierCount;

	float rotateBy;
	float scaleBy;
	float xPos;
	float yPos;
	float zPos;
};

#endif // ! CHECKPOINT_H