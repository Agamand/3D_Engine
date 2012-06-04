#ifndef GEOM_H
#define GEOM_H
#include <glm/glm.hpp>

class Plan;
class Droite;

class Droite
{
public:
	Droite(glm::vec3 orig, glm::vec3 dir);

	glm::vec3 ori;
	glm::vec3 dir;
};

class Plan
{
public:
	Plan() {p = glm::vec3(); normal = glm::vec3(0,0,1);}
	Plan(glm::vec3 p, glm::vec3 normal);

	bool intersect(Plan p,Droite &d);
	bool intersect(Droite d, glm::vec3 &v);

	glm::vec3 p;
	glm::vec3 normal;
};

class Triangle
{

};


class RayTest
{
public:
	RayTest() { p = Plan();}
	RayTest(Plan _p);

	bool test(glm::vec3 &v,int x, int y,glm::vec3 campos);
private:
	Plan p; // intersec plan
};

#endif GEOM_H