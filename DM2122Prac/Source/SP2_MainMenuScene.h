#ifndef SP2_MainMenuScene_H
#define	SP2_MainMenuScene_H

#include "Scene.h"
#include "MenuCamera.h"
#include "FPSCamera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include <string>

using namespace std;

class SP2_MainMenuScene : public Scene
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

		GEO_MENU,
		GEO_ARROW,
		GEO_BACKGROUND,
		GEO_TITLEBACKGROUND,
		GEO_TITLE,

		GEO_MODEL1,
		GEO_MODEL2,

		NUM_GEOMETRY,
	};

	enum GAMESTATE
	{
		NPC,
		MENU,
		RACE,
	};

public:
	SP2_MainMenuScene();
	~SP2_MainMenuScene();

	virtual void Init();

	virtual void Update(double dt);
	
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	GAMESTATE state;
	FPSCamera camera;
	//MenuCamera camera;
	MS modelStack, viewStack, projectionStack;
	Light light[3]; //array size is the number of light sources in the scene

	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	string UpdateFrameRate(float string);

	float bounceTime;
	float FPS;

	bool isMenu;

	float tmpAngle; //remove later
	float tmpx;
	float tmpy;
	float tmpz;

	float transitionTime;

	int sceneNumber;
	double arrowY;
};

#endif // ! SP2_MainMenuScene_H