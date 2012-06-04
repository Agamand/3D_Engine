#include "Physics.h"


Mass::Mass(Object* obj, float mass)
{
	this->obj = obj;
	this->mass = mass;
	velocity = glm::vec3();
	force = glm::vec3();
	absorb = 1.0f;
}


Mass::~Mass()
{
}


void Mass::simulate(int dt)
{

	glm::vec3 pos = obj->getPosition();
	velocity += (force/mass + glm::vec3(0.0f,0.0f,-GRAVITY_ACCELERATION))*(float)dt/1000.0f; //dt is in ms 

	pos += velocity*(float)dt/1000.0f;
	if(pos.z < 0.0)
	{
		pos.z = 0.0f;
		velocity += glm::vec3(0.0f,0.0f,velocity.z < 0 ? -velocity.z : 0)*(1.0f+absorb);
	}
	obj->setPosition(pos);
}