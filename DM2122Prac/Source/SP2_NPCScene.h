#ifndef SP2_NPCScene_H
#define	SP2_NPCScene_H

#include "Scene.h"
#include "Camera3.h"
#include "FPSCamera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "RenderStrings.h"

#include "Player.h"
#include "Coins.h"
#include "NPCS.h"
#include "Definitions.h"

#include <string>
using namespace std;

class SP2_NPCScene : public Scene
{
private:
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
	 	U_LIGHT2_EXPONENT,

		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_NUMLIGHTS,
		U_LIGHTENABLED,

		U_TOTAL,
	};

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_LIGHTBALL,
		GEO_TEXT,
		GEO_PROMPT,

		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		GEO_KART,
		GEO_WHEELS,
		GEO_COLOR,

		GEO_SURROUNDINGS,
		GEO_NPC_MECHANIC,
		GEO_NPC,
		GEO_CHOCO,
		GEO_GARAGEDOOR,
		GEO_COIN,
		GEO_MARKET1,
		GEO_MARKET2,
		GEO_MARKET3,
		GEO_MARKET4,
		GEO_MARKET5,

		GEO_MENU,

		NUM_GEOMETRY,
	};

public:
	SP2_NPCScene();
	~SP2_NPCScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	FPSCamera camera;
	MS modelStack, viewStack, projectionStack;
	Light light[3]; //array size is the number of light sources in the scene

	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	bool CloseToNPC(); //For the mechanic NPC, which is sitting down
	bool CloseToDoor();
	void UpdateDoor(double dt);
	void UpdateInteraction(int i);
	void UpdateMerchant(int i);
	void RenderMarketPlace();
	string NPCRandomText();
	
	RenderStrings text;
	string UpdateFrameRate(float string);
	Player *playerInstance;

	float FPS;
	float rotateAngle;
	int transitionColor;
	int transitionKart;
	int transitionWheels;
	float bounceTime;
	bool interact;
	NPCS NPCs[7];
	float GarageDoorY, GarageDoorRotate;
	bool GarageOpen;
	Coins coins[2];
	string NPCtext;

	bool healthUpgradeLive;
	bool speedUpgradeLive;
	bool accelerationUpgradeLive;
	bool maxAccelerationUpgradeLive;
	bool steerUpgradeLive;

	bool doMenu;
};

#endif // ! SP2_NPCScene_H