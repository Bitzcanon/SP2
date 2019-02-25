#include "SP2_CoinCollectionScene.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"

SP2_CoinCollectionScene::SP2_CoinCollectionScene()
{
	playerInstance = Player::getInstance();
}

SP2_CoinCollectionScene::~SP2_CoinCollectionScene()
{

}

void SP2_CoinCollectionScene::loadBarrierCoordinates()
{
	ifstream myfile("TextFiles//MazeTileCoordinates.txt"); //File directory

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

void SP2_CoinCollectionScene::initBarrier()
{
	for (int i = 0; i < MAZETILECOUNT; i++) //Init array container to NULL
	{
		Barriers[i] = NULL;
	}

	for (size_t i = 0; i < (BarrierList.size() / MAZETILEROWCOUNT); i++)
	{
		Barriers[i] = new Barrier;
	}

	int counter = 1;
	for (size_t i = 0; i < BarrierList.size(); i++) // loop through the total cords in the text file
	{
		int loc = i / MAZETILEROWCOUNT;
		// i = 0 , loc = 0 . i = 1 , loc = 0 , i = 2 , loc = 0 , i = 3 , loc = 0 
		// i = 4 , loc = 0 , i = 5 , loc = 1 , i = 6 , loc = 1 , i = 7 , loc = 1

		if (counter == 3) // 
		{
			Barriers[loc]->setzPos(BarrierList[i]);
			counter = 1;
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

void SP2_CoinCollectionScene::Init()
{
	//Loads Barrier coordinates
	loadBarrierCoordinates();
	initBarrier();

	timer = 30;

	bounceTime = 0;

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
	camera.Init(Vector3(0, 20, 1), Vector3(0, 20, 0), Vector3(0, 1, 0));

	//Light parameters
	//Lower floor lighting
	light[0].type = Light::LIGHT_SPOT;
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

	glUniform1i(m_parameters[U_NUMLIGHTS], 1); //This value is the number of lights in the scene

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

	//remove later
	meshList[GEO_TESTCAR] = MeshBuilder::GenerateCube("Car", Color(0, 1, 0), 5, 1, 1);

	//Default init for kart
	meshList[GEO_KART] = MeshBuilder::GenerateOBJ("Car", playerInstance->returnKart());
	meshList[GEO_KART]->textureID = LoadTGA(playerInstance->returnColor().c_str());

	meshList[GEO_WHEELS] = MeshBuilder::GenerateOBJ("Car", playerInstance->returnWheels());
	meshList[GEO_WHEELS]->textureID = LoadTGA("Image//Colors//Gray.tga");

	//Default init for kart
	meshList[GEO_ROADBLOCK] = MeshBuilder::GenerateOBJ("RoadBlock", "OBJ//RoadBlock.obj");
	meshList[GEO_MAZETILE] = MeshBuilder::GenerateOBJ("MazeTile", "OBJ//MazeTile.obj");

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);


	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("Light Sphere", Color(1.f, 1.f, 1.f), 32, 36, 1.f);

	meshList[GEO_COINS] = MeshBuilder::GenerateOBJ("coin", "OBJ//Coin.obj");
	meshList[GEO_COINS]->textureID = LoadTGA("Image//PlaceholderCoinTexture.tga");

	//Set projection to Perspective and load projection matrix
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
	projectionStack.LoadMatrix(projection);

	//Initialise variables
	vehicleSpeed = 0;

	cameraPos = (Vehicle.newPosition.x, Vehicle.newPosition.y, Vehicle.newPosition.z);
	cameraTarget = (Vehicle.newPosition.x + 1, Vehicle.newPosition.y + 1, Vehicle.newPosition.z + 10);

	isWon = false;
	displayUpgrades = true;
	coinappeared = false;
	initCoins();

	coinrotation = 0.f; coinup = 0.f;
	goingup = false;

	healthUpgradeLive = playerInstance->getHealthUpgradeStatus();
	speedUpgradeLive = playerInstance->getMaxSpeedUpgradeStatus();
	accelerationUpgradeLive = playerInstance->getAccelerationUpgradeStatus();
	maxAccelerationUpgradeLive = playerInstance->getMaxAccelerationUpgradeStatus();
	steerUpgradeLive = playerInstance->getSteerUpgradeStatus();
}

void SP2_CoinCollectionScene::initCoins()
{
	coin[0].SetCoinCoords(150.f, 175.f);
	coin[1].SetCoinCoords(150.f, -175.f);	
	coin[2].SetCoinCoords(150.f, 25.f);	
	coin[3].SetCoinCoords(150.f, -75.f);
	coin[4].SetCoinCoords(150.f, -125.f);
	coin[5].SetCoinCoords(50.f, -25.f);	
	coin[6].SetCoinCoords(-150.f, -75.f);
	coin[7].SetCoinCoords(50.f, 175.f);
	coin[8].SetCoinCoords(150.f, 125.f);	
	coin[9].SetCoinCoords(50.f, 75.f);
	coin[10].SetCoinCoords(50.f, 25.f);
	coin[11].SetCoinCoords(-50.f, 175.f);	
	coin[12].SetCoinCoords(50.f, -125.f);
	coin[13].SetCoinCoords(50.f, -175.f);
	coin[14].SetCoinCoords(-50.f, -125.f);	
	coin[15].SetCoinCoords(-50.f, -25.f);	
	coin[16].SetCoinCoords(-50.f, 125.f);
	coin[17].SetCoinCoords(-150.f, 75.f);	
	coin[18].SetCoinCoords(50.f, 125.f);	
	coin[19].SetCoinCoords(-50.f, 25.f);
	coin[20].SetCoinCoords(-150.f, -25.f);	
	coin[21].SetCoinCoords(150.f, 75.f);	
	coin[22].SetCoinCoords(-150.f, -175.f);
	coin[23].SetCoinCoords(-50.f, -75.f);
	coin[24].SetCoinCoords(150.f, -25.f);		
	coin[25].SetCoinCoords(-150.f, 175.f);	
	coin[26].SetCoinCoords(-150.f, 125.f);	
	coin[27].SetCoinCoords(-50.f, 75.f);	
	coin[28].SetCoinCoords(-150.f, 25.f);
	coin[29].SetCoinCoords(50.f, -75.f);
	coin[30].SetCoinCoords(-150.f, -125.f);
	coin[31].SetCoinCoords(-50.f, -175.f);
}

int SP2_CoinCollectionScene::countCoins()
{
	int count = 0;
	for (int i = 0; i < 32; i++)
	{
		if (coin[i].CheckTaken())
		{
			count++;
		}
	}
	return count;
}


void SP2_CoinCollectionScene::Update(double dt)
{
	FPS = 1.f / (float)dt;
	
	timer -= (float)(1 * dt);

	if (timer <= 0)
	{
		sounds.playBGM(0);
		Application::SceneSetter = 3;
	}

	playerInstance->setCoinsEarned(countCoins());

	if (bounceTime > 0) //updating bouncetime
	{
		bounceTime -= (float)(1 * dt);
	}

	healthUpgradeLive = playerInstance->getHealthUpgradeStatus();
	speedUpgradeLive = playerInstance->getMaxSpeedUpgradeStatus();
	accelerationUpgradeLive = playerInstance->getAccelerationUpgradeStatus();
	maxAccelerationUpgradeLive = playerInstance->getMaxAccelerationUpgradeStatus();
	steerUpgradeLive = playerInstance->getSteerUpgradeStatus();

	if (playerInstance->returnChangeSomething() == true) // reload car model if something has changed.
	{
		cout << "something changed " << endl;
		meshList[GEO_KART] = MeshBuilder::GenerateOBJ("Car", playerInstance->returnKart());
		meshList[GEO_KART]->textureID = LoadTGA(playerInstance->returnColor().c_str());

		meshList[GEO_WHEELS] = MeshBuilder::GenerateOBJ("Wheels", playerInstance->returnWheels());
		meshList[GEO_WHEELS]->textureID = LoadTGA("Image//Colors//Gray.tga");
		playerInstance->setChangeSomething(false);
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

	/*Maze Tile logic done by Winston*/
	for (size_t i = 0; i < BarrierList.size() / MAZETILEROWCOUNT; i++)
	{
		if (CollisionChecker(1, i, Barriers[i]->returnxPos(), Barriers[i]->returnzPos(), 1.9f, 1.9f) == true)
		{
			sounds.playInstantSound(2); //Added by Afiq. For sound when car crashes into barrier
			Barrier::BarrierDelay = 0.2f;
			Vehicle.setSpeed(Vehicle.returnSpeed() * (-1.f - 0.2f));
			Vehicle.setIsCollided(true);
		}
	}
	/*World border collision detection logic done by Winston*/
	if (((Vehicle.newPosition.x * (Vehicle.returnCarScale() / 4)) >= (CAMERABOUNDSCHASE - 4.5f)) || ((Vehicle.newPosition.x * (Vehicle.returnCarScale() / 4)) <= -(CAMERABOUNDSCHASE - 4.5f)) || ((Vehicle.newPosition.z * (Vehicle.returnCarScale() / 4)) >= (CAMERABOUNDSCHASE - 4.5f)) || ((Vehicle.newPosition.z * (Vehicle.returnCarScale() / 4)) <= -(CAMERABOUNDSCHASE - 4.5f)))
	{
		Barrier::BarrierDelay = 0.2f;
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
		cameraPos.x = (Vehicle.newPosition.x - sin(Math::DegreeToRadian(Vehicle.steerAngle)) * 6) * (Vehicle.returnCarScale() / 4);
		cameraPos.y = Vehicle.newPosition.y + 10;
		cameraPos.z = (Vehicle.newPosition.z - cos(Math::DegreeToRadian(Vehicle.steerAngle)) * 6) * (Vehicle.returnCarScale() / 4);
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		cameraPos.x = (Vehicle.newPosition.x + sin(Math::DegreeToRadian(Vehicle.steerAngle)) * 6) * (Vehicle.returnCarScale() / 4);
		cameraPos.y = Vehicle.newPosition.y + 10;
		cameraPos.z = (Vehicle.newPosition.z + cos(Math::DegreeToRadian(Vehicle.steerAngle)) * 6) * (Vehicle.returnCarScale() / 4);
	}

	cameraTarget.x = Vehicle.newPosition.x * (Vehicle.returnCarScale() / 4);
	cameraTarget.y = Vehicle.newPosition.y;
	cameraTarget.z = Vehicle.newPosition.z * (Vehicle.returnCarScale() / 4);

	camera.Update(dt);
	if (cameraPos.x >= CAMERABOUNDSCHASE)
	{
		cameraPos.x = CAMERABOUNDSCHASE - 1.f;
	}
	else if (cameraPos.x <= -CAMERABOUNDSCHASE)
	{
		cameraPos.x = -CAMERABOUNDSCHASE + 1.f;
	}
	else if (cameraPos.z >= CAMERABOUNDSCHASE)
	{
		cameraPos.z = CAMERABOUNDSCHASE - 1.f;
	}
	else if (cameraPos.z <= -CAMERABOUNDSCHASE)
	{
		cameraPos.z = -CAMERABOUNDSCHASE + 1.f;
	}

	for (int i = 0; i < 32; i++)
	{
		if (coin[i].hasAppeared() && !coin[i].CheckTaken())
		{
			coin[i].CoinCollision(Vehicle.newPosition.x * (Vehicle.returnCarScale() / 4), Vehicle.newPosition.z * (Vehicle.returnCarScale() / 4));
		}
	}

	for (int i = 0; i < 32; i++)
	{
		if (coin[i].hasAppeared() && !coin[i].CheckTaken())
		{
			break;
		}
		if (!coin[i].CheckTaken() && !coin[i].hasAppeared())
		{
			coin[i].appears();
			break;
		}
	}

	coinrotation += (float)dt * 40.f;
	if (goingup && coinup < 2.f)
	{
		coinup += (float)dt * 1.f;
	}
	else if (goingup && coinup >= 2.f)
	{
		goingup = false;
	}
	if (!goingup && coinup > 0.f)
	{
		coinup -= (float)dt * 2.f;
	}
	else if (!goingup && coinup <= 0.f)
	{
		goingup = true;
	}
}

/*Original logic done by Gary, Function and code organization done by Winston*/
bool SP2_CoinCollectionScene::CollisionChecker(int type, int index, float objX, float objZ, float length, float width)
{
	float minimumXObj = objX / (Vehicle.returnCarScale() / 4);
	float minimumZObj = objZ / (Vehicle.returnCarScale() / 4);
	float maximumXObj = NULL;
	float maximumZObj = NULL;

	switch (type) //1 == MazeTile
	{
	case 1:
	{
		maximumXObj = objX / (Vehicle.returnCarScale() / 4) + length;
		maximumZObj = objZ / (Vehicle.returnCarScale() / 4) + width;
		break;
	}
	default:
	{
		maximumXObj = objX / (Vehicle.returnCarScale() / 4) + length;
		maximumZObj = objZ / (Vehicle.returnCarScale() / 4) + width;
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
		if (DEBUG)
		{
			cout << "Collide" << endl;
		}
		return true;
	}
}

static const float SKYBOXSIZE = 500.f;

/*FPS counter done by Winston*/
string SP2_CoinCollectionScene::UpdateFrameRate(float fps)
{
	int IntFPS = static_cast<int>(fps); //Convert FPS to 2 digits for display
	string fpsCount = to_string(IntFPS);

	return fpsCount;
}

void SP2_CoinCollectionScene::RenderMesh(Mesh *mesh, bool enableLight) //Pass in mesh name to go through this to enable lighting for that mesh
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

void SP2_CoinCollectionScene::RenderText(Mesh* mesh, std::string text, Color color)
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

void SP2_CoinCollectionScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SP2_CoinCollectionScene::RenderSkybox()
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
		modelStack.Translate(0, CAMERABOUNDSCHASE, 0);
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
		RenderMesh(meshList[GEO_BOTTOM], false);
	}
	modelStack.PopMatrix();
	//Bottom of Skybox
}

void SP2_CoinCollectionScene::Render()
{
	//Clear color & depth buffer every time
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Define the view/ camera lookat and load the view matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(cameraPos.x, cameraPos.y, cameraPos.z, cameraTarget.x, cameraTarget.y, cameraTarget.z, 0, 1, 0);

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

	//Draw Axes (For debugging purposes)
	RenderMesh(meshList[GEO_AXES], false);

	//Draw Test Car (Modelled by Gary, rendered by Winston)
	modelStack.PushMatrix();
	{
		modelStack.Scale(Vehicle.returnCarScale() / 4, Vehicle.returnCarScale() / 4, Vehicle.returnCarScale() / 4);

		modelStack.Translate(Vehicle.newPosition.x, Vehicle.newPosition.y, Vehicle.newPosition.z);
		modelStack.Rotate(Vehicle.steerAngle, 0, 1, 0);

		RenderMesh(meshList[GEO_KART], true);

		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_WHEELS], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	//Draw Maze Tiles in the map (Modelled and rendered by Winston)
	for (size_t i = 0; i < BarrierList.size() / MAZETILEROWCOUNT; i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(Barriers[i]->returnxPos(), Barriers[i]->returnyPos(), Barriers[i]->returnzPos());
			modelStack.Scale(Vehicle.returnCarScale() / 4, Vehicle.returnCarScale() / 4, Vehicle.returnCarScale() / 4);
			RenderMesh(meshList[GEO_MAZETILE], true);
		}
		modelStack.PopMatrix();
	}

	//Draw coins in the map (Stuff by Afiq)
	for (int i = 0; i < 32; i++)
	{
		if (!coin[i].CheckTaken() && coin[i].hasAppeared())
		{
			modelStack.PushMatrix();
			{
				modelStack.Translate(coin[i].getX(), coinup, coin[i].getZ());
				modelStack.Scale(5.f, 5.f, 5.f);
				modelStack.Rotate(coinrotation, 0.f, 1.0f, 0.f);
				RenderMesh(meshList[GEO_COINS], true);
			}
			modelStack.PopMatrix();
		}
	}

	//Draw Skybox
	modelStack.PushMatrix();
	{
		RenderSkybox();

		//Draw UI (Logic and rendering done by Winston)
		modelStack.PushMatrix();
		{
			RenderTextOnScreen(meshList[GEO_TEXT], UpdateFrameRate(FPS), Color(1, 1, 0), 2, 72, 55);

			if (DEBUG)
			{
				//Player's Position (FOR DEBUG PURPOSES)
				int vehiclePosX = static_cast<int>(Vehicle.newPosition.x); //Convert x coordinate of the vehicle to 2 digits for display
				int vehiclePosZ = static_cast<int>(Vehicle.newPosition.z); //Convert z coordinate of the vehicle to 2 digits for display

				int cameraX = static_cast<int>(cameraPos.x); //Convert x coordinate of the camera to 2 digits for display
				int cameraY = static_cast<int>(cameraPos.y); //Convert y coordinate of the camera to 2 digits for display
				int cameraZ = static_cast<int>(cameraPos.z); //Convert z coordinate of the camera to 2 digits for display

				RenderTextOnScreen(meshList[GEO_TEXT], to_string(vehicleSpeed), Color(1, 1, 0), 1, -1, 58);
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(vehiclePosX), Color(1, 1, 0), 1, -1, 56);
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(vehiclePosZ), Color(1, 1, 0), 1, -1, 54);

				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraX), Color(1, 0, 0), 1, -1, 52);
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraY), Color(1, 0, 0), 1, -1, 50);
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraZ), Color(1, 0, 0), 1, -1, 48);

				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraTarget.x), Color(1, 0, 0), 1, -1, 46);
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraTarget.y), Color(1, 0, 0), 1, -1, 44);
				RenderTextOnScreen(meshList[GEO_TEXT], to_string(cameraTarget.z), Color(1, 0, 0), 1, -1, 42);

			}

			RenderTextOnScreen(meshList[GEO_TEXT], "Coins:", Color(1, 1, 1), 1, -1, 36);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(playerInstance->getCoinCount()), Color(1, 1, 1), 1, 8, 36);

			RenderTextOnScreen(meshList[GEO_TEXT], "Coins Collected:", Color(1, 1, 1), 1, -1, 38);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string(countCoins()), Color(1, 1, 1), 1, 15, 38);

			RenderTextOnScreen(meshList[GEO_TEXT], to_string((int)timer), Color(1, 1, 0), 4, 37, 53);

			if (displayUpgrades == true)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Upgrades:", Color(1, 1, 1), 1, -1, 32);
				RenderTextOnScreen(meshList[GEO_TEXT], "Health Upgrade", Color(!healthUpgradeLive, healthUpgradeLive, 0), 1, -1, 30);
				RenderTextOnScreen(meshList[GEO_TEXT], "Max Speed Upgrade", Color(!speedUpgradeLive, speedUpgradeLive, 0), 1, -1, 28);
				RenderTextOnScreen(meshList[GEO_TEXT], "Acceleration Upgrade", Color(!accelerationUpgradeLive, accelerationUpgradeLive, 0), 1, -1, 26);
				RenderTextOnScreen(meshList[GEO_TEXT], "Max Acceleration Upgrade", Color(!maxAccelerationUpgradeLive, maxAccelerationUpgradeLive, 0), 1, -1, 24);
				RenderTextOnScreen(meshList[GEO_TEXT], "Steering Upgrade", Color(!steerUpgradeLive, steerUpgradeLive, 0), 1, -1, 22);
			}
		}
		modelStack.PopMatrix();

	}
	modelStack.PopMatrix();
}

void SP2_CoinCollectionScene::Exit()
{
	playerInstance->setCoinCount(playerInstance->getCoinCount() + countCoins());
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