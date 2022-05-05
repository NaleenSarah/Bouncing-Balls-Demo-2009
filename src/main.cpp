
#include <gl/glut.h>
#include <iostream>

//#include "includes.h"
#include "app.h"

//GLfloat timeinterval = 100.0f;
int initBalls;

extern Application* getApplication();
extern Application* getApplication(int iniBalls);
Application* app;


void display(void)
{
	app->display();
}

void createWindow(const char* title, int h, int w)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(h, w);
    glutCreateWindow(title);
}

void resize(int width, int height)
{
    app->resize(width, height);
}


void TimerFunc(int value)
{
	app->update();
	float  timeinterval = app->getTimeinterval();
	glutTimerFunc(timeinterval, TimerFunc, 1);
}


int main(int argc, char* argv[])
{
	LPCSTR Name = (LPCSTR)"Sphere 2D Collision";
	glutInit(&argc, argv);

	std::cout << "How Many Balls? (Max 500)\nWorks best with 2 - 4 Obj's: ";
	std::cin >> initBalls;
	if(initBalls >= 1000)
		initBalls = 1000;

	app = getApplication(initBalls);
	float  timeinterval = 10;
	app->setTimeinterval(timeinterval);
	createWindow("Sphere 2D Collision", app->getHeight(), app->getWidth());
	
	glutReshapeFunc(resize);
	glutDisplayFunc(display); 
	glutTimerFunc(timeinterval, TimerFunc, 1);
	
	app->initGraphics();
	glutMainLoop();

	delete app; 	
	return 0;
}