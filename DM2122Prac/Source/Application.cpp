#include "Application.h"
#include "SP2_MainMenuScene.h"

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SP2_TrackScene.h"
#include "SP2_NPCScene.h"
#include "SP2_ChaseEnemyScene.h"

//Framework prepared by Winston

int::Application::SceneSetter = 0 ;
bool::Application::resetScene = false;

Application::Application()
{
}

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

double Application::mouse_x = 0;
double Application::mouse_y = 0;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Application::mouse_x = xpos;
	Application::mouse_y = ypos;
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0); 
}



Application::~Application()
{
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(800, 600, "Computer Graphics", NULL, NULL);

	//Register callback for window size (New to Scene 2)
	glfwSetWindowSizeCallback(m_window, resize_callback);

	//Captures the cursor in the window and take its input
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(m_window, mouse_callback);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}


void Application::Run()
{
	//Main Loop
	Scene *scene[5];
	//INIT TO NULL
	for (int i = 0; i < 5; i++)
	{
		scene[i] = NULL;
	}

	scene[0] = new SP2_MainMenuScene();

	scene[1] = new SP2_TrackScene();
	scene[2] = new SP2_ChaseEnemyScene();
	/*scene[3] = new SP2_SurvivalScene();*/
	scene[4] = new SP2_NPCScene();

	for (int i = 0; i < 5; i++)
	{
		if (scene[i] != NULL)
		{
			scene[i]->Init();
		}
	}

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame

	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		scene[SceneSetter]->Update(m_timer.getElapsedTime());

		if ((SceneSetter == 1 || SceneSetter == 2) /*|| SceneSetter == 3*/ && resetScene == true) // reset the track everytime u enter from main menu
		{
			int i = SceneSetter;
			scene[i]->Exit();
			delete scene[i];
			if (i == 1)
			{
				scene[1] = new SP2_TrackScene;
				scene[1]->Init();
			}
			else if (i == 2)
			{
				scene[2] = new SP2_ChaseEnemyScene;
				scene[2]->Init();
			}
			/*else if (i == 3)
			{
				scene[3] = new SP2_SurvivalScene;
				scene[3]->Init();
			}*/
			resetScene = false;
		}
		else if (SceneSetter == 10) // ENSURE THIS IS BEFORE RENDER SO IT WONT OVERLOAD RENDER
		{
			break;
		}

		scene[SceneSetter]->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
		m_timer.waitUntil(frameTime);// Frame rate limiter. Limits each frame to a specified time in ms. 
	}

	for (int i = 0; i < 5; i++)
	{
		if (scene[i] != NULL)
		{
			scene[i]->Exit();
			delete scene[i];
		}
	}
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
