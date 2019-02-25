#ifndef SP2_COINCOLLECTIONSCENE_H
#define	SP2_COINCOLLECTIONSCENE_H

#include "Scene.h"
#include "Camera3.h"
#include "FPSCamera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Definitions.h"

#include "RenderStrings.h"
#include "Barrier.h"
#include "Car.h"
#include "Player.h"
#include "Coins.h"
#include "Music.h"

#include <string>
using namespace std;

class SP2_CoinCollectionScene : public Scene
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

		GEO_TESTCAR,

		GEO_KART,
		GEO_WHEELS,
		GEO_COLOR,

		GEO_ROADBLOCK,
		GEO_MAZETILE,
		GEO_COINS,

		NUM_GEOMETRY,
	};

public:
	SP2_CoinCollectionScene();
	~SP2_CoinCollectionScene();

	virtual void Init();

	virtual void Update(double dt);
	virtual bool CollisionChecker(int type, int index, float objX, float objZ, float length, float width);

	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;
	MS modelStack, viewStack, projectionStack;
	Light light[1]; //array size is the number of light sources in the scene

	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void initBarrier();
	void loadBarrierCoordinates();

	void initCoins();
	int countCoins();

	string UpdateFrameRate(float string);

	float FPS;

	float timer;

	Barrier *Barriers[MAZETILECOUNT];

	//Declaration of class instances
	RenderStrings texts;
	Car Vehicle;
	Player *playerInstance;
	RenderStrings text; // text file that stores the car locations

	float bounceTime;
	float vehicleSpeed;

	Vector3 cameraPos;
	Vector3 cameraTarget;

	bool isWon;
	bool displayUpgrades;

	bool healthUpgradeLive;
	bool speedUpgradeLive;
	bool accelerationUpgradeLive;
	bool maxAccelerationUpgradeLive;
	bool steerUpgradeLive;

	vector <float> BarrierList;

	Coins coin[32];
	bool coinappeared;
	float coinrotation;
	bool goingup;
	float coinup;

	Music sounds;
};

#endif // ! SP2_CoinCollectionScene_H