#include <stdio.h>
#include <stdlib.h>
#include "ObjectAccessor.h"






void addObject(ObjectAccessor* objmgr,void* p, char*name)
{
	ListCh* ls;
	Object * obj;
	if(!Objmgr)
		return;
	ls = objmgr->objectlist;
	ls->Append(ls,p);
}

Object* getObjectFromP(void*p)
{
	ListCh* ls;
	Pointer *itr;
	if(!Objmgr)
		return NULL;
	ls = Objmgr->objectlist;
	itr = ls->begin;
	while((itr = itr->nextpointer) != ls->end)
	{
		if(((Object*)itr->pointer) == p)
			return (Object*)itr->pointer;
	}
	return NULL;
}

void removeObjectFromP(void*p)
{
	ListCh* ls;
	Object * obj;
	if(!Objmgr)
		return;
	ls = Objmgr->objectlist;
	if(obj = getObjectFromP(p))
	{
		ls->Erase(ls,obj);
	}

}

void addTexture(void* p)
{
	ListCh* ls;
	Object * obj;
	if(!Objmgr)
		return;
	ls = Objmgr->texturelist;
	ls->Append(ls,p);
}

Texture* getTextureFromP(void*p)
{
	ListCh* ls;
	Pointer *itr;
	if(!Objmgr)
		return NULL;
	ls = Objmgr->texturelist;
	itr = ls->begin;
	while((itr = itr->nextpointer) != ls->end)
	{
		if(((Texture*)itr->pointer) == p)
			return (Texture*)itr->pointer;
	}
	return NULL;
}
Texture* getTextureFromName(char * name)
{
	ListCh* ls;
	Pointer *itr;
	if(!Objmgr)
		return NULL;
	ls = Objmgr->texturelist;
	itr = ls->begin;
	while((itr = itr->nextpointer) != ls->end)
	{
		if(!strcmp(((Texture*)itr->pointer)->textureName, name))
			return (Texture*)itr->pointer;
	}
	return NULL;
}
void removeTextureFromP(void*p)
{
	ListCh* ls;
	Texture * t;
	if(!Objmgr)
		return;
	ls = Objmgr->objectlist;
	if(t = getTextureFromP(p))
	{
		ls->Erase(ls,t);
	}
}