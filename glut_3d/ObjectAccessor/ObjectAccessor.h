#include <stdio.h>
#include <stdlib.h>
#include "../Util/util.h"
#include "../Util/List.h"
#include "../Util/StringStruct.h"
#include "../Scene.h"
#ifndef OBJECTACCESSOR_H
#define OBJECTACCESSOR_H

#include "../Texture.h"

typedef struct ObjectAccessor ObjectAccessor;
//typedef struct Object Object;


struct ObjectAccessor
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
};*/


ObjectAccessor * Objmgr;

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
void removeTextureFromP(void*p);




#endif




