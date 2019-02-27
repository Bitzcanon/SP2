#include "SP2_MainMenuScene.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"

SP2_MainMenuScene::SP2_MainMenuScene()
{
	playerInstance = Player::getInstance();
}

SP2_MainMenuScene::~SP2_MainMenuScene()
{

}

void SP2_MainMenuScene::Init()
{
	bounceTime = 0;
	arrowY = 0.2;
	isMenu = true;
	isInstructions = false;
	rotateAngle = 0;

	for (int i = 0; i < 4; i++)
	{
		transition[i] = false;
	}
	
	transitionTime = 0;

	tmpx = 0;
	tmpy = 0;
	tmpz = 0;

	tmpAngle = 25;
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

	//Initialise initial Camera position x y z target up
	camera.Init(Vector3(0, 20, 240), Vector3(0, 20, 0), Vector3(0, 1, 0)); //For MainMenu Camera
	//camera.Init(Vector3(0, 20, 120)); //For FPS Camera (Only for NPCScene, testing in TrackScene

	//Light parameters
	//Lower floor lighting
	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 60, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 10.f;
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

	meshList[GEO_MENU] = MeshBuilder::GenerateOBJ("Menu", "OBJ//Quad.obj");
	meshList[GEO_MENU]->textureID = LoadTGA("Image//MainMenu.tga");

	meshList[GEO_TITLE] = MeshBuilder::GenerateOBJ("Title", "OBJ//Quad.obj");
	meshList[GEO_TITLE]->textureID = LoadTGA("Image//Title1.tga");

	meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("Model1", "OBJ//Kart2.obj");
	meshList[GEO_MODEL1]->textureID = LoadTGA("Image//Colors//Blue.tga");

	meshList[GEO_WHEELS] = MeshBuilder::GenerateOBJ("Model1", "OBJ//Wheels1.obj");
	meshList[GEO_WHEELS]->textureID = LoadTGA("Image//Colors//Gray.tga");

	meshList[GEO_ARROW] = MeshBuilder::GenerateOBJ("Arrow", "OBJ//Arrow.obj");

	meshList[GEO_BACKGROUND] = MeshBuilder::GenerateOBJ("Background", "OBJ//Quad.obj");
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Colors//Black.tga");

	meshList[GEO_TITLEBACKGROUND] = MeshBuilder::GenerateOBJ("Title Background", "OBJ//Quad.obj");
	meshList[GEO_TITLEBACKGROUND]->textureID = LoadTGA("Image//Colors//White.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("Light Sphere", Color(1.f, 1.f, 1.f), 32, 36, 1.f);

	//Set projection to Perspective and load projection matrix
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 500.f);
	projectionStack.LoadMatrix(projection);

	bgm.playBGM(0);
}

void SP2_MainMenuScene::Update(double dt)
{
	FPS = 1.f / (float)dt;
	if (rotateAngle < 360)
	{
		rotateAngle += (float)(20 * dt);
	}
	else 
	{
		rotateAngle = 0;
	}
	if (transitionTime < 8)
	{
		transitionTime += (float)(1 * dt);
	}

	if (transitionTime < 7.5f)
	{
		if (transitionTime < 2 && transition[0] == false)
		{
			transition[0] = true;
			meshList[GEO_TITLE]->textureID = LoadTGA("Image//Title1.tga");
		}
		if (transitionTime < 4 && transitionTime > 2 && transition[1] == false)
		{
			transition[1] = true;
			meshList[GEO_TITLE]->textureID = LoadTGA("Image//Title2.tga");
		}
		if (transitionTime < 5.5f && transitionTime > 4 && transition[2] == false)
		{
			transition[2] = true;
			meshList[GEO_TITLE]->textureID = LoadTGA("Image//Title4.tga");
		}
		if (transitionTime < 7 && transitionTime > 5.5f && transition[3] == false)
		{
			transition[2] = true;
			meshList[GEO_TITLE]->textureID = LoadTGA("Image//Title3.tga");
		}
	}
	else if (camera.position.z > 120)
	{
		camera.position.z -= (float)(100 * dt);
	}

	if (transitionTime > 8)
	{
		if (Application::IsKeyPressed(VK_UP))
		{
			tmpy += (float)(1 * dt);
		}
		else if (Application::IsKeyPressed(VK_LEFT))
		{
			tmpz -= (float)(1 * dt);
		}
		else if (Application::IsKeyPressed(VK_DOWN))
		{
			tmpy -= (float)(1 * dt);
		}
		else if (Application::IsKeyPressed(VK_RIGHT))
		{
			tmpz += (float)(1 * dt);
		}

		if (Application::IsKeyPressed(VK_RETURN))
		{
			
			if (bounceTime <= 0)
			{
				bounceTime = 0.2f;
				
				if (isInstructions == true)
				{
					meshList[GEO_MENU]->textureID = LoadTGA("Image//MainMenu.tga");
					isInstructions = false;
					isMenu = true;
					arrowY = 0.2;
				}
				else if (isInstructions == false)
				{
					if (isMenu == true) // if player is at the menu ,
					{
						if (arrowY == 0.2)
						{
							sceneNumber = 1;
							meshList[GEO_MENU]->textureID = LoadTGA("Image//ConfirmMenu.tga");
							arrowY = 0.1;
							isMenu = false;
						}
						else if (arrowY == 0.1)
						{
							meshList[GEO_MENU]->textureID = LoadTGA("Image//Controls.tga");
							arrowY = 1;
							isMenu = false;
							isInstructions = true;
						}
						else if (arrowY == 0)
						{
							playerInstance->resetSaveFile();
						}
						else if (arrowY == -0.1)
						{
							bgm.stopMusic();
							Application::SceneSetter = 4;
						}
						else if (arrowY == -0.2)
						{
							Application::SceneSetter = 10;
						}
					}
					else if (isMenu == false && isInstructions == false)
					{
						if (arrowY == 0.1)
						{
							bgm.stopMusic();
							Application::SceneSetter = sceneNumber;
							Application::resetScene = false;
						}
						else if (arrowY == 0)
						{
							bgm.stopMusic(); 
							Application::SceneSetter = sceneNumber;
							Application::resetScene = true;
						}
						else if (arrowY == -0.1)
						{
							meshList[GEO_MENU]->textureID = LoadTGA("Image//MainMenu.tga");
							isMenu = true;
						}
					}
				}
			}
		}

		if (Application::IsKeyPressed(VK_UP))
		{
			if (isInstructions == false)
			{
				if (isMenu == true)
				{
					if (bounceTime <= 0)
					{
						bounceTime = 0.1f;
						arrowY += 0.1;
						if (arrowY > 0.3)
						{
							arrowY = -0.2;
						}
					}
				}
				else if (isMenu == false)
				{
					if (bounceTime <= 0)
					{
						bounceTime = 0.1f;
						arrowY += 0.1;
						if (arrowY > 0.1)
						{
							arrowY = -0.1;
						}
					}
				}
			}
		}

		if (Application::IsKeyPressed(VK_DOWN))
		{
			if (isInstructions == false)
			{
				if (isMenu == true)
				{
					if (bounceTime <= 0)
					{
						bounceTime = 0.1f;
						arrowY -= 0.1;
						if (arrowY < -0.3)
						{
							arrowY = 0.2;
						}
					}
				}
				else if (isMenu == false)
				{
					if (bounceTime <= 0)
					{
						bounceTime = 0.1f;
						arrowY -= 0.1;
						if (arrowY < -0.1)
						{
							arrowY = 0.1;
						}
					}
				}
			}
		}
	}
	if (bounceTime > 0)
	{
		bounceTime -= (float)(1 * dt);
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

	camera.Update(dt);
}

static const float SKYBOXSIZE = 1000.f;

/*FPS counter done by Winston*/
string SP2_MainMenuScene::UpdateFrameRate(float fps)
{
	int IntFPS = static_cast<int>(fps); //Convert FPS to 2 digits for display
	string fpsCount = to_string(IntFPS);

	return fpsCount;
}

void SP2_MainMenuScene::RenderMesh(Mesh *mesh, bool enableLight) //Pass in mesh name to go through this to enable lighting for that mesh
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

void SP2_MainMenuScene::RenderText(Mesh* mesh, std::string text, Color color)
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

void SP2_MainMenuScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SP2_MainMenuScene::Render()
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
	if (DEBUG)
	{
		RenderMesh(meshList[GEO_AXES], false);
	}

	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 20, -200);
		modelStack.Scale(500, 500, 500);
		RenderMesh(meshList[GEO_BACKGROUND], false);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 20, -40);
		modelStack.Scale(100, 100, 100);
		RenderMesh(meshList[GEO_MENU], false);

		modelStack.PushMatrix();
		{
			modelStack.Translate(0.5f, 0, 0.2f);
			modelStack.Rotate(10, 1, 0, 0);
			modelStack.Rotate(rotateAngle, 0, 1, 0);
			modelStack.Scale(0.2f, 0.2f, 0.2f);
			RenderMesh(meshList[GEO_MODEL1], true); //set lighting to true once completed

			modelStack.PushMatrix();
			{
				RenderMesh(meshList[GEO_WHEELS], true); //set lighting to true once completed
			}
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		{
			modelStack.Translate(-0.38f, (float)(arrowY), 0.1f);
			modelStack.Scale(0.05f, 0.05f, 0.05f);
			modelStack.Rotate(270, 0, 1, 0);
			RenderMesh(meshList[GEO_ARROW], false);
		}
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 20, 119.9f);
		modelStack.Scale(300, 300, 10);
		RenderMesh(meshList[GEO_TITLEBACKGROUND], false);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	{
		modelStack.Translate(0, 20, 120);
		modelStack.Scale(100, 100, 100);
		RenderMesh(meshList[GEO_TITLE], false);
	}
	modelStack.PopMatrix();
}

void SP2_MainMenuScene::Exit()
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