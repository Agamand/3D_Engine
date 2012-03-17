#include <glew.h>
#include <stdlib.h>
#include "Shader.h"
#include "Particle.h"





Particle::Particle(Vector3D v,float begin, float ttl, int prog)
{
	this->v = v;
	this->begin = begin;
	this->ttl = ttl;
	this->prog = prog;
}
int Particle::show(float t)
{
	int uniID[3];
	if(ttl < t-begin)
		return 0;

	uniID[0] = glGetUniformLocation(prog, "time");
	uniID[1] = glGetUniformLocation(prog, "repeat");
	uniID[2] = glGetUniformLocation(prog, "v0");
	glUseProgram(prog);
	glUniform1f(uniID[0],t-begin);
	glUniform1f(uniID[1],ttl);
	glUniform3f(uniID[2],v.getX(),v.getY(),v.getZ());
	glBegin(GL_POINTS);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.01f,0.0f,0.01f);
/*	glVertex3f(0.01f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.01);*/
	glEnd();
	glUseProgram(0);
	return 1;
}

void showAllParticle(lpart list,float t)
{

	if(list.empty())
		return;

	for(std::size_t i = 0; i < list.size(); i++)
	{		
		if(!list[i]->show(t))
		{
			//delete list[i];
			//list.erase(list.begin()+i);

		}
	}
}