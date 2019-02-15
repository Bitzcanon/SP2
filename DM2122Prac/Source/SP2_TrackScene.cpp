#include "SP2_TrackScene.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"


SP2_TrackScene::SP2_TrackScene()
{
	
}

SP2_TrackScene::~SP2_TrackScene()
{

}

void SP2_TrackScene::Init()
{
	bounceTime = 0;
	transitionColor = 0;
	conditionTester = false;
	condition = "Something Happened ! OWO";
	//Set background color to dark blue (Before this are initialized variables, after is the rest)
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

	// Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	//Enable back face culling
	glDisable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Generate default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");


	//Use our shader
	glUseProgram(m_programID);

	//Initialise initial Camera position
	//camera.Init(Vector3(0, 20, 1), Vector3(0, 20, 0), Vector3(0, 1, 0)); //For Camera3
	camera.Init(Vector3(0, 20, 0)); //For FPS Camera (Only for NPCScene, testing in TrackScene

	//Light parameters
	//Lower floor lighting
	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 60, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 4.f;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);
	glUniform1i(m_parameters[U_NUMLIGHTS], 3); //This value is the number of lights in the scene

	//Initialise all meshes to NULL
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	//Skyboxes: http://www.custommapmakers.org/skyboxes.php
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("LEFT", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//Colors//Blue.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("RIGHT", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("TOP", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("BOTTOM", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("FRONT", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("BACK", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_PROMPT] = MeshBuilder::GenerateText("prompt", 16, 16);
	meshList[GEO_PROMPT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_TESTCAR] = MeshBuilder::GenerateCube("Car", Color(0, 1, 0), 5, 1, 1);

	//Default init for kart
	meshList[GEO_KART] = MeshBuilder::GenerateOBJ("Car", texts.returnKartString(0));
	meshList[GEO_KART]->textureID = LoadTGA(texts.returnColorString(1).c_str());
	//
	cout << texts.returnColorString(1);

	meshList[GEO_WHEELS] = MeshBuilder::GenerateOBJ("Car", texts.returnWheelsString(0));

	meshList[GEO_WHEEL] = MeshBuilder::GenerateOBJ("Car", texts.returnWheelString(0));

	//Default init for kart

	meshList[GEO_TRACK] = MeshBuilder::GenerateOBJ("modelTrack", "OBJ//Track.obj");

	meshList[GEO_SPEEDBUFF] = MeshBuilder::GenerateOBJ("SpeedBuff", "OBJ//SpeedBoost.obj");
	meshList[GEO_SPEEDBUFF]->textureID = LoadTGA("Image//SpeedBoostTexture.tga");

	meshList[GEO_ROADBLOCK] = MeshBuilder::GenerateOBJ("RoadBlock", "OBJ//RoadBlock.obj");

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("Light Sphere", Color(1.f, 1.f, 1.f), 32, 36, 1.f);


	//Set projection to Perspective and load projection matrix
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
	projectionStack.LoadMatrix(projection);

	//Initialise variables
	vehicleSpeed = 0;
	cameraPosX = Vehicle.newPosition.x;
	cameraPosY = Vehicle.newPosition.y;
	cameraPosZ = Vehicle.newPosition.z;

	cameraTargetX = Vehicle.newPosition.x + 1;
	cameraTargetY = Vehicle.newPosition.y + 1;
	cameraTargetZ = Vehicle.newPosition.z + 10;
}

void SP2_TrackScene::UpdateBuffs(double dt)
{
}

void SP2_TrackScene::Update(double dt)
{
	FPS = 1.f / (float)dt;
	
	if (Application::IsKeyPressed('U'))
	{
		if (bounceTime <= 0)
		{
			transitionColor += 1;
			if (transitionColor > 4)
			{
				transitionColor = 0;
			}
			meshList[GEO_KART]->textureID = LoadTGA(texts.returnColorString(transitionColor).c_str());
			bounceTime = 0.5;
		}
	}
	
	if (bounceTime > 0)
	{
		bounceTime -= 1 * dt;
	}

	/*Speedbuff logic done by Gary*/
	for (int i = 0; i < SBuff.returnSpeedBuffQuantity(); i++)
	{
		if (CollisionChecker(1 ,i, SBuff.returnxPos(i), SBuff.returnzPos(i), 1, 1) == true)
		{
			SBuff.setTimer(4);
			SBuff.setCondition(true);
		}
	}
	//Timer after stepping on SpeedBuff
	if (SBuff.returnTimer() > 0)
	{
		SBuff.setTimer(SBuff.returnTimer() - 1 * dt);
		Vehicle.setSpeed(0.2);
	}
	else if (SBuff.returnTimer() < 0 && SBuff.returnCondition() == true)
	{
		SBuff.setCondition(false);
	}

	/*RoadBlock logic done by Winston*/
	for (int i = 0; i < RoadBlock.returnBarrierQuantity(); i++)
	{
		if (CollisionChecker(2 ,i, RoadBlock.returnxPos(i), RoadBlock.returnzPos(i), 1.6f, 1.f) == true) //1.6 as the length due to the model being slightly shorter than 2 (as seen in Maya)
		{
			RoadBlock.setTimer(0.2f);
			Vehicle.setSpeed(Vehicle.returnSpeed() * (-1.f - 0.2f));
			Vehicle.setIsCollided(true);
		}
	}
	//Timer after colliding with road block, to prevent player from having backward controls
	if (RoadBlock.returnTimer() > 0)
	{
		RoadBlock.setTimer(RoadBlock.returnTimer() - 1 * dt);
		
	}
	else if (RoadBlock.returnTimer() < 0 && Vehicle.returnIsCollided() == true)
	{
		Vehicle.setIsCollided(false);
		Vehicle.setAcceleration(0);
		Vehicle.setSpeed(0);
	}

	//Miscellaneous controls
	if (Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //Toggle fill mode
	}
	if (Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Toggle wireframe mode
	}

	UpdateFrameRate(FPS);

	/*Vehicle Movement & Camera movement logic done by Winston*/
	Vehicle.Update(dt);
	vehicleSpeed = Vehicle.returnSpeed();

	cameraPosX = (Vehicle.newPosition.x - sin(Math::DegreeToRadian(Vehicle.steerAngle)) * 5) * 10;
	cameraPosY = Vehicle.newPosition.y + 20;
	cameraPosZ = (Vehicle.newPosition.z - cos(Math::DegreeToRadian(Vehicle.steerAngle)) * 5) * 10;

	cameraTargetX = Vehicle.newPosition.x * 10 ;
	cameraTargetY = Vehicle.newPosition.y;
	cameraTargetZ = Vehicle.newPosition.z * 10;

	camera.Update(dt);

	/*World border collision detection logic done by Winston*/
	if (((Vehicle.newPosition.x * 10) >= 495.f) || ((Vehicle.newPosition.x * 10) <= -495.f) || ((Vehicle.newPosition.z * 10) >= 495.f) || ((Vehicle.newPosition.z * 10) <= -495.f))
	{
		RoadBlock.setTimer(0.2f);
		Vehicle.setSpeed(Vehicle.returnSpeed() * (-1.f - 0.2f));
		Vehicle.setIsCollided(true);
	}
}

/*Original logic done by Gary, Function and code organization done by Winston*/
bool SP2_TrackScene::CollisionChecker(int type, int index, float objX, float objZ, float length, float width)
{
	float minimumXObj = objX / Vehicle.returnCarScale();
	float minimumZObj = objZ / Vehicle.returnCarScale();
	float maximumXObj;
	float maximumZObj;

	switch (type) //1 == Speedboost, 2 == Barrier
	{
		case 1:
		{
			maximumXObj = objX / Vehicle.returnCarScale() + length;
			maximumZObj = objZ / Vehicle.returnCarScale() + width;
		}
		case 2:
		{
			maximumXObj = objX / Vehicle.returnCarScale() + length * RoadBlock.returnBarrierScale(index);
			maximumZObj = objZ / Vehicle.returnCarScale() + width * RoadBlock.returnBarrierScale(index);
		}
	}
	
	//tmp var for car pos
	float carXMin = Vehicle.newPosition.x;
	float carXMax = Vehicle.newPosition.x + length;

	float carZMin = Vehicle.newPosition.z;
	float carZMax = Vehicle.newPosition.z + width;

	if (carXMax < minimumXObj || carXMin > maximumXObj)
	{
		//cout << "No Collide" << endl;
		return false;
	}
	else if (carZMax < minimumZObj || carZMin > maximumZObj)
	{
		//cout << "No Collide" << endl;
		return false;
	}
	else
	{
		//cout << "Collide" << endl;
		return true;
	}	
}

static const float SKYBOXSIZE = 1000.f;

/*FPS counter done by Winston*/
string SP2_TrackScene::UpdateFrameRate(float fps)
{
	int IntFPS = static_cast<int>(fps); //Convert FPS to 2 digits for display
	string fpsCount = to_string(IntFPS);

	return fpsCount;
}

void SP2_TrackScene::RenderMesh(Mesh *mesh, bool enableLight) //Pass in mesh name to go through this to enable lighting for that mesh
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SP2_TrackScene::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character
			Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() *
			characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SP2_TrackScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST);

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x + 3, y, 0);
	modelStack.Scale(size * 2, size * 2, size * 2);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f, 0.5, 0); //1.0f is the spacing of each character
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void SP2_TrackScene::RenderSkybox()
{
	//Left side of Skybox
	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 198, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
		modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
		RenderMesh(meshList[GEO_LEFT], false);
	}
	modelStack.PopMatrix();
	//Left side of Skybox

	//Right side of Skybox
	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 198, 0);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
		modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
		RenderMesh(meshList[GEO_RIGHT], false);
	}
	modelStack.PopMatrix();
	//Right side of Skybox

	//Front of Skybox
	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 198, 0);
		modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
		modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
		RenderMesh(meshList[GEO_FRONT], false);
	}
	modelStack.PopMatrix();
	//Front of Skybox

	//Back of Skybox
	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 198, 0);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
		modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
		RenderMesh(meshList[GEO_BACK], false);
	}
	modelStack.PopMatrix();
	//Back of Skybox

	//Top of Skybox
	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 198, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
		modelStack.Rotate(90, 0, 0, 1);
		modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
		RenderMesh(meshList[GEO_TOP], false);
	}
	modelStack.PopMatrix();
	//Top of Skybox

	//Bottom of Skybox
	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 498.f, 0);
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
		RenderMesh(meshList[GEO_BOTTOM], false);
	}
	modelStack.PopMatrix();
	//Bottom of Skybox
}

void SP2_TrackScene::Render()
{
	//Clear color & depth buffer every time
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Define the view/ camera lookat and load the view matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	//viewStack.LookAt(cameraPosX, cameraPosY, cameraPosZ, cameraTargetX, cameraTargetY, cameraTargetZ, 0, 1, 0); //Switch to this once all implementations are done

	modelStack.LoadIdentity();
	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);

		lightDir.Set(light[1].position.x, light[1].position.y, light[1].position.z);
		lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);

		lightDir.Set(light[2].position.x, light[2].position.y, light[2].position.z);
		lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);

		lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);

		lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
		spotDirection_cameraspace = viewStack.Top() * light[2].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

		lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);

		lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//Draw Axes (For debugging purposes)
	RenderMesh(meshList[GEO_AXES], false);

	//Draw Track (Modelled and rendered by Gary)
	modelStack.PushMatrix();
	{
		float trackScale = Vehicle.returnCarScale() * 2;
		modelStack.Scale(trackScale, trackScale, trackScale);
		modelStack.Translate(0, -0.495f, 0);

		RenderMesh(meshList[GEO_TRACK], true);
	}
	modelStack.PopMatrix();

	//Draw Test Car (Modelled by Gary, rendered by Winston)
	modelStack.PushMatrix();
	{
		modelStack.Scale(Vehicle.returnCarScale(), Vehicle.returnCarScale(), Vehicle.returnCarScale());

		modelStack.Translate(Vehicle.newPosition.x, Vehicle.newPosition.y, Vehicle.newPosition.z);
		modelStack.Rotate(Vehicle.steerAngle, 0, 1, 0);

		RenderMesh(meshList[GEO_KART], true);

		modelStack.PushMatrix();
			RenderMesh(meshList[GEO_WHEEL], true);
			modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	//Draw Speed buffs in the map (Modelled and rendered by Gary)
	for (int i = 0; i < SBuff.returnSpeedBuffQuantity(); i++)
	{
		modelStack.PushMatrix();
		
		modelStack.Translate(SBuff.returnxPos(i), SBuff.returnyPos(i), SBuff.returnzPos(i));
		modelStack.Scale(Vehicle.returnCarScale(), Vehicle.returnCarScale(), Vehicle.returnCarScale());
		modelStack.Rotate(SBuff.returnSpeedBuffRotation(i), 0, 1, 0);
		RenderMesh(meshList[GEO_SPEEDBUFF], false);
		modelStack.PopMatrix();
	}

	//Draw Road Blocks in the map (Modelled by Zheng Hong, rendered by Winston)
	for (int i = 0; i < RoadBlock.returnBarrierQuantity(); i++)
	{
		modelStack.PushMatrix();

		modelStack.Translate(RoadBlock.returnxPos(i), RoadBlock.returnyPos(i), RoadBlock.returnzPos(i));
		modelStack.Scale(Vehicle.returnCarScale() * RoadBlock.returnBarrierScale(i), Vehicle.returnCarScale() * RoadBlock.returnBarrierScale(i), Vehicle.returnCarScale() * RoadBlock.returnBarrierScale(i));
		modelStack.Rotate(RoadBlock.returnBarrierRotation(i), 0, 1, 0);
		RenderMesh(meshList[GEO_ROADBLOCK], true); //set lighting to true once completed
		modelStack.PopMatrix();
	}

	//Draw Skybox
	modelStack.PushMatrix();
	{
		RenderSkybox();

		//Draw UI (Logic and rendering done by Winston)
		modelStack.PushMatrix();
		{
			RenderTextOnScreen(meshList[GEO_TEXT], UpdateFrameRate(FPS), Color(1, 1, 0), 2, 72, 55);

			//Player's Position (FOR DEBUG PURPOSES)
			int vehiclePosX = static_cast<int>(Vehicle.newPosition.x); //Convert x coordinate of the vehicle to 2 digits for display
			int vehiclePosZ = static_cast<int>(Vehicle.newPosition.z); //Convert z coordinate of the vehicle to 2 digits for display

			int cameraX = static_cast<int>(cameraPosX); //Convert x coordinate of the camera to 2 digits for display
			int cameraY = static_cast<int>(cameraPosY); //Convert y coordinate of the camera to 2 digits for display
			int cameraZ = static_cast<int>(cameraPosZ); //Convert z coordinate of the camera to 2 digits for display

			RenderTextOnScreen(meshList[GEO_TEXT], to_string(vehicleSpeed), Color(1, 1, 0), 1, -1, 58);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(vehiclePosX), Color(1, 1, 0), 1, -1, 56);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(vehiclePosZ), Color(1, 1, 0), 1, -1, 54);

			RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraX), Color(1, 0, 0), 1, -1, 52);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraY), Color(1, 0, 0), 1, -1, 50);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraZ), Color(1, 0, 0), 1, -1, 48);

			RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraTargetX), Color(1, 0, 0), 1, -1, 46);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraTargetY), Color(1, 0, 0), 1, -1, 44);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraTargetZ), Color(1, 0, 0), 1, -1, 42);
		}
		modelStack.PopMatrix();

	}
	modelStack.PopMatrix();

	if (SBuff.returnTimer() > 0)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], to_string(SBuff.returnTimer()), Color(1, 1, 0), 3, 0, 0);
	}
}

void SP2_TrackScene::Exit()
{
	// Cleanup here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i] != NULL)
		{
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}