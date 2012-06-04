
#include <stdlib.h>
#include "../Shader/Shader.h"
#include "Particle.h"
#include "../opengl.h"





Particle::Particle(glm::vec3 v, glm::vec3 a, float begin, float ttl, int prog)
{
    this->v = v;
    this->begin = begin;
    this->ttl = ttl;
    this->prog = prog;
	this->a = a;
}

void Particle::generate(glm::vec3 v,glm::vec3 a, float begin, float ttl)
{
    this->v = v;
	this->a = a;
    this->begin = begin;
    this->ttl = ttl;
}

bool Particle::show(float t)
{
    int uniID[4];

	if(begin > t)
		return true;

    if(ttl < t-begin)
        return false;

    uniID[0] = glGetUniformLocation(prog, "time");
    uniID[1] = glGetUniformLocation(prog, "repeat");
    uniID[2] = glGetUniformLocation(prog, "v0");
	uniID[3] = glGetUniformLocation(prog, "v2");
    glUseProgram(prog);
    glUniform1f(uniID[0],t-begin);
    glUniform1f(uniID[1],ttl);
    glUniform3f(uniID[2],v.x,v.y,v.z);
	glUniform3f(uniID[3],a.x,a.y,a.z);
	glBegin(GL_POINTS);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.01f,0.0f,0.01f);
    /*glVertex3f(0.005f,0.0f,0.1f);
    glVertex3f(0.01f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);*/
    //glVertex3f(0.0f,0.0f,0.01);
    glEnd();
    glUseProgram(0);
    return true;
}

void showAllParticle(lpart list,float t)
{

    if(list.empty())
        return;
    
    std::size_t max = list.size();
	for(std::size_t i = 0; i < max; )
    {        
        if(!list[i]->show(t))
        {
            //delete list[i];
            list.erase(list.begin()+i);
        }else i++;
    }
}