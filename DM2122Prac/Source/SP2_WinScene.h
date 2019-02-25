#ifndef SP2_WinScene_H
#define	SP2_WinScene_H

#include "Scene.h"
//#include "FPSCamera.h"
//#include "MenuCamera.h"
#include "WinCamera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Definitions.h"
#include "Player.h"

#include <string>

using namespace std;

class SP2_WinScene : public Scene
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

		GEO_TRACK,
		GEO_FINISHLINE,
		GEO_PROPELLERFINISH,
		GEO_CHECKPOINT,
		GEO_PROPELLERCHECKPOINT,
		GEO_TESTCAR,

		GEO_TESTTRACK,

		GEO_WINSCREEN,
		GEO_BACKGROUND,

		NUM_GEOMETRY,
	};

public:
	SP2_WinScene();
	~SP2_WinScene();

	virtual void Init();

	virtual void Update(double dt);

	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	WinCamera camera; //Switch to Camera3 once implementations are done

	MS modelStack, viewStack, projectionStack;
	Light light[3]; //array size is the number of light sources in the scene

	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	//initialize game objects

	string UpdateFrameRate(float string);

	float FPS;

	bool conditionTester;


	float ResetTimer;

	Player *playerInstance;

	float bounceTime;

	float propellerRotation;

	float vehicleSpeed;

	Vector3 cameraPos;
	Vector3 cameraTarget;

	float timer;
};

#endif // ! SP2_WinScene_H