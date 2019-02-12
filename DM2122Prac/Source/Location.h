#ifndef Location_H
#define Location_H

class Location
{
public:
	Location();
	~Location();

	float returnXPos();
	float returnYPos();
	float returnZPos();

	void setLocation(float x, float y, float z);

private:
	float xPos;
	float yPos;
	float zPos;

};

#endif