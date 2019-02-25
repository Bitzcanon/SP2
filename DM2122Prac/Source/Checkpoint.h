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

	float returnCheckpointRotation();
	void setCheckpointRotation(float);

	bool returnIsPassedThrough();
	void passedThroughCheckpoint();
	void resetCheckpoint();

	int returnCheckpointQuantity(void);

private:
	int barrierCount;

	bool passedThrough;
	float rotateBy;
	float xPos;
	float yPos;
	float zPos;
};

#endif // ! CHECKPOINT_H