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
	playerInstance = Player::getInstance();
}

SP2_TrackScene::~SP2_TrackScene()
{

}
static const float SKYBOXSIZE = 10000.f;
void SP2_TrackScene::loadSpeedBuffCoordinates()
{
	ifstream myfile("TextFiles//Buffs//SpeedBuffCoordinates.txt"); // open text file

	if (myfile.is_open()) // open text file
	{
		int i = 0;
		float tmp;

		while (myfile.eof() == false)
		{
			myfile >> tmp;
			i++;
			SpeedBuffList.push_back(tmp);
		}
		myfile.close();
	}
}

void SP2_TrackScene::loadSlowBuffCoordinates()
{
	ifstream myfile("TextFiles//Buffs//SlowBuffCoordinates.txt"); // open text file

	if (myfile.is_open()) // open text file
	{
		int i = 0;
		float tmp;

		while (myfile.eof() == false)
		{
			myfile >> tmp;
			i++;
			SlowBuffList.push_back(tmp);
		}
		myfile.close();
	}
}

void SP2_TrackScene::loadDamageBuffCoordinates()
{
	ifstream myfile("TextFiles//Buffs//DamageBuffCoordinates.txt"); // open text file

	if (myfile.is_open()) // open text file
	{
		int i = 0;
		float tmp;

		while (myfile.eof() == false)
		{
			myfile >> tmp;
			i++;
			DamageBuffList.push_back(tmp);
		}
		myfile.close();
	}
}

void SP2_TrackScene::loadReverseBuffCoordinates()
{
	ifstream myfile("TextFiles//Buffs//ReverseBuffCoordinates.txt"); // open text file

	if (myfile.is_open()) // open text file
	{
		int i = 0;
		float tmp;

		while (myfile.eof() == false)
		{
			myfile >> tmp;
			i++;
			ReverseBuffList.push_back(tmp);
		}
		myfile.close();
	}
}

void SP2_TrackScene::loadBarrierCoordinates()
{
	ifstream myfile("TextFiles//BarrierCoordinates.txt"); //File directory

	if (myfile.is_open()) //Open the text file
	{
		int i = 0;
		float tmp;

		while (myfile.eof() == false)
		{
			myfile >> tmp;
			i++;
			BarrierList.push_back(tmp);
		}
		myfile.close();
	}
}

void SP2_TrackScene::loadCheckpointCoordinates()
{
	ifstream myfile("TextFiles//CheckpointCoordinates.txt"); //File directory

	if (myfile.is_open()) //Open the text file
	{
		int i = 0;
		float tmp;

		while (myfile.eof() == false)
		{
			myfile >> tmp;
			i++;
			CheckpointList.push_back(tmp);
		}
		myfile.close();
	}
}

void SP2_TrackScene::initBuffs()
{
	for (int i = 0; i < 100; i++)
	{
		Buffs[i] = NULL;
	}

	//new speedbuff
	for (size_t i = 0; i < (SpeedBuffList.size() / 4); i++)
	{
		Buffs[i] = new SpeedBuff;
	}
	//new slowbuff
	for (size_t i = (SpeedBuffList.size() / 4); i < ((SpeedBuffList.size() / 4) + (SlowBuffList.size()/4)); i++)
	{
		Buffs[i] = new SlowBuff;
	}
	// new DamageBuff
	for (size_t i = ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4)); i < ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4) + (DamageBuffList.size() / 4)); i++)
	{
		Buffs[i] = new DamageBuff;
	}
	// new reverseBuff
	for (size_t i = ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4) + (DamageBuffList.size()/4)); i < ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4) + (DamageBuffList.size() / 4) + (ReverseBuffList.size() / 4)); i++)
	{
		Buffs[i] = new ReverseBuff;
	}

	int counter = 1;
	for (size_t i = 0; i < SpeedBuffList.size(); i++) // loop through the total cords in the text file
	{
		int loc = i / 4; 
		// i = 0 , loc = 0 . i = 1 , loc = 0 , i = 2 , loc = 0 , i = 3 , loc = 0 
		// i = 4 , loc = 1 , i = 5 , loc = 1 , i = 6 , loc = 1 , i = 7 , loc = 1
		if (counter == 4)
		{
			Buffs[loc]->setRotateBy(SpeedBuffList[i]);
			counter = 1;
		}
		else if (counter == 3) // 
		{
			Buffs[loc]->setzPos(SpeedBuffList[i]);
			counter += 1;
		}
		else if (counter == 2) // if k = second number in line
		{
			Buffs[loc]->setyPos(SpeedBuffList[i]);
			counter += 1;
		}
		else if (counter == 1) // if k = first number in line
		{
			Buffs[loc]->setxPos(SpeedBuffList[i]);
			counter += 1;
		}
	}
	counter = 1;
	for (size_t i = 0; i < SlowBuffList.size(); i++) // loop through the total cords in the text file
	{
		int loc = ((SpeedBuffList.size() /4 ) + i / 4);
		// i = 0 , loc = 0 . i = 1 , loc = 0 , i = 2 , loc = 0 , i = 3 , loc = 0 
		// i = 4 , loc = 1 , i = 5 , loc = 1 , i = 6 , loc = 1 , i = 7 , loc = 1
		if (counter == 4)
		{
			Buffs[loc]->setRotateBy(SlowBuffList[i]);
			counter = 1;
		}
		else if (counter == 3) // 
		{
			Buffs[loc]->setzPos(SlowBuffList[i]);
			counter += 1;
		}
		else if (counter == 2) // if k = second number in line
		{
			Buffs[loc]->setyPos(SlowBuffList[i]);
			counter += 1;
		}
		else if (counter == 1) // if k = first number in line
		{
			Buffs[loc]->setxPos(SlowBuffList[i]);
			counter += 1;
		}
	}
	counter = 1;
	for (size_t i = 0; i < DamageBuffList.size(); i++) // loop through the total cords in the text file
	{
		int loc = (((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4 )) + ( i / 4));
		// i = 0 , loc = 0 . i = 1 , loc = 0 , i = 2 , loc = 0 , i = 3 , loc = 0 
		// i = 4 , loc = 1 , i = 5 , loc = 1 , i = 6 , loc = 1 , i = 7 , loc = 1
		if (counter == 4)
		{
			Buffs[loc]->setRotateBy(DamageBuffList[i]);
			counter = 1;
		}
		else if (counter == 3) // 
		{
			Buffs[loc]->setzPos(DamageBuffList[i]);
			counter += 1;
		}
		else if (counter == 2) // if k = second number in line
		{
			Buffs[loc]->setyPos(DamageBuffList[i]);
			counter += 1;
		}
		else if (counter == 1) // if k = first number in line
		{
			Buffs[loc]->setxPos(DamageBuffList[i]);
			counter += 1;
		}
	}

	counter = 1;
	for (size_t i = 0; i < ReverseBuffList.size(); i++) // loop through the total cords in the text file
	{
		int loc = (((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4) + (DamageBuffList.size() / 4)) + (i / 4));
		// i = 0 , loc = 0 . i = 1 , loc = 0 , i = 2 , loc = 0 , i = 3 , loc = 0 
		// i = 4 , loc = 1 , i = 5 , loc = 1 , i = 6 , loc = 1 , i = 7 , loc = 1
		if (counter == 4)
		{
			Buffs[loc]->setRotateBy(ReverseBuffList[i]);
			counter = 1;
		}
		else if (counter == 3) // 
		{
			Buffs[loc]->setzPos(ReverseBuffList[i]);
			counter += 1;
		}
		else if (counter == 2) // if k = second number in line
		{
			Buffs[loc]->setyPos(ReverseBuffList[i]);
			counter += 1;
		}
		else if (counter == 1) // if k = first number in line
		{
			Buffs[loc]->setxPos(ReverseBuffList[i]);
			counter += 1;
		}
	}
}

void SP2_TrackScene::initBarrier()
{
	for (int i = 0; i < ROADBLOCKCOUNT; i++) //Init array container to NULL
	{
		Barriers[i] = NULL;
	}

	for (size_t i = 0; i < (BarrierList.size() / ROADBLOCKROWCOUNT); i++)
	{
		Barriers[i] = new Barrier;
	}

	int counter = 1;
	for (size_t i = 0; i < BarrierList.size(); i++) // loop through the total cords in the text file
	{
		int loc = i / ROADBLOCKROWCOUNT;
		// i = 0 , loc = 0 . i = 1 , loc = 0 , i = 2 , loc = 0 , i = 3 , loc = 0 
		// i = 4 , loc = 0 , i = 5 , loc = 1 , i = 6 , loc = 1 , i = 7 , loc = 1

		if (counter == 5)
		{
			Barriers[loc]->setBarrierScale(BarrierList[i]);
			counter = 1;
		}
		else if (counter == 4)
		{
			Barriers[loc]->setBarrierRotation(BarrierList[i]);
			counter += 1;
		}
		else if (counter == 3) // 
		{
			Barriers[loc]->setzPos(BarrierList[i]);
			counter += 1;
		}
		else if (counter == 2) // if k = second number in line
		{
			Barriers[loc]->setyPos(BarrierList[i]);
			counter += 1;
		}
		else if (counter == 1) // if k = first number in line
		{
			Barriers[loc]->setxPos(BarrierList[i]);
			counter += 1;
		}
	}
}

void SP2_TrackScene::initCheckpoint()
{
	for (int i = 0; i < CHECKPOINTCOUNT; i++) //Init array container to NULL
	{
		Checkpoints[i] = NULL;
	}

	for (size_t i = 0; i < (CheckpointList.size() / CHECKPOINTROWCOUNT); i++)
	{
		Checkpoints[i] = new Checkpoint;
	}

	int counter = 1;
	for (size_t i = 0; i < CheckpointList.size(); i++) // loop through the total cords in the text file
	{
		int loc = i / CHECKPOINTROWCOUNT;
		// i = 0 , loc = 0 . i = 1 , loc = 0 , i = 2 , loc = 0 , i = 3 , loc = 0 
		// i = 4 , loc = 0 , i = 5 , loc = 1 , i = 6 , loc = 1 , i = 7 , loc = 1

		if (counter == 4)
		{
			Checkpoints[loc]->setCheckpointRotation(CheckpointList[i]);
			counter = 1;
		}
		else if (counter == 3) // 
		{
			Checkpoints[loc]->setzPos(CheckpointList[i]);
			counter += 1;
		}
		else if (counter == 2) // if k = second number in line
		{
			Checkpoints[loc]->setyPos(CheckpointList[i]);
			counter += 1;
		}
		else if (counter == 1) // if k = first number in line
		{
			Checkpoints[loc]->setxPos(CheckpointList[i]);
			counter += 1;
		}

	}
}

void SP2_TrackScene::Init()
{
	ResetTimer = 0;
	ResetStart = true;

	//Loads SpeedBuff coordinates and initializes the buffs
	loadSpeedBuffCoordinates();
	loadSlowBuffCoordinates();
	loadDamageBuffCoordinates();
	loadReverseBuffCoordinates();
	loadBarrierCoordinates();
	loadCheckpointCoordinates();

	//Loads Buff coordinates
	initBuffs();
	//Loads Barrier coordinates
	initBarrier();
	//Loads Checkpoint coordinates
	initCheckpoint();

	tmpBool = false;

	bounceTime = 0;
	conditionTester = false;

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

	//Use our shader
	glUseProgram(m_programID);

	//Initialise initial Camera position
	//camera.Init(Vector3(0, 20, 1), Vector3(0, 20, 0), Vector3(0, 1, 0));
	camera.Init(Vector3(0, 30, 1));

	//Light parameters
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(998, 998, -998);
	light[0].color.Set(1, 1, 1);
	light[0].power = 2.f;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 1.f;
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

	glUniform1i(m_parameters[U_NUMLIGHTS], 1); //This value is the number of lights in the scene

	//Initialise all meshes to NULL
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	//Skyboxes: http://www.custommapmakers.org/skyboxes.php
	meshList[GEO_LEFT] = MeshBuilder::GenerateOBJ("LEFT", "OBJ//Quad.obj");
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateOBJ("RIGHT", "OBJ//Quad.obj");
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateOBJ("TOP", "OBJ//Quad.obj");
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateOBJ("BOTTOM", "OBJ//Quad.obj");
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");
	meshList[GEO_FRONT] = MeshBuilder::GenerateOBJ("FRONT", "OBJ//Quad.obj");
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateOBJ("BACK", "OBJ//Quad.obj");
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_PROMPT] = MeshBuilder::GenerateText("prompt", 16, 16);
	meshList[GEO_PROMPT]->textureID = LoadTGA("Image//calibri.tga");

	//remove later
	meshList[GEO_TESTCAR] = MeshBuilder::GenerateCube("Car", Color(0, 1, 0), 5, 1, 1);

	//Default init for kart
	meshList[GEO_KART] = MeshBuilder::GenerateOBJ("Car", playerInstance->returnKart());
	meshList[GEO_KART]->textureID = LoadTGA(playerInstance->returnColor().c_str());

	meshList[GEO_WHEELS] = MeshBuilder::GenerateOBJ("Car", playerInstance->returnWheels());
	meshList[GEO_WHEELS]->textureID = LoadTGA("Image//Colors//Gray.tga");
	//

	meshList[GEO_FINISHLINE] = MeshBuilder::GenerateOBJ("modelFinishLine", "OBJ//FinishLine.obj");
	meshList[GEO_FINISHLINE]->textureID = LoadTGA("Image//FinishLine.tga");

	meshList[GEO_PROPELLERFINISH] = MeshBuilder::GenerateOBJ("modelPropeller", "OBJ//PropellerFinish.obj");

	meshList[GEO_CHECKPOINT] = MeshBuilder::GenerateOBJ("modelCheckpoint", "OBJ//Checkpoint.obj");
	meshList[GEO_CHECKPOINT]->textureID = LoadTGA("Image//Checkpoint.tga");

	meshList[GEO_PROPELLERCHECKPOINT] = MeshBuilder::GenerateOBJ("modelPropeller", "OBJ//PropellerCheckpoint.obj");

	/* Gary ENUMS*/

	meshList[GEO_TRACK] = MeshBuilder::GenerateOBJ("modelTrack", "OBJ//Track.obj");
	meshList[GEO_TRACK]->textureID = LoadTGA("Image//Track.tga");

	meshList[GEO_SPEEDBUFF] = MeshBuilder::GenerateOBJ("SpeedBuff", "OBJ//Boost.obj");
	meshList[GEO_SPEEDBUFF]->textureID = LoadTGA("Image//SpeedBuffTexture.tga");

	meshList[GEO_SLOWBUFF] = MeshBuilder::GenerateOBJ("SlowBuff", "OBJ//Boost.obj");
	meshList[GEO_SLOWBUFF]->textureID = LoadTGA("Image//SlowBuffTexture.tga");
	
	meshList[GEO_DAMAGEBUFF] = MeshBuilder::GenerateOBJ("DamageBuff", "OBJ//DamageBuff.obj");
	meshList[GEO_DAMAGEBUFF]->textureID = LoadTGA("Image//DamageBuff.tga");

	meshList[GEO_REVERSEBUFF] = MeshBuilder::GenerateOBJ("DamageBuff", "OBJ//ReverseBuff.obj");
	meshList[GEO_REVERSEBUFF]->textureID = LoadTGA("Image//ReverseBuff.tga");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("Tree", "OBJ//Plant.obj");
	meshList[GEO_TREE]->textureID = LoadTGA("Image//Plant.tga");


	meshList[GEO_TESTTRACK] = MeshBuilder::GenerateOBJ("TestTrack", "OBJ//TestTrack.obj");

	//
	meshList[GEO_ROADBLOCK] = MeshBuilder::GenerateOBJ("RoadBlock", "OBJ//RoadBlock.obj");

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("Light Sphere", Color(1.f, 1.f, 1.f), 32, 36, 1.f);

	//Set projection to Perspective and load projection matrix
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, SKYBOXSIZE + 1000.f);
	projectionStack.LoadMatrix(projection);

	//Initialise variables
	healthLive = Vehicle.returnHealth();
	vehicleSpeed = 0;

	cameraPos = (Vehicle.newPosition.x, Vehicle.newPosition.y, Vehicle.newPosition.z);
	cameraTarget = (Vehicle.newPosition.x + 1, Vehicle.newPosition.y + 1, Vehicle.newPosition.z + 10);

	propellerRotation = 0;

	isWon = false;
	isLapCompleted = false;
	lapCount = 0;

	healthUpgradeLive = playerInstance->getHealthUpgradeStatus();
	speedUpgradeLive = playerInstance->getMaxSpeedUpgradeStatus();
	accelerationUpgradeLive = playerInstance->getAccelerationUpgradeStatus();
	maxAccelerationUpgradeLive = playerInstance->getMaxAccelerationUpgradeStatus();
	steerUpgradeLive = playerInstance->getSteerUpgradeStatus();
	
	displayUpgrades = true;

	timer = 137.f;
}

void SP2_TrackScene::Update(double dt)
{
	FPS = 1.f / (float)dt;

	timer -= (float)(1 * dt);

	healthUpgradeLive = playerInstance->getHealthUpgradeStatus();
	speedUpgradeLive = playerInstance->getMaxSpeedUpgradeStatus();
	accelerationUpgradeLive = playerInstance->getAccelerationUpgradeStatus();
	maxAccelerationUpgradeLive = playerInstance->getMaxAccelerationUpgradeStatus();
	steerUpgradeLive = playerInstance->getSteerUpgradeStatus();

	propellerRotation += (float)(180 * dt);

	if (bounceTime > 0) //updating bouncetime
	{
		bounceTime -= (float)(1 * dt);
	}

	healthLive = Vehicle.returnHealth();
	propellerRotation += (float)(180 * dt);

	//Timer to reset the game if the player loses
	if (healthLive <= 0 && ResetStart == true) // causes the reset timer to trigger once
	{
		ResetTimer = 4;
		ResetStart = false;
	}
	if (ResetTimer > 0) 
	{
		ResetTimer -= (float)(1 * dt);
	}
	if (ResetTimer < 0 || timer < 0)
	{
		if (DEBUG)
		{
			cout << "YOU LOST";
		}
		Application::resetScene = true;
	}

	if (Application::IsKeyPressed('M'))
	{
		music.playBGM(0);
		Application::SceneSetter = 0;
	}

	//Toggle between showing upgrades active in the UI
	if (Application::IsKeyPressed('B'))
	{
		if (bounceTime <= 0)
		{
			bounceTime = 0.3f;
			displayUpgrades = !displayUpgrades;
		}
	}

	if (playerInstance->returnChangeSomething() == true) // reload car model if something has changed.
	{
		cout << "change detected" << endl;
		meshList[GEO_KART] = MeshBuilder::GenerateOBJ("Car", playerInstance->returnKart());
		meshList[GEO_KART]->textureID = LoadTGA(playerInstance->returnColor().c_str());

		meshList[GEO_WHEELS] = MeshBuilder::GenerateOBJ("Wheels" , playerInstance->returnWheels());
		meshList[GEO_WHEELS]->textureID = LoadTGA("Image//Colors//Gray.tga");
		playerInstance->setChangeSomething(false);
	}

	//*Speedbuff logic done by Gary*/
	for (size_t i = 0; i < (SpeedBuffList.size() / 4); i++)
	{
		if (CollisionChecker(1, i, Buffs[i]->returnxPos(), Buffs[i]->returnzPos(), 1, 1) == true)
		{
			music.stopMusic();
			music.playInstantSound(0); //Sound effect made by Afiq
			SpeedBuff::timer = 1;
		}
	}
	//*SlowBuff logic done by Gary*/
	for (size_t i = (SpeedBuffList.size() / 4); i < (SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4); i++)
	{
		if (CollisionChecker(1 , i, Buffs[i]->returnxPos(), Buffs[i]->returnzPos(), 1, 1) == true)
		{
			music.stopMusic();
			music.playInstantSound(6); //Sound effect by Afiq
			SlowBuff::timer = 2;
		}
	}
	//*DamageBuff logic done by Gary*/
	for (size_t i = (SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4); i < ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4) + (DamageBuffList.size() / 4 )); i++)
	{
		if (CollisionChecker(1, i, Buffs[i]->returnxPos(), Buffs[i]->returnzPos(), 1, 1) == true)
		{
			music.playInstantSound(3); //Sound effect by Afiq
			Vehicle.setHealth(healthLive - 1);
		}
	}

	for (size_t i = ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4) + (DamageBuffList.size() / 4)); i < ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4) + (DamageBuffList.size() / 4) + (ReverseBuffList.size() / 4)); i++)
	{
		if (CollisionChecker(1, i, Buffs[i]->returnxPos(), Buffs[i]->returnzPos(), 1, 1) == true)
		{
			ReverseBuff::timer = 6;
			music.stopMusic();
			music.playInstantSound(5); //Sound effect by Afiq
			Vehicle.setInverseControls(true);
		}
	}

	float defaultSpeed;

	if (playerInstance->getMaxSpeedUpgradeStatus() == true)
	{
		defaultSpeed = 0.5f;
	}
	else
	{
		defaultSpeed = 0.4f;
	}
	
	//Timer after stepping on SpeedBuff
	if (SpeedBuff::timer > 0)
	{
		SpeedBuff::timer = SpeedBuff::timer - (float)(1 * dt);
		Vehicle.setSpeed(defaultSpeed * 1.3f);
	}

	//Timer after stepping on SlowBuff
	if (SlowBuff::timer > 0)
	{
		SlowBuff::timer = SlowBuff::timer - (float)(1 * dt);
		Vehicle.setSpeed(0.2f);
	}

	if (ReverseBuff::timer > 0)
	{
		ReverseBuff::timer = ReverseBuff::timer - (float)(1 * dt);
	}
	else
	{
		Vehicle.setInverseControls(false);
	}

	/*RoadBlock logic done by Winston*/
	for (size_t i = 0; i < BarrierList.size() / ROADBLOCKROWCOUNT; i++)
	{
		//Barriers only exist in 90 degree rotation intervals for this game
		if (Barriers[i]->returnBarrierRotation() == 90 || Barriers[i]->returnBarrierRotation() == 270)
		{
			if (CollisionChecker(2, i, Barriers[i]->returnxPos(), Barriers[i]->returnzPos(), 1.4f, 0.9f) == true)
			{
				music.stopMusic();
				music.playInstantSound(2);
				Barrier::BarrierDelay = 0.4f;
				Vehicle.setSpeed(Vehicle.returnSpeed() * (-1.f - 0.2f));
				Vehicle.setIsCollided(true);
			}
		}
		else
		{
			if (CollisionChecker(2, i, Barriers[i]->returnxPos(), Barriers[i]->returnzPos(), 0.9f, 1.4f) == true)
			{
				music.stopMusic();
				music.playInstantSound(2);
				Barrier::BarrierDelay = 0.4f;
				Vehicle.setSpeed(Vehicle.returnSpeed() * (-1.f - 0.2f));
				Vehicle.setIsCollided(true);
			}
		}
	}
	/*World border collision detection logic done by Winston*/
	if ((Vehicle.newPosition.x * Vehicle.returnCarScale()) >= (CAMERABOUNDSORIGINAL - 4.5f) || ((Vehicle.newPosition.x * Vehicle.returnCarScale()) <= -(CAMERABOUNDSORIGINAL - 4.5f)) || ((Vehicle.newPosition.z * Vehicle.returnCarScale()) >= (CAMERABOUNDSORIGINAL - 4.5f)) || ((Vehicle.newPosition.z * Vehicle.returnCarScale()) <= -(CAMERABOUNDSORIGINAL - 4.5f)))
	{
		Barrier::BarrierDelay = 0.4f;
		Vehicle.setSpeed(Vehicle.returnSpeed() * (-1.f - 0.2f));
		Vehicle.setIsCollided(true);
	}

	//Timer after colliding with road block, to prevent player from having backward controls
	if (Barrier::BarrierDelay > 0)
	{
		Barrier::BarrierDelay = Barrier::BarrierDelay - (float)(1 * dt);
	}
	else if (Barrier::BarrierDelay < 0 && Vehicle.returnIsCollided() == true)
	{
		Vehicle.setIsCollided(false);
		Vehicle.setAcceleration(0);
		Vehicle.setSpeed(0);
	}

	/*Checkpoint logic done by Winston*/
	for (size_t i = 0; i < CheckpointList.size() / CHECKPOINTROWCOUNT; i++)
	{
		if (Checkpoints[i]->returnCheckpointRotation() == 90 || Checkpoints[i]->returnCheckpointRotation() == 270)
		{
			if (CollisionChecker(4, i, Checkpoints[i]->returnxPos(), Checkpoints[i]->returnzPos(), 1.f, 4.f) == true)
			{
				if (Checkpoints[i]->returnIsPassedThrough() == false)
				{
					Checkpoints[i]->passedThroughCheckpoint();
				}
			}
		}
		else
		{
			if (CollisionChecker(4, i, Checkpoints[i]->returnxPos(), Checkpoints[i]->returnzPos(), 4.f, 1.f) == true)
			{
				if (Checkpoints[i]->returnIsPassedThrough() == false)
				{
					Checkpoints[i]->passedThroughCheckpoint();
				}
			}
		}
	}

	//Check if all checkpoints have been reached (Done by Winston)
	for (size_t i = 0; i < CheckpointList.size() / CHECKPOINTROWCOUNT; i++)
	{
		if (Checkpoints[i]->returnIsPassedThrough() == false)
		{
			isLapCompleted = false;
			break;
		}
		else
		{
			isLapCompleted = true;
		}
	}

	//Win condition done by Winston
	if (CollisionChecker(3, 1, 45, 0, 4, 1) == true)
	{
		if (isLapCompleted == true)
		{
			lapCount++;
			for (size_t i = 0; i < CheckpointList.size() / CHECKPOINTROWCOUNT; i++)
			{
				Checkpoints[i]->resetCheckpoint();
			}
			isLapCompleted = false;
		}
		if (lapCount == 3) //3 laps is needed to win the game
		{
			isWon = true;
		}
		if (isWon == true)
		{
			playerInstance->setChangeSomething(true);
			//Set car's speed to 0 at the start of the game (fixing a bug with random boost at the start of the game)
			Vehicle.setSpeed(0);
			playerInstance->setCoinCount(playerInstance->getCoinCount() + RACEREWARD);
			Application::SceneSetter = 2;
		}
	}
	if (DEBUG)
	{
		if (Application::IsKeyPressed('H'))
		{
			isWon = true;
			playerInstance->setChangeSomething(true);
		}
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

	if (!Application::IsKeyPressed(VK_SPACE))
	{
		cameraPos.x = (Vehicle.newPosition.x - sin(Math::DegreeToRadian(Vehicle.steerAngle)) * 5) * Vehicle.returnCarScale(); //Multiplied value is the camera angle, bigger number = further from car
		cameraPos.y = Vehicle.newPosition.y + 20;
		cameraPos.z = (Vehicle.newPosition.z - cos(Math::DegreeToRadian(Vehicle.steerAngle)) * 5) * Vehicle.returnCarScale();
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		cameraPos.x = (Vehicle.newPosition.x + sin(Math::DegreeToRadian(Vehicle.steerAngle)) * 5) * Vehicle.returnCarScale(); //Multiplied value is the camera angle, bigger number = further from car
		cameraPos.y = Vehicle.newPosition.y + 20;
		cameraPos.z = (Vehicle.newPosition.z + cos(Math::DegreeToRadian(Vehicle.steerAngle)) * 5) * Vehicle.returnCarScale();
	}

	cameraTarget.x = Vehicle.newPosition.x * Vehicle.returnCarScale();
	cameraTarget.y = Vehicle.newPosition.y;
	cameraTarget.z = Vehicle.newPosition.z * Vehicle.returnCarScale();

	camera.Update(dt);
	if (cameraPos.x >= CAMERABOUNDSORIGINAL)
	{
		cameraPos.x = CAMERABOUNDSORIGINAL - 1.f;
	}
	else if (cameraPos.x <= -CAMERABOUNDSORIGINAL)
	{
		cameraPos.x = -CAMERABOUNDSORIGINAL + 1.f;
	}
	else if (cameraPos.z >= CAMERABOUNDSORIGINAL)
	{
		cameraPos.z = CAMERABOUNDSORIGINAL - 1.f;
	}
	else if (cameraPos.z <= -CAMERABOUNDSORIGINAL)
	{
		cameraPos.z = -CAMERABOUNDSORIGINAL + 1.f;
	}

}

/*Original logic done by Gary, Function and code organization done by Winston*/
bool SP2_TrackScene::CollisionChecker(int type, int index, float objX, float objZ, float length, float width)
{
	float minimumXObj = objX / Vehicle.returnCarScale();
	float minimumZObj = objZ / Vehicle.returnCarScale();
	float maximumXObj = NULL;
	float maximumZObj = NULL;

	switch (type) //1 == Speedboost, 2 == Barrier, 3 == Finish Line, 4 == Checkpoint
	{
		case 1:
		{
			maximumXObj = objX / Vehicle.returnCarScale() + length;
			maximumZObj = objZ / Vehicle.returnCarScale() + width;
			break;
		}
		case 2:
		{
			maximumXObj = objX / Vehicle.returnCarScale() + length * Barriers[index]->returnBarrierScale();
			maximumZObj = objZ / Vehicle.returnCarScale() + width * Barriers[index]->returnBarrierScale();
		}
		case 3:
		{
			maximumXObj = objX / Vehicle.returnCarScale() + length;
			maximumZObj = objZ / Vehicle.returnCarScale() + width;
			break;
		}
		case 4:
		{
			maximumXObj = objX / Vehicle.returnCarScale() + length;
			maximumZObj = objZ / Vehicle.returnCarScale() + width;
			break;
		}
		default:
		{
			maximumXObj = objX / Vehicle.returnCarScale() + length;
			maximumZObj = objZ / Vehicle.returnCarScale() + width;
			break;
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
		/*cout << "Collide" << endl;*/
		return true;
	}	
}

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
		modelStack.Translate(0, CAMERABOUNDSORIGINAL, 0);
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
	//viewStack.LookAt(cameraPos.x, cameraPos.y, cameraPos.z, cameraTarget.x, cameraTarget.y, cameraTarget.z, 0, 1, 0);
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);

	modelStack.LoadIdentity();
	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (DEBUG)
	{
		//Draw Axes (For debugging purposes)
		RenderMesh(meshList[GEO_AXES], false);
	}

	//Draw Track (Modelled and rendered by Gary)
	modelStack.PushMatrix();
	{
		float trackScale = Vehicle.returnCarScale() * 2;
		modelStack.Scale(trackScale, trackScale, trackScale);
		modelStack.Translate(0, -0.49f, 0);

		RenderMesh(meshList[GEO_TRACK], true);
	}
	modelStack.PopMatrix();
	//Draw Finish Line (Modelled and rendered by Winston)
	modelStack.PushMatrix();
	{
		float finishLineScale = Vehicle.returnCarScale() * 2;
		modelStack.Translate(44.5f, 0, 0);
		modelStack.Scale(finishLineScale, finishLineScale, finishLineScale);

		RenderMesh(meshList[GEO_FINISHLINE], true);

		//Draw Propeller (Modelled and rendered by Winston)
		modelStack.PushMatrix();
		{
			modelStack.Translate(-1.15f, 3.25f, 0);
			modelStack.Rotate(propellerRotation, 0, 1, 0);
			RenderMesh(meshList[GEO_PROPELLERFINISH], true);
		}
		modelStack.PopMatrix();

		//Draw Propeller (Modelled and rendered by Winston)
		modelStack.PushMatrix();
		{
			modelStack.Translate(1.15f, 3.25f, 0);
			modelStack.Rotate(-propellerRotation, 0, 1, 0);
			RenderMesh(meshList[GEO_PROPELLERFINISH], true);
		}
		modelStack.PopMatrix();

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
		{
			RenderMesh(meshList[GEO_WHEELS], true);
		}
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	//Draw Speed buffs in the map (Modelled and rendered by Gary)
	//start from the start of the buffs
	for (size_t i = 0; i < SpeedBuffList.size() / 4; i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(Buffs[i]->returnxPos(), Buffs[i]->returnyPos(), Buffs[i]->returnzPos());
			modelStack.Scale(Vehicle.returnCarScale(), Vehicle.returnCarScale(), Vehicle.returnCarScale());
			modelStack.Rotate((float)(Buffs[i]->returnBuffRotation()), 0, 1, 0);
			RenderMesh(meshList[GEO_SPEEDBUFF], false);
		}
		modelStack.PopMatrix();
	}
	//Render slow buff. start from where speedbuff ended off at 
	for (size_t i = (SpeedBuffList.size() / 4); i < ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4)); i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(Buffs[i]->returnxPos(), Buffs[i]->returnyPos(), Buffs[i]->returnzPos());
			modelStack.Scale(Vehicle.returnCarScale(), Vehicle.returnCarScale(), Vehicle.returnCarScale());
			modelStack.Rotate((float)(Buffs[i]->returnBuffRotation()), 0, 1, 0);
			RenderMesh(meshList[GEO_SLOWBUFF], false);
		}
		modelStack.PopMatrix();
	}

	for (size_t i = ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4)); i < ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4) + (DamageBuffList.size() / 4)); i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(Buffs[i]->returnxPos(), Buffs[i]->returnyPos(), Buffs[i]->returnzPos());
			modelStack.Scale(Vehicle.returnCarScale(), Vehicle.returnCarScale(), Vehicle.returnCarScale());
			RenderMesh(meshList[GEO_DAMAGEBUFF], false);
		}
		modelStack.PopMatrix();
	}

	for (size_t i = ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4) + (DamageBuffList.size() / 4)); i < ((SpeedBuffList.size() / 4) + (SlowBuffList.size() / 4) + (DamageBuffList.size() / 4) + (ReverseBuffList.size()/4)); i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(Buffs[i]->returnxPos(), Buffs[i]->returnyPos(), Buffs[i]->returnzPos());
			modelStack.Scale(Vehicle.returnCarScale(), Vehicle.returnCarScale(), Vehicle.returnCarScale());
			RenderMesh(meshList[GEO_REVERSEBUFF], false);
		}
		modelStack.PopMatrix();
	}
	//

	//Draw Road Blocks in the map (Modelled by Zheng Hong, rendered by Winston)
	for (size_t i = 0; i < BarrierList.size() / ROADBLOCKROWCOUNT; i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(Barriers[i]->returnxPos(), Barriers[i]->returnyPos(), Barriers[i]->returnzPos());
			modelStack.Scale(Vehicle.returnCarScale() * Barriers[i]->returnBarrierScale(), Vehicle.returnCarScale() * Barriers[i]->returnBarrierScale(), Vehicle.returnCarScale() * Barriers[i]->returnBarrierScale());
			modelStack.Rotate((float)(Barriers[i]->returnBarrierRotation()), 0, 1, 0);
			RenderMesh(meshList[GEO_ROADBLOCK], true);
		}
		modelStack.PopMatrix();
	}

	//Draw Checkpoints in the map (Modelled and rendered by Winston)
	for (size_t i = 0; i < CheckpointList.size() / CHECKPOINTROWCOUNT; i++)
	{
		float checkpointScale = Vehicle.returnCarScale() * 2;
		modelStack.PushMatrix();
		{
			modelStack.Translate(Checkpoints[i]->returnxPos(), Checkpoints[i]->returnyPos(), Checkpoints[i]->returnzPos());
			modelStack.Scale(checkpointScale, checkpointScale, checkpointScale);
			modelStack.Rotate((float)(Checkpoints[i]->returnCheckpointRotation()), 0, 1, 0);
			RenderMesh(meshList[GEO_CHECKPOINT], false);

			//Draw Checkpoint Propeller (Modelled and rendered by Winston)
			modelStack.PushMatrix();
			{
				modelStack.Rotate(propellerRotation, 0, 1, 0);
				RenderMesh(meshList[GEO_PROPELLERCHECKPOINT], false);
			}
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	//Draw Skybox
	modelStack.PushMatrix();
	{
		RenderSkybox();

		//Draw UI (Logic and rendering done by Winston)
		modelStack.PushMatrix();
		{
			//FPS counter to display on the top right
			RenderTextOnScreen(meshList[GEO_TEXT], UpdateFrameRate(FPS), Color(1, 1, 0), 2, 72, 55);

			//Timer
			int displayTrackTimer = static_cast<int>(timer);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(displayTrackTimer), Color(1, 1, 0), 4, 37, 53);

			//Player Car's speed
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(vehicleSpeed), Color(1, 1, 0), 1, -1, 58);

			//Player's Position (FOR DEBUG PURPOSES)
			if (DEBUG)
			{
				int vehiclePosX = static_cast<int>(Vehicle.newPosition.x); //Convert x coordinate of the vehicle to 2 digits for display
				int vehiclePosZ = static_cast<int>(Vehicle.newPosition.z); //Convert z coordinate of the vehicle to 2 digits for display

				int cameraX = static_cast<int>(cameraPos.x); //Convert x coordinate of the camera to 2 digits for display
				int cameraY = static_cast<int>(cameraPos.y); //Convert y coordinate of the camera to 2 digits for display
				int cameraZ = static_cast<int>(cameraPos.z); //Convert z coordinate of the camera to 2 digits for display

				RenderTextOnScreen(meshList[GEO_TEXT], to_string(vehiclePosX), Color(1, 1, 0), 1, -1, 56); //Relative to orignial position, not world position
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(vehiclePosZ), Color(1, 1, 0), 1, -1, 54);

				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraX), Color(1, 0, 0), 1, -1, 52);
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraY), Color(1, 0, 0), 1, -1, 50);
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraZ), Color(1, 0, 0), 1, -1, 48);

				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraTarget.x), Color(1, 0, 0), 1, -1, 46);
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraTarget.y), Color(1, 0, 0), 1, -1, 44);
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraTarget.z), Color(1, 0, 0), 1, -1, 42);
			}

			RenderTextOnScreen(meshList[GEO_TEXT], "Health:", Color(1, 1, 1), 1, -1, 38);
			if (healthLive >= 0)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(healthLive), Color(1, 1, 1), 1, 8, 38);
			}

			RenderTextOnScreen(meshList[GEO_TEXT], "Coins:", Color(1, 1, 1), 1, -1, 36);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(playerInstance->getCoinCount()), Color(1, 1, 1), 1, 8, 36);

			RenderTextOnScreen(meshList[GEO_TEXT], "Laps:", Color(1, 1, 1), 1, -1, 34);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(lapCount), Color(1, 1, 1), 1, 8, 34);

			if (displayUpgrades == true)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Upgrades:", Color(1, 1, 1), 1, -1, 32);
				RenderTextOnScreen(meshList[GEO_TEXT], "Health Upgrade", Color(!healthUpgradeLive, healthUpgradeLive, 0), 1, -1, 30);
				RenderTextOnScreen(meshList[GEO_TEXT], "Max Speed Upgrade", Color(!speedUpgradeLive, speedUpgradeLive, 0), 1, -1, 28);
				RenderTextOnScreen(meshList[GEO_TEXT], "Acceleration Upgrade", Color(!accelerationUpgradeLive, accelerationUpgradeLive, 0), 1, -1, 26);
				RenderTextOnScreen(meshList[GEO_TEXT], "Max Acceleration Upgrade", Color(!maxAccelerationUpgradeLive, maxAccelerationUpgradeLive, 0), 1, -1, 24);
				RenderTextOnScreen(meshList[GEO_TEXT], "Steering Upgrade", Color(!steerUpgradeLive, steerUpgradeLive, 0), 1, -1, 22);
			}

			int countdown = static_cast<int>(ResetTimer);
			if (ResetTimer > 0)
			{
				//death counter
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(countdown), Color(1, 0, 0), 4, 40, 40);
			}

			if (SpeedBuff::timer > 0)
			{
				//speedBuff timer
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(SpeedBuff::timer), Color(1, 1, 0), 1, -1, 0);
			}
			if (SlowBuff::timer > 0)
			{
				//slowBuff timer
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(SlowBuff::timer), Color(1, 1, 0), 1, -1, 2);
			}
			if (ReverseBuff::timer > 0)
			{
				//reverseBuff timer
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(ReverseBuff::timer), Color(1, 1, 0), 1, -1, 4);
			}
		}
		modelStack.PopMatrix();

	}
	modelStack.PopMatrix();
}

void SP2_TrackScene::Exit()
{
	playerInstance->writeSave();
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