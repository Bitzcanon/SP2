#ifndef Location_H
#define Location_H

class Location
{
public:
	Location();
	~Location();

	float returnXPos() const;
	float returnYPos() const;
	float returnZPos() const;

	void setLocation(float x, float y, float z);

private:
	float xPos;
	float yPos;
	float zPos;

};

#endif