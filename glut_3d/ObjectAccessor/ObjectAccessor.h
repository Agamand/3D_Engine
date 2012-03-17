
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
	//static ObjectAccessor * Objmgr;
	// Shader* getShader(String name);
	// void addShader(Shader* sh) { program_list.push_back(sh); }

	static ObjectAccessor* getObjMgr() {return objmgr;}

private:
	Scene* scene;
	std::list<Texture*> texture_list;
	//std::list<> program_list;
	static ObjectAccessor* objmgr;
};



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




