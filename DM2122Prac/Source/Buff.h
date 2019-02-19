#ifndef BUFF_H
#define BUFF_H

class Buff
{
public:
	Buff();
	~Buff();
	//return coordinates
	float returnxPos();
	float returnyPos();
	float returnzPos();

	void setxPos(float);
	void setyPos(float);
	void setzPos(float);
	//

	//return rotation
	float returnBuffRotation();

	void setRotateBy(float);

	//How many buffs are created


protected:
	int speedBuffQuantity;


	float rotateBy;
	float xPos;
	float yPos;
	float zPos;

};

#endif
