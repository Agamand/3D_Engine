
#ifndef OBJECTACCESSOR_H
#define OBJECTACCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include "../Util/util.h"
#include "../Scene/Scene.h"
#include "../Texture/Texture.h"
#include "../Shader/Shader.h"
#include <list>
#include <assert.h>



class ObjectAccessor
{
public:
	ObjectAccessor();
    ObjectAccessor(Scene* sc);
	~ObjectAccessor();

	Texture* getTexture(String name);
	void addTexture(Texture* t) { texture_list.push_back(t); }
	// void delTexture(Texture* t);
	
	Shader* getShader();
	void addShader(Shader* sh);
	

	Scene* getScene() { return scene; }
	void setScene(Scene * sc) { scene = sc;}
	uint64 nextGUID() {return ++_guid;}
	void addObject(Object* obj) { object_list.push_back(obj);}
	void delObject(Object* obj) { delObject(obj->getGUID());}
	void delObject(uint64 guid);
	Object* getObject(uint64 guid);

	List<Object*> getLostObject() {return lost_object;}


	// Shader* getShader(String name);
	// void addShader(Shader* sh) { program_list.push_back(sh); }

	static ObjectAccessor* getObjMgr() 
	{
		if(!objmgr)
			objmgr = new ObjectAccessor();
		
		assert(objmgr != NULL);
		return objmgr;
	}

private:
	Scene* scene;
	List<Texture*> texture_list;
	List<Object*> object_list;
	List<Object*> lost_object;
	//std::list<> program_list;
	//Singleton
	static ObjectAccessor* objmgr;
	uint64 _guid;
};

#endif




