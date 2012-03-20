
#ifndef MASS_H
#define MASS_H
#include "Object.h"
#include "Camera\Vector.h"

#define GRAVITY_ACCELERATION 9.81

class Mass
{
public:
	Mass(Object* obj, float mass);
	~Mass();

	Vector3D velocity;
	Vector3D force;
	void applyForce(Vector3D f) { force += f;}
	void applyVelocity(Vector3D v) { velocity += v;} 
	void simulate(int dt);
	void setVelocity(Vector3D v){ velocity = v;}


private:
	float mass;
	float absorb;
	Object* obj; // Linked Object
};

class Simulation
{
};


#endif

