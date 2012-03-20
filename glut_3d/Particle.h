

#ifndef PARTICLE_H
#define PARTICLE_H


#include "Camera\Vector.h"
#include <vector>

class Particle
{
public:
	Particle(Vector3D v ,float begin ,float ttl, int prog);
	~Particle() {}
	int show(float t);
private:
	Vector3D v; //Vitesse
	float begin;
	float ttl;
	int prog;
};

typedef std::vector<Particle*> lpart;




void showAllParticle(lpart l,float t);




#endif