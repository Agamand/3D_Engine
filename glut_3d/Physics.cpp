#include "Physics.h"


Mass::Mass(Object* obj, float mass)
{
	this->obj = obj;
	this->mass = mass;
	velocity = Vector3D();
	force = Vector3D();
	absorb = 0.7f;
}


Mass::~Mass()
{
}


void Mass::simulate(int dt)
{

	Vector3D pos = obj->getPosition();
	velocity += (force/mass + Vector3D(0.0f,0.0f,-GRAVITY_ACCELERATION))*dt/1000.0f; //dt is in ms 

	pos += velocity*dt/1000.0f;
	if(pos.getZ() < 0.0)
	{
		pos.setZ(0.0f);
		velocity += Vector3D(0.0f,0.0f,velocity.getZ() < 0 ? -velocity.getZ() : 0)*(1.0f+absorb);
	}
	obj->setPosition(pos);
}