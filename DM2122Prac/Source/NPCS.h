#pragma once

class NPCS
{
public:
	NPCS();
	~NPCS();
	void MoveNPC(double dt, int index);
	bool CloseToNPC(float playerx, float playerz);
	void setCoordsNPC(float npcx, float npcz);
	void setDirection(float i);
	float getx();
	float getz();
	float getDirection();
	bool IsInteracting();
	void Interacts(int i);
private:


	float x, z, direction;
	bool close, interacting;
};