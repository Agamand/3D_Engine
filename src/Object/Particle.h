

#ifndef PARTICLE_H
#define PARTICLE_H


#include <glm/glm.hpp>
#include "../Util/List.h"
#include <vector>

class Particle
{
public:
	Particle(glm::vec3 v ,glm::vec3 a,float begin ,float ttl, int prog);
	~Particle() {}

	bool show(float t);
	void generate(glm::vec3 v,glm::vec3 a, float begin, float ttl);
private:
	glm::vec3 v; //Vitesse
	glm::vec3 a;
	float begin;
	float ttl;
	int prog;
};

typedef List<Particle*> lpart;




void showAllParticle(lpart l,float t);




#endif