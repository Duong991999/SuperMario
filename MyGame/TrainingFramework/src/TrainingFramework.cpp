#include "targetver.h"
#include "Shaders.h"
#include "Application.h"
#include "utilities.h" 
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

GLint screenWidth = 720;
GLint screenHeight = 480;
GLint xSpeed = 0;
GLint ySpeed = 100;
GLint gravity = 13;
GLint score = 0;
//GLint vantoc = 300;

GLint highScore[3];


void LoadHighScore()
{
	printf("load \n");
	fstream f;
	f.open("highscore.txt", ios::in);

	string data;
	int i = 0;
	string line;
	while (!f.eof())         
	{
		getline(f, line); 
		data += line + " ";
	}

	f.close();
	while (data.find(" "))
	{
		highScore[i++] = std::stoi(data.substr(0, data.find(" ")));
		data = data.substr(data.find(" ") + 1, data.length());
	}

	for (int i = 0; i < 3; i++)
	{
		printf("%d ", highScore[i]);
	}
}
GLint Init(ESContext* esContext)
{
	Application::GetInstance()->Init();
	return 0;
}

void Draw(ESContext* esContext)
{
	Application::GetInstance()->Render();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, GLfloat deltaTime)
{
	Application::GetInstance()->Update(deltaTime);
}

void Key(ESContext* esContext, unsigned char key, bool bbIsPresseded)
{
	Application::GetInstance()->HandleKeyEvent(key, bbIsPresseded);
}

void Mouse(ESContext* esContext, GLint x, GLint y, bool bbIsPresseded)
{
	Application::GetInstance()->HandleTouchEvent(x, y, bbIsPresseded);
}

void CleanUp()
{
	Application::GetInstance()->Exit();
	Application::FreeInstance();
}

GLint _tmain(GLint argc, _TCHAR* argv[])
{

	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "Demo Game", screenWidth, screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
	esRegisterMouseFunc(&esContext, Mouse);
	esMainLoop(&esContext);


	CleanUp();


	MemoryDump();


	return 0;
}

