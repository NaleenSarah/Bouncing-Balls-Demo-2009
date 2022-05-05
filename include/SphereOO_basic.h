//#include <gl/glut.h>// OpenGL toolkit
//#include <math.h>//mathematics library
#include "includes.h"
#include "app.h"// OpenGL toolkit
//#include "particle.h"





class SphereDemo : public Application
{
public:
	SphereDemo();
	SphereDemo(int iniBalls);
    virtual void display();
	virtual void sphereUpdate();
	particle Ball[MAX_Balls];
	float EuclidD(float x1, float x2, float y1, float y2);
	void Elastic(char mode, double alpha, double R, 
	int Ball_1, int Ball_2);

};