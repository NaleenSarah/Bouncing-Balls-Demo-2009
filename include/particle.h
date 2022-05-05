#pragma once
#include "coreMath.h"

#ifndef PARTICLE_H
#define PARTICLE_H



class particle
{
private:
protected:
	Vector2 velocity;
	Vector2 position;
	Vector2 acceleration;
	Vector2 forceAccum;
	


	float radius;
	float damping;	
	float inverseMass;
public:
	float Color[3] = {0};
	int Collided[1000] = { 0 };
	particle(const float vx, const float vy, const float px, const float py, float r, float iMass, float AccX, float AccY, float Damp);
	particle(void);
	~particle(void);
	// calculates the next position of the particle.
	// Duration denotes the time interval  
	//since the last update.
	void integrate(float duration);
	// Sets the position of the particle by component.
	void setPosition(const float x, const float y);
	void setPositionAlpha(const float x, const float y);
	// Gets the position of the particle.  
	Vector2 getPosition(void) const;
	// Sets the velocity of the particle by component.
	
	void setVelocity(const Vector2 &velocity);
	void setVelocity(const float x, const float y);
	void setVelocityBall(const float x, const float y);
	// Gets the velocity of the particle.
	Vector2 getVelocity(void) const;
	//Sets the radius of the particle.
	void setRadius(const float r);
	// Gets the radius of the particle.
	float getRadius(void) const;

	
	void setAcceleration(const Vector2 &acceleration);
	void setAcceleration(const float x, const float y);
	Vector2 getAcceleration() const ;

	
	void setDamping(const float damping);
	float getDamping() const ;

	void setMass(const float mass);
	float getMass() const;
	void setInverseMass(const float inverseMass);
	float getInverseMass() const;
	bool hasFiniteMass() const;

	void clearAccumulator();
	void addForce(const Vector2 &force);

};

#endif PARTICLE_H