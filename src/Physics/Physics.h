
#ifndef MASS_H
#define MASS_H
#include <glm/glm.hpp>
#include "../Object/Object.h"

#define GRAVITY_ACCELERATION 9.81

class Mass
{
public:
	Mass(Object* obj, float mass);
	~Mass();

	glm::vec3 velocity;
	glm::vec3 force;
	void applyForce(glm::vec3 f) { force += f;}
	void applyVelocity(glm::vec3 v) { velocity += v;} 
	void simulate(int dt);
	void setVelocity(glm::vec3 v){ velocity = v;}


private:
	float mass;
	float absorb;
	Object* obj; // Linked Object
};

class Simulation
{
};

#endif

