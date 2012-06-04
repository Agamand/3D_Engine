#include <stdlib.h>
#include <stdio.h>
#include "../opengl.h"
#include "Scene.h"
#include <iostream>
#include <fstream>


using namespace std;

Scene::Scene(int opt)
{
	time = 0;
	useShader = true;
	_start = false;
	option = opt;
	for(int i = 0; i < MAX_LIGHT; i++)
		_light[i] = false;

	main_shader_program = new Shader("../../src/Shader/Scene.vert","../../src/Shader/Scene.frag");// "../../src/Shader/shownormal.geom");
	shadernormal = new Shader("../../src/Shader/Scene.vert","../../src/Shader/color.frag", "../../src/Shader/shownormal.geom");
	simpleShader = new Shader("../../src/Shader/simpleTransform.vert","../../src/Shader/color.frag");
}

void Scene::update(int diff,bool forced)
{
	if(_start || forced)
		time += diff;

	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		if(_start || forced)
			object_list[i]->updateAnim(time);

		object_list[i]->update(diff);
	}
}

void Scene::reset()
{
	time = 0;
	_start = false;

		//DEBUG LOG
	printf("SCENE RESET");

	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		object_list[i]->updateAnim(0);
	}
}
void Scene::applyOption()
{
	if(option & OPTION_ENABLE_LIGHT)
		glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);

	if(option & OPTION_ENABLE_TEXTURE)
		glEnable(GL_TEXTURE_2D);
	else glDisable(GL_TEXTURE_2D);
}
void Scene::show()
{
	applyOption();

	UniformVar ena_l = main_shader_program->getUniform("enableLight");

	int light[MAX_LIGHT] = 
	{
		_light[0] ? 1 : 0,
		_light[1] ? 1 : 0,
		_light[2] ? 1 : 0,
		_light[3] ? 1 : 0,
		_light[4] ? 1 : 0,
		_light[5] ? 1 : 0,
		_light[6] ? 1 : 0,
		_light[7] ? 1 : 0
	};
	for(int i = 0; i  < MAX_LIGHT; i++)
		glUniform1iv(ena_l.loc+i,1,(light+i));

	if(useShader)
		ActiveShader(main_shader_program);
	else glUseProgram(0);
	if(object_list.empty())
		return;

	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		object_list[i]->show();
	}
	/*ActiveShader(shadernormal);
	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		object_list[i]->show();
	}*/

}

void Scene::del(Object* obj)
{
	if(object_list.empty())
		return;

	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		if(obj == object_list[i])
			object_list.erase(object_list.begin()+i);
	}
}
void Scene::updatePosition()
{

	if(_start)
		return;

	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		object_list[i]->updatePosition(time);
	}
}

void Scene::setTime(int time)
{
	if(_start)
		return;

	//updatePosition();
	if(time < 0)
		time = 0;

	this->time = time;
	//DEBUG LOG
	printf("TIME = %d ms\n",time);
	update(0,true);
}

int Scene::getUnusableLight()
{
	for(int i = 0; i < MAX_LIGHT; i++)
	{
		if(!_light[i]) 
			return i;
	}
	return -1;
}

int Scene::file_import(String filepath)
{
	return 1;
}
int Scene::file_export(String filepath)
{
	ofstream file(filepath.c_str(),ios::out | ios::binary);

	if(!file)
		return -1; // Problème d'ouverture du fichier.

	file << (int)SCENE_VERSION;
	file << option;


	// EXPORT OBJECT
	file << object_list.size();
	for(size_t i = 0; i < object_list.size(); i++)
	{

	}

	file.close();
	return 1;
}
