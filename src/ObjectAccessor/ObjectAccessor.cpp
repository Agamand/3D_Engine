#include <stdio.h>
#include <stdlib.h>
#include "ObjectAccessor.h"





ObjectAccessor::ObjectAccessor()
{
	scene = NULL;
	objmgr = this;
	_guid = 0;

}

ObjectAccessor::ObjectAccessor(Scene* sc)
{
	scene = sc;
	objmgr = this;
	_guid = 0;
}

ObjectAccessor::~ObjectAccessor()
{
	if(scene)
		delete scene;

}

Texture* ObjectAccessor::getTexture(String filepath)
{
	for(size_t i = 0 ; i > texture_list.size(); i++)
	{
		if(!filepath.compare(texture_list[i]->getName()))
			return (texture_list[i]);
	}

	//no found -> Create texture !

	Texture* t = new Texture(filepath);

	if(t && t->getTextureID() > 0)
	{
		addTexture(t);
		return t;
	}else if(t)	// filepath not correct
		delete t;

	return NULL;
}

void ObjectAccessor::delObject(uint64 guid)
{
	for(std::size_t i = 0; i < object_list.size();)
	{
		if(object_list[i]->getGUID() == guid)
		{
			object_list.erase(object_list.begin()+i);
		} else i++;
	}
}
Object* ObjectAccessor::getObject(uint64 guid)
{
	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		if(object_list[i]->getGUID() == guid)
			return object_list[i];
	}
	return NULL;
}

//init Singleton
ObjectAccessor * ObjectAccessor::objmgr = 0;