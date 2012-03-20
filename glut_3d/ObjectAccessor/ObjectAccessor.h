
#ifndef OBJECTACCESSOR_H
#define OBJECTACCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include "../Util/util.h"
#include "../Scene.h"
#include "../Texture.h"
#include "../Shader.h"
#include <list>


class ObjectAccessor
{
public:
	ObjectAccessor();
    ObjectAccessor(Scene* sc);
	~ObjectAccessor();

	Texture* getTexture(String name);
	void addTexture(Texture* t) { texture_list.push_back(t); }

	Scene* getScene() { return scene; }
	void setScene(Scene * sc) { scene = sc;}
	uint64 nextGUID() {return ++_guid;}
	//static ObjectAccessor * Objmgr;
	// Shader* getShader(String name);
	// void addShader(Shader* sh) { program_list.push_back(sh); }

	static ObjectAccessor* getObjMgr() 
	{
		if(!objmgr)
			objmgr = new ObjectAccessor();
		return objmgr;
	}

private:
	Scene* scene;
	std::list<Texture*> texture_list;
	//std::list<> program_list;
	static ObjectAccessor* objmgr;
	uint64 _guid;
};

//ObjectAccessor * ObjectAccessor::objmgr = NULL;



//typedef struct ObjectAccessor ObjectAccessor;
//typedef struct Object Object;


/*struct ObjectAccessor
{
	Scene* scene;
	ListCh* objectlist;
	ListCh* texturelist;
	ListCh* programList;
	//unsigned long int guid;
};

/*struct Object
{
	uint64 guid;
	uint32 type;
	StringC * name;
	void * p;
};*//*




static void initObjectAccessor()
{
	Objmgr = (ObjectAccessor*)malloc(sizeof(ObjectAccessor));
	Objmgr->objectlist = newListCh();
	Objmgr->texturelist = newListCh();

}
static ObjectAccessor * getObjectAccessor()
{
	return Objmgr;
}


//ObjectAccessor function
void addObject(void* p);
Object* getObjectFromP(void*p);
void removeObjectFromP(void*p);

void addTexture(void* p);
Texture* getTextureFromP(void*p);
Texture* getTextureFromName(char * name);
void removeTextureFromP(void*p);*/




#endif




