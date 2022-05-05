
#include <gl/glut.h>

#include "app.h"
Application::Application() {
	this->height = 0;
	this->nRange = 0;
	this->width = 0;
}

void Application::initGraphics()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f );	
}


void Application::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Application::resize(int width, int height)
{
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;

    // Prevent a divide by zero
    if(height == 0) height = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, width, height);

	// Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

     //Establish clipping volume (left, right, bottom, top, near, far)
    if (width <= height) 
	{
	Application::width = nRange;
    Application::height = nRange/aspectRatio;
		glOrtho ((double)-nRange, (double)nRange, (double)-nRange/aspectRatio, (double)nRange/aspectRatio, (double)-nRange*2.0, (double)nRange*2.0);
	}
    else 
	{
	Application::width = nRange*aspectRatio;
    Application::height = nRange;
    glOrtho ((double)-nRange*aspectRatio, (double)nRange*aspectRatio, -nRange, nRange, (double)-nRange*2.0, (double)nRange*2.0);
	}

	// Reset the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

}

int Application::getHeight(void)
{
	return this->height;
}

int Application::getWidth(void)
{
	return this->width;
}

void Application::update()
{
	glutPostRedisplay();
}

float Application::getTimeinterval()
{
    return timeinterval;
}

void Application::setTimeinterval(float timeinterval)
{
    Application::timeinterval = timeinterval;
}