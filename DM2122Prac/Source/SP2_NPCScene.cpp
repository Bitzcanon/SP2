#include "SP2_NPCScene.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"


SP2_NPCScene::SP2_NPCScene()
{
	
}

SP2_NPCScene::~SP2_NPCScene()
{

}

void SP2_NPCScene::Init()
{
	rotateAngle = 0;
	bounceTime = 0;

	transitionColor = 0;
	transitionBody = 0;
	transitionWheels = 0;

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
	camera.Init(Vector3(0, 30, 1));

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

	/*light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(500, 500, -500);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1.f;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 1.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	light[2].type = Light::LIGHT_POINT;
	light[2].position.Set(63.5f, 103, 55);
	light[2].color.Set(1, 1, 1);
	light[2].power = 0.5f;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 1.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);*/

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
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
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

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_SURROUNDINGS] = MeshBuilder::GenerateOBJ("Surroundings", "OBJ//Placeholder NPC scene.obj");
	meshList[GEO_SURROUNDINGS]->textureID = LoadTGA("Image//Texture.tga");

	meshList[GEO_NPC_MECHANIC] = MeshBuilder::GenerateOBJ("mechanic", "OBJ//Placeholder sitting NPC.obj");
	meshList[GEO_NPC_MECHANIC]->textureID = LoadTGA("Image//NPC texture.tga");

	meshList[GEO_NPC] = MeshBuilder::GenerateOBJ("randomNPC", "OBJ//Placeholder NPC.obj");
	meshList[GEO_NPC]->textureID = LoadTGA("Image//NPC texture.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("Light Sphere", Color(1.f, 1.f, 1.f), 32, 36, 1.f);

	meshList[GEO_CHOCO] = MeshBuilder::GenerateOBJ("choco", "OBJ//NPC scene chocolates.obj");
	meshList[GEO_CHOCO]->textureID = LoadTGA("Image//Texture.tga");

	meshList[GEO_KART] = MeshBuilder::GenerateOBJ("Car", text.returnKartString(0));
	meshList[GEO_KART]->textureID = LoadTGA(text.returnColorString(0).c_str());

	meshList[GEO_WHEELS] = MeshBuilder::GenerateOBJ("Car", text.returnWheelsString(0));
	meshList[GEO_WHEELS]->textureID = LoadTGA("Image//Colors//Gray.tga");

	meshList[GEO_GARAGEDOOR] = MeshBuilder::GenerateOBJ("door", "OBJ//GarageDoor.obj");
	meshList[GEO_GARAGEDOOR]->textureID = LoadTGA("Image//GarageDoorTexture.tga");

	meshList[GEO_COIN] = MeshBuilder::GenerateOBJ("coin", "OBJ//Coin.obj");
	meshList[GEO_COIN]->textureID = LoadTGA("Image//PlaceholderCoinTexture.tga");

	//Set projection to Perspective and load projection matrix
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
	projectionStack.LoadMatrix(projection);

	NPCs[0].x = -20.f; NPCs[0].z = 20.f; NPCs[0].close = false; NPCs[0].direction = 0; NPCs[0].interacting = false; //initialises the first NPC's starting position, bools for when player is close
	NPCs[1].x = 6.f; NPCs[1].z = -50.f; NPCs[1].close = false; NPCs[1].direction = 0; NPCs[1].interacting = false; //and bool when player is interacting with the NPC
	GarageDoorY = 6.685f; GarageDoorRotate = 0.f; GarageOpen = false;
	coins[0].SetCoinCoords(10.f, 50.f); coins[1].SetCoinCoords(100.f, 90.f);
}

void SP2_NPCScene::Update(double dt)
{
	FPS = 1.f / (float)dt;

	if (rotateAngle < 360)
	{
		rotateAngle += 80.f * (float)dt;
	}
	else
	{
		rotateAngle = 0;
	}

	if (Application::IsKeyPressed(VK_RIGHT))
	{
		if (bounceTime <= 0)
		{
			transitionColor += 1;
			if (transitionColor > 4)
			{
				transitionColor = 0;
			}
			delete meshList[16];
			meshList[GEO_KART] = MeshBuilder::GenerateOBJ("Car", text.returnKartString(transitionBody));
			meshList[GEO_KART]->textureID = LoadTGA(text.returnColorString(transitionColor).c_str());
			bounceTime = 0.2f;
		}
	}
	else if (Application::IsKeyPressed(VK_UP))
	{
		if (bounceTime <= 0)
		{
			transitionBody += 1;
			if (transitionBody > 2)
			{
				transitionBody = 0;
			}
			delete meshList[16];
			meshList[GEO_KART] = MeshBuilder::GenerateOBJ("Car", text.returnKartString(transitionBody));
			meshList[GEO_KART]->textureID = LoadTGA(text.returnColorString(transitionColor).c_str());
			bounceTime = 0.2f;
		}
	}
	else if (Application::IsKeyPressed(VK_DOWN))
	{
		if (bounceTime <= 0)
		{
			transitionWheels += 1;
			if (transitionWheels > 2)
			{
				transitionWheels = 0;
			}
			delete meshList[17];
			meshList[GEO_WHEELS] = MeshBuilder::GenerateOBJ("Wheels", text.returnWheelsString(transitionWheels));
			meshList[GEO_WHEELS]->textureID = LoadTGA("Image//Colors//Gray.tga");
			bounceTime = 0.2f;
		}
	}

	if (bounceTime > 0)
	{
		bounceTime -= 1.f * (float)dt;
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

	//Check for camera bounds on skybox
	if (camera.position.x < 500.f && camera.position.x > -500.f && camera.position.z < 500.f && camera.position.z > -500.f && camera.position.y < 700 && camera.position.y > 0)
	{
		camera.Update(dt);
	}
	//Camera looks opposite direction when hitting y bounds, but does not do anything when hitting x and z bounds
	else if (camera.position.x >= 499.f)
	{
		camera.position.x = 498.f;
	}
	else if (camera.position.x <= -499.f)
	{
		camera.position.x = -498.f;
	}
	else if (camera.position.z >= 499.f)
	{
		camera.position.z = 498.f;
	}
	else if (camera.position.z <= -499.f)
	{
		camera.position.z = -498.f;
	}
	else if (camera.position.y <= 0.f)
	{
		camera.position.y = 1.f;
		camera.target.y = 1.f;
	}
	else if (camera.position.y >= 699.f)
	{
		camera.position.y = 698.f;
		camera.target.y = 0.f;
	}

	MoveNPC(dt);
	UpdateDoor(dt);
	coins[0].CoinCollision(camera.position.x, camera.position.z);
	coins[1].CoinCollision(camera.position.x, camera.position.z);
}

void SP2_NPCScene::UpdateDoor(double dt)
{
	if (GarageOpen)
	{
		if (GarageDoorY < 12.537f)
		{
			GarageDoorY += (float)dt * 2.5f;
		}
		if (GarageDoorRotate > -67.338f)
		{
			GarageDoorRotate -= (float)dt * 20.f;
		}
	}
	if (!GarageOpen)
	{
		if (GarageDoorY > 6.685f)
		{
			GarageDoorY -= (float)dt * 2.5f;
		}
		if (GarageDoorRotate < 0.f)
		{
			GarageDoorRotate += (float)dt * 40.f;
		}
	}
	if (Application::IsKeyPressed('F') && GarageOpen && CloseToDoor())
	{
		GarageOpen = false;
	}
	else if (Application::IsKeyPressed('F') && !GarageOpen && CloseToDoor())
	{
		GarageOpen = true;
	}
}

void SP2_NPCScene::MoveNPC(double dt) //Moves the 2 NPCs that "walks" around
{
	if (!NPCs[0].close)
	{
		switch ((int)NPCs[0].direction)
		{
		case 0:
			if (NPCs[0].x < 20.f)
			{
				NPCs[0].x += (float)dt * 5.f;
			}
			else
			{
				NPCs[0].direction = 1.f;
			}
			break;
		case 1:
			if (NPCs[0].z > -20.f)
			{
				NPCs[0].z -= (float)dt * 5.f;
			}
			else
			{
				NPCs[0].direction = 2.f;
			}
			break;
		case 2:
			if (NPCs[0].x > -20.f)
			{
				NPCs[0].x -= (float)dt * 5.f;
			}
			else
			{
				NPCs[0].direction = 3.f;
			}
			break;
		case 3:
			if (NPCs[0].z < 20.f)
			{
				NPCs[0].z += (float)dt * 5.f;
			}
			else
			{
				NPCs[0].direction = 0.f;
			}
			break;
		}
	}

	if (!NPCs[1].close)
	{
		switch ((int)NPCs[1].direction)
		{
		case 0:
			if (NPCs[1].x < 10.f && !NPCs[1].close)
			{
				NPCs[1].x += (float)dt * 5.f;
			}
			else
			{
				NPCs[1].direction = 1.f;
			}
			break;
		case 1:
			if (NPCs[1].x > -10.f && !NPCs[1].close)
			{
				NPCs[1].x -= (float)dt * 5.f;
			}
			else
			{
				NPCs[1].direction = 0.f;
			}
			break;
		}
	}
}

static const float SKYBOXSIZE = 1000.f;

string SP2_NPCScene::UpdateFrameRate(float fps)
{
	int IntFPS = static_cast<int>(fps); //Convert FPS to 2 digits for display
	string fpsCount = to_string(IntFPS);

	return fpsCount;
}

void SP2_NPCScene::RenderMesh(Mesh *mesh, bool enableLight) //Pass in mesh name to go through this to enable lighting for that mesh
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

void SP2_NPCScene::RenderText(Mesh* mesh, std::string text, Color color)
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

void SP2_NPCScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SP2_NPCScene::RenderSkybox()
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

bool SP2_NPCScene::CloseToSellerNPC() //To check if player is close to the NPCs that are moving
{
	if (camera.position.x >= NPCs[0].x * 5.f - 40.f && camera.position.x <= NPCs[0].x * 5.f + 40.f)
	{
		if (camera.position.z >= NPCs[0].z * 5.f - 40.f && camera.position.z <= NPCs[0].z * 5.f + 40.f)
		{
			NPCs[0].close = true;
			return true;
		}
	}
	if (camera.position.x >= NPCs[1].x * 5.f - 40.f && camera.position.x <= NPCs[1].x * 5.f + 40.f)
	{
		if (camera.position.z >= NPCs[1].z * 5.f - 40.f && camera.position.z <= NPCs[1].z * 5.f + 40.f)
		{
			NPCs[1].close = true;
			return true;
		}
	}

	NPCs[0].close = false;
	NPCs[1].close = false;
	return false;
}

bool SP2_NPCScene::CloseToNPC() //To check if player is close to the mechanic NPC
{
	if (camera.position.x >= -190.f - 40.f && camera.position.x <= -190.f + 40.f)
	{
		if (camera.position.z >= -320.f - 40.f && camera.position.z <= -320.f + 40.f)
		{
			return true;
		}
	}
	return false;
}

bool SP2_NPCScene::CloseToDoor()
{
	if (camera.position.x >= -295.f && camera.position.x <= -167.f)
	{
		if (camera.position.z >= -280.f && camera.position.z <= -200.f)
		{
			return true;
		}
	}
	return false;
}

void SP2_NPCScene::Render()
{
	//Clear color & depth buffer every time
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Define the view/ camera lookat and load the view matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
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

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.1f, 0.f);
	modelStack.Scale(5.f, 5.f, 5.f);
	RenderMesh(meshList[GEO_SURROUNDINGS], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(5.f, 5.f, 5.f);
	modelStack.Translate(-38.109f, -0.259f, -62.605f);
	modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
	RenderMesh(meshList[GEO_NPC_MECHANIC], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(5.f, 5.f, 5.f);
	modelStack.Translate(NPCs[0].x, 0.f, NPCs[0].z);
	modelStack.Rotate(NPCs[0].direction * 90.f, 0.f, 1.f, 0.f);
	RenderMesh(meshList[GEO_NPC], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(5.f, 5.f, 5.f);
	modelStack.Translate(NPCs[1].x, 0.f, NPCs[1].z);
	modelStack.Rotate(NPCs[1].direction * 180.f, 0.f, 1.f, 0.f);
	RenderMesh(meshList[GEO_NPC], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.1f, 0.f);
	modelStack.Scale(5.f, 5.f, 5.f);
	RenderMesh(meshList[GEO_CHOCO], true);
	modelStack.PopMatrix();

	if (!coins[0].CheckTaken())
	{
		modelStack.PushMatrix();
		modelStack.Translate(coins[0].getX(), 0.f, coins[0].getZ());
		RenderMesh(meshList[GEO_COIN], true);
		modelStack.PopMatrix();
	}

	if (!coins[1].CheckTaken())
	{
		modelStack.PushMatrix();
		modelStack.Translate(coins[1].getX(), 0.f, coins[1].getZ());
		RenderMesh(meshList[GEO_COIN], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Scale(5.f, 5.f, 5.f);
	modelStack.Translate(-46.369f, GarageDoorY, -56.662f);
	modelStack.Rotate(GarageDoorRotate, 1.f, 0.f, 0.f);
	RenderMesh(meshList[GEO_GARAGEDOOR], false);
	modelStack.PopMatrix();

	//Draw Skybox
	modelStack.PushMatrix();
	{
		RenderSkybox();

		//Draw FPS
		modelStack.PushMatrix();
		{
			RenderTextOnScreen(meshList[GEO_TEXT], UpdateFrameRate(FPS), Color(1, 1, 0), 2, 72, 55);
			
		}
		modelStack.PopMatrix();

		//Player's Position (FOR DEBUG PURPOSES)
		modelStack.PushMatrix();
		{
			int cameraX = static_cast<int>(camera.position.x); //Convert x coordinate of the camera to 2 digits for display
			int cameraY = static_cast<int>(camera.position.y); //Convert y coordinate of the camera to 2 digits for display
			int cameraZ = static_cast<int>(camera.position.z); //Convert z coordinate of the camera to 2 digits for display

			RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraX), Color(1, 1, 0), 1, -1, 58);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraY), Color(1, 1, 0), 1, -1, 56);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraZ), Color(1, 1, 0), 1, -1, 54);
		}
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-240, 10, -380);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	modelStack.Scale(50, 50, 50);
	RenderMesh(meshList[GEO_KART], true);

	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_WHEELS], true);

	modelStack.PopMatrix();
	modelStack.PopMatrix();

	if (CloseToNPC())
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press E to build car", Color(1, 1, 0), 1, -1, 10);
	}
	if (CloseToSellerNPC())
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press E to interact with NPC", Color(1, 1, 0), 1, -1, 10);
	}
	if (CloseToDoor() && !GarageOpen)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press F to open garage door", Color(1, 1, 0), 1, -1, 10);
	}
	else if (CloseToDoor() && GarageOpen)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press F to close garage door", Color(1, 1, 0), 1, -1, 10);
	}
}

void SP2_NPCScene::Exit()
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