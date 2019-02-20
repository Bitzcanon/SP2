#pragma once

class NPCS
{
public:
	NPCS();
	~NPCS();
	void MoveNPC(double dt, int index);
	bool CloseToNPC(float playerx, float playerz);
	void setCoordsNPC(float npcx, float npcz);
	float getx();
	float getz();
	float getDirection();
private:


	float x, z, direction;
	bool close, interacting;
};