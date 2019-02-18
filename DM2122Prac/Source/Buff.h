#ifndef BUFF_H
#define BUFF_H

class Buff
{
public:
	Buff();
	Buff(float , float , float);
	~Buff();
	//return coordinates
	float returnxPos();
	float returnyPos();
	float returnzPos();

	void setxPos(float);
	void setyPos(float);
	void setzPos(float);
	//

	//booleans for whether the buff has been activated
	bool returnCondition();
	void setCondition(bool);
	//

	//return rotation
	float returnBuffRotation();

	int returnBuffQuantity();
	float returnEffect();
	float returnTimer();
	void setTimer(float);

	void setRotateBy(float);

	//How many buffs are created
	static int BuffCount;
	static float timer;
	static bool activateYet;

protected:
	int speedBuffQuantity;


	float rotateBy;
	float xPos;
	float yPos;
	float zPos;

};

#endif
