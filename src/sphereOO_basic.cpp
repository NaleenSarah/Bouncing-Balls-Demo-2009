// sphereJK_OO.cpp
// draw a single sphere in the middle of the screen
// OO basic

#include "includes.h"
#include "SphereOO_basic.h"

//http://en.wikipedia.org/wiki/Density
#define LQ_HYDROGEN 70
#define PLASTIC_A 860
#define WATER 1000
#define EARTH 5515
#define LEAD 11340
#define PLUTONIUM 21450
#define SUN_CORE 150000
#define GREY_HOLE  100000000000000000
#define BLACK_HOLE 400000000000000000
#define FRAME_BREAK 0



float SphereDemo::EuclidD(float x1, float x2, float y1, float y2)
{
	float Dx, Dy;
	Dx = (x1 - x2);
	Dy = (y1 - y2);

	return sqrtf((Dx * Dx) + (Dy * Dy));
}
SphereDemo::SphereDemo()
{
	for ( int j = 1; j < Num_Balls ; j++)
	{
		// x y
		Ball[j-1].setRadius(j*.2);
		Ball[j-1].setPosition( j*0.5-80 , j*7-50);//(j*14+50)-100
		Ball[j-1].setVelocity(0 , 100);
		Ball[j-1].setAcceleration( 0, 0.1f);
		Ball[j-1].setDamping(1.0);
		Ball[j-1].Collided[j] = 0;
		Ball[j-1].setMass(LQ_HYDROGEN*(Ball[j-1].getRadius()/1000));
	}
}
SphereDemo::SphereDemo(int iniBalls)
{
	width = 600; height = 600; nRange = 100;
	if(iniBalls > MAX_Balls/2)
		Num_Balls = iniBalls-1;
	else
		Num_Balls = iniBalls;
	for ( int j = 1; j < MAX_Balls ; j++)
	{
		// x y
		float k = sinf(360/(5)* (j/300.0f));
		Ball[j-1].setRadius(4);
		Ball[j-1].setPosition( k*80 , j*7-50);//(j*14+50)-100
		Ball[j-1].setVelocity(0 , 0);
		Ball[j-1].setAcceleration( 0, 0.1f);
		Ball[j-1].setMass((float)SUN_CORE);
		Ball[j-1].Color[0] = 255.0f; 
		Ball[j-1].Color[1] = 255.0f; 
		Ball[j-1].Color[2] = 0.0f;
		for(int i = 0; i < Num_Balls; i++)
			Ball[j-1].Collided[i] = 0;
		Ball[j-1].setDamping(1);//(j) * 0.8 / Num_Balls );
		
		if(j%2)
		{
			Ball[j-1].setMass((float)PLASTIC_A);
			Ball[j-1].setRadius(2);
			Ball[j-1].Color[0] = (j / 255.0f) * (255.0f/Num_Balls) ; 
			Ball[j-1].Color[1] = (255.0f/Num_Balls); 
			Ball[j-1].Color[2] = 100.0f;
		}
		if(j == 1)
		{
			Ball[j-1].setMass((float)BLACK_HOLE);
			Ball[j-1].setRadius(1.7f);
			Ball[j-1].setPositionAlpha(0.0f, Ball[j-1].getPosition().y);
			Ball[j-1].Color[0] = 0.0f; 
			Ball[j-1].Color[1] = 0.0f; 
			Ball[j-1].Color[2] = 0.0f;
		}
		if(j == 10)
		{
			Ball[j-1].setMass((float)BLACK_HOLE);
			Ball[j-1].setRadius(1.8f);
			Ball[j-1].setPositionAlpha(0.1f, Ball[j-1].getPosition().y);
			Ball[j-1].Color[0] = 0.0f; 
			Ball[j-1].Color[1] = 0.0f; 
			Ball[j-1].Color[2] = 0.0f;
		}
		if(j > 16)
		{
			Ball[j-1].setMass((float)GREY_HOLE/4);
			Ball[j-1].setRadius(3.0f);
			Ball[j-1].Color[0] = 150.0f; 
			Ball[j-1].Color[1] = 150.0f; 
			Ball[j-1].Color[2] = 150.0f;
		}

		 
	}
}

void SphereDemo::sphereUpdate(void)
{
	
	float g = 9.8f;

	float duration = Application::timeinterval / 8000;

	GLfloat aspectRatio = 6;
	float buffer = 0.0;

	for(int j = 0; j < Num_Balls ; j++)
	{

		//Double step detection.
		//Left
		if( Ball[j].getPosition().x < -nWidth + Ball[j].getRadius() )
		{
			Ball[j].setPositionAlpha(-nWidth + Ball[j].getRadius(), Ball[j].getPosition().y );
			if(Ball[j].getVelocity().x < 0)
			 Ball[j].setVelocity(-1, 1);
		}

		//Right
		if( Ball[j].getPosition().x > nWidth - Ball[j].getRadius() )
		{
			Ball[j].setPositionAlpha(nWidth - Ball[j].getRadius(), Ball[j].getPosition().y );
			if(Ball[j].getVelocity().x > 0)
				Ball[j].setVelocity(-1, 1);
		}

		//Bottom
		if( Ball[j].getPosition().y < -nWidth + Ball[j].getRadius())
		{
			Ball[j].setPositionAlpha(Ball[j].getPosition().x, -nWidth + Ball[j].getRadius());
			//Ball[j].setVelocity(1, -1);
			if(Ball[j].getVelocity().y < 0)
				Ball[j].setVelocity(1, -1);
		}
		
		//Top
		if(Ball[j].getPosition().y > nWidth  - Ball[j].getRadius())
		{
			if(Ball[j].getVelocity().y > 0)
				Ball[j].setVelocity(1, -1);
		}
		
		
		if( Ball[j].getPosition().y <= -nWidth + Ball[j].getRadius() )
		{
			float SpeedBallJ = (pow(Ball[j].getVelocity().y , 2) + pow(Ball[j].getVelocity().x , 2));
			//Ball[j].setVelocityBall(Ball[j].getVelocity().x, 0);
			if(SpeedBallJ <= 0.09)
			{
				Ball[j].setVelocityBall(Ball[j].getVelocity().x, 0); 
				Ball[j].setPositionAlpha(Ball[j].getPosition().x, -nWidth + Ball[j].getRadius());
			}
			
		}
		

		//move the sphere
		
		for (int i = 0 ; i < Num_Balls-1; i++)
		{
			int pColi_1 = j;
			int pColi_2 = i;

			if(Ball[pColi_1].Collided[pColi_2] > 0)
				Ball[pColi_1].Collided[pColi_2] -= 1;
			if(Ball[pColi_2].Collided[pColi_1] > 0)
				Ball[pColi_2].Collided[pColi_1] -= 1;

			if( Ball[pColi_1].Collided[pColi_2] == 0 && Ball[pColi_2].Collided[pColi_1] == 0) 
			{
				float mDistance = EuclidD(Ball[j].getPosition().x, Ball[i].getPosition().x, Ball[j].getPosition().y, Ball[i].getPosition().y) ;

				if( mDistance < (Ball[j].getRadius() + Ball[i].getRadius()))
				{
					//if(j <= Num_Balls-1)
					{
						if(j != i)
						{
						

						
						
							float aX = (Ball[pColi_1].getPosition().x - Ball[pColi_2].getPosition().x);
							float aY = (Ball[pColi_1].getPosition().y - Ball[pColi_2].getPosition().y);
							float Angle = atan2(aX, aY);
							//mode, angle of collision, damping (1 = perfect), array index 1 & 2
							Elastic('0', Angle , 1.0, pColi_1, pColi_2);
							Ball[pColi_1].Collided[pColi_2] += FRAME_BREAK; 
							Ball[pColi_2].Collided[pColi_1] += FRAME_BREAK;

							//Basic Y penetration Calculation.
							if(Ball[pColi_1].getPosition().y > Ball[pColi_2].getPosition().y)
							{
								float mPenetration = (Ball[pColi_1].getRadius() + Ball[pColi_2].getRadius()) - mDistance;
								Ball[pColi_1].setPositionAlpha( Ball[pColi_1].getPosition().x,  Ball[pColi_1].getPosition().y + mPenetration);
							}
							float mAbsVel = pow(Ball[pColi_1].getVelocity().y , 2) + pow(Ball[pColi_1].getVelocity().x , 2) ;
							if(mAbsVel < 0.0005)
							{
								Ball[pColi_1].setVelocity(0,0);
								Ball[pColi_1].setAcceleration(0,0);
							}
						}
					}
				}
			}
		}

		Ball[j].setPosition(Ball[j].getVelocity().x, Ball[j].getVelocity().y);
		Ball[j].addForce(Vector2( 0, (-g * Ball[j].getMass()) ));
		Ball[j].integrate(duration);
		

	}

	Application::update();
}

void SphereDemo::display(void)
{
	Application::display();

	sphereUpdate();
	for(int j = 0 ; j < Num_Balls ; j++)
	{
		
		glPushMatrix(); 
		{
			glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
			glColor3ub( j*ColourB, 255-(j*ColourB), 180);
			glColor3ub( Ball[j].Color[0], Ball[j].Color[1], Ball[j].Color[2]);
			glTranslatef( Ball[j].getPosition().x, Ball[j].getPosition().y, 0);
			glutSolidSphere( Ball[j].getRadius(),30,30);
		}
		glPopMatrix();
	}

	glutSwapBuffers();
	glutPostRedisplay();

}

Application* getApplication()
{
    return new SphereDemo();
}
Application* getApplication(int iniBalls)
{
	
	
    return new SphereDemo(iniBalls);
}


void SphereDemo::Elastic(char mode,double alpha, double R, 
	int Ball_1, int Ball_2)
{

	double  r12,m21,d,gammav,gammaxy,dgamma,dr,dc,sqs,t,
			dvx2,a,x21,y21,vx21,vy21,pi2,vx_cm,vy_cm;

	double m1 = Ball[Ball_1].getMass();
	double m2 = Ball[Ball_2].getMass();

	//Velocities
	double vx1 = Ball[Ball_1].getVelocity().x;
	double vy1 = Ball[Ball_1].getVelocity().y;

	double vx2 = Ball[Ball_2].getVelocity().x;
	double vy2 = Ball[Ball_2].getVelocity().y;

	//positions
	double x1 = Ball[Ball_1].getPosition().x;
	double y1 = Ball[Ball_1].getPosition().y;

	double x2 = Ball[Ball_2].getPosition().x;
	double y2 = Ball[Ball_2].getPosition().y;

	//Radius'
	double r1 = Ball[Ball_1].getRadius();
	double r2 = Ball[Ball_2].getRadius();



	pi2 = 2*acos(-1.0E0);
	//Radius i + i+1
	r12 = r1+r2+0.1;

	//Difference in Mass
	m21 = m2/m1;

	//Difference in X Coord
	x21 = x2-x1;
	//Difference in Y Coord
	y21 = y2-y1;

	//Difference in Velocities
	vx21 = vx2-vx1;
	vy21 = vy2-vy1;

	vx_cm = (m1*vx1+m2*vx2)/(m1+m2) ;
	vy_cm = (m1*vy1+m2*vy2)/(m1+m2) ;



	//calculate relative velocity angle             
	gammav=atan2(-vy21,-vx21);




	//If Initial Position Given
	//Free Mode
	if (mode != 'f')
	{

       
		d=sqrt(x21*x21 +y21*y21);
       
		//Calc Reletive Positions
		gammaxy=atan2(y21,x21);
		dgamma=gammaxy-gammav;
		if (dgamma>pi2) 
		{
			dgamma=dgamma-pi2;
		}
		else if (dgamma<-pi2)
		{
			dgamma=dgamma+pi2;
		}
		dr=d*sin(dgamma)/r12;
      


		//calculate impact angle if balls collide
		alpha=asin(dr);

       
		//calculate time to collision
		dc=d*cos(dgamma);
		if (dc>0) 
		{
			sqs=1.0;
		}
		else 
		{
			sqs=-1.0;
		}
		t=(dc-sqs*r12*sqrt(1-dr*dr))/sqrt(vx21*vx21+ vy21*vy21);
		
		//update positions
		x1=x1+vx1*t;
		y1=y1+vy1*t;
		x2=x2+vx2*t;
		y2=y2+vy2*t;

       
	}//END
       
	//update velocities 
    a=tan( gammav +alpha);

    dvx2 = -2* (vx21 +a*vy21) / ( (1+a*a) * (1+m21) );
       
    vx2 = vx2 +			dvx2;
    vy2 = vy2 + a		*dvx2;
    vx1 = vx1 - m21		*dvx2;
    vy1 = vy1 - a*m21	*dvx2;

	Ball[Ball_1].setVelocityBall(vx1,vy1);
	Ball[Ball_2].setVelocityBall(vx2,vy2);
       

    return;
}