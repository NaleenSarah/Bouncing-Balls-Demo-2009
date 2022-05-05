#include <gl/glut.h>
#include "coreMath.h"
#include "particle.h"
#include <assert.h>
#include <float.h>

#define SHINEY 0.9
#define ROUGHASS 0.01

float MAX_Speed = 3.0f;

particle::particle(const float vx = 3, const float vy = 1, const float px = 0, const float py = 0, float r = 1, float iMass = 0, float AccX = 0, float AccY = 0, float Damp = 1)
{
	this->position = Vector2(px, py);
	this->velocity = Vector2(vx, vy);
	this->radius = r;
	this->inverseMass = iMass;
	this->acceleration = Vector2(AccX, AccY);
	this->damping = Damp;
}

particle::particle(void)
{
	this->position = Vector2(0, 0);
	this->velocity = Vector2(1.5, 1.5);
	this->radius = 1;
	this->inverseMass = 0;
	this->acceleration = Vector2(1, 1);
	this->damping = 1;
}

particle::~particle(void){}
// calculates the next position of the particle.
// Duration denotes the time interval  
//since the last update.
//void particle::integrate(float duration = 0.0f)
//{
//	assert(duration > 0.0);
//	velocity.addScaledVector(acceleration, duration);
//	position.addScaledVector(velocity, duration);
//}

void particle::integrate(float duration)
{


	/*assert(duration > 0.0);
	velocity.addScaledVector(acceleration, duration);
	velocity *= pow(damping, duration);
	position.addScaledVector(velocity, duration);*/
	
	/*if (inverseMass <= 0.0f) return;
	assert(duration > 0.0);
	velocity.addScaledVector(acceleration, duration);
	velocity *= pow(damping, duration);
	position.addScaledVector(velocity, duration);*/

	
	if (inverseMass <= 0.0f) return;
		assert(duration > 0.0f);

	// Work out the acceleration from the force
	Vector2 resultingAcc = acceleration;
	resultingAcc.addScaledVector(forceAccum,inverseMass);
	// Update linear velocity from the acceleration.
	velocity.addScaledVector(resultingAcc, duration);
	// Impose drag.
	float fluidD = 0.011f;
	float speedA = (pow(this->acceleration.y , 2) + pow(this->acceleration.x , 2)) ;
	float VelV = pow(this->velocity.y , 2) + pow(this->velocity.x , 2) ;
	//float dragCoe = / 0.5*( fluidD * (3.14*this->radius*this->radius) * speedA)
	

	this->damping = 0.25f * (fluidD * VelV * 0.9f * (3.14f*this->radius*this->radius));
	
	velocity *= pow(damping, duration);
	// Update linear position.
	position.addScaledVector(velocity, duration);
	// Clear the forces
	clearAccumulator();

	


}
// Sets the position of the particle by component.
void particle::setPosition(const float x, const float y)
{
	this->position.x += x;
	this->position.y += y;

}
void particle::setPositionAlpha(const float x, const float y)
{
	this->position.x = x;
	this->position.y = y;

}

// Gets the position of the particle.  
Vector2 particle::getPosition(void) const
{
	return this->position;
}

// Sets the velocity of the particle by component.
void particle::setVelocity(const Vector2 &velocity)
{
	particle::velocity = velocity;
}

void particle::setVelocity(const float x, const float y)
{

	this->velocity.x *= x;
	this->velocity.y *= y;

	if(this->velocity.x > 5)
		this->velocity.x = 5;
	if(this->velocity.y > 5)
		this->velocity.y = 5;

	if(this->velocity.x < -5)
		this->velocity.x = -5;
	if(this->velocity.y < -5)
		this->velocity.y = -5;
}

void particle::setVelocityBall(const float x, const float y)
{
	

	this->velocity.x = x;
	this->velocity.y = y;

	if(this->velocity.x > MAX_Speed)
		this->velocity.x = MAX_Speed;
	if(this->velocity.y > MAX_Speed)
		this->velocity.y = MAX_Speed;

	if(this->velocity.x < -MAX_Speed)
		this->velocity.x = -MAX_Speed;
	if(this->velocity.y < -MAX_Speed)
		this->velocity.y = -MAX_Speed;
}

// Gets the velocity of the particle.
Vector2 particle::getVelocity(void) const
{
	return this->velocity;
}

//Sets the radius of the particle.
void particle::setRadius(const float r)
{
	this->radius = r;
}

// Gets the radius of the particle.
float particle::getRadius(void) const
{
	return this->radius;
}

void particle::setAcceleration(const Vector2 &acceleration)
{
	particle::acceleration = acceleration;
}

void particle::setAcceleration(const float x, const float y)
{
	this->acceleration.x = x;
	this->acceleration.y = y;
}

Vector2 particle::getAcceleration(void) const 
{
	return this->acceleration;
}

void particle::setDamping(const float damping)
{
	particle::damping = damping;
}

float particle::getDamping() const
{
	return this->damping;
}

void particle::setMass(const float mass)
{
	assert(mass != 0);
	this->inverseMass = ((float)1.0)/mass;
}

float particle::getMass() const
{
	if(inverseMass == 0)
	{
		return (float)DBL_MAX;
	}
	else
	{
		return ((float)1.0)/inverseMass;
	}
}

void particle::setInverseMass(const float inverseMass)
{
	this->inverseMass = inverseMass;
}

float particle::getInverseMass() const
{
	return inverseMass;
}

bool particle::hasFiniteMass() const
{
	return inverseMass >= 0.0f;
}

void particle::clearAccumulator()
{
	forceAccum.clear();
}

void particle::addForce(const Vector2 &force)
{
	forceAccum += force;
}
