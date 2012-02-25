#include <stdlib.h>
#include "Scene.h"



// CONSTRUTOR / DECONSTRUTOR
Scene * newScene(Scene* sc)
{
	if(!sc)
		sc = (Scene*)malloc(sizeof(Scene));

	sc->object_list = newListCh();
	sc->option = NOTHING_OPTION;
	sc->showAllObject = showAllObject;
	sc->showObject = showObject;
	sc->anim = newAnimScene(NULL);
	return sc;
}
void deleteScene(Scene*sc )
{
	deleteListCh(sc->object_list);
	deleteAnimScene(sc->anim);
	free(sc);
}

Scene* cpyScene(Scene*sc)
{
	Scene* nsc;

	nsc = newScene(NULL);
	nsc->option = sc->option;

}

//Function
void showAllObject(Scene*sc)
{
	Pointer * pt;
	pt = sc->object_list->begin;

	while((pt = pt->nextpointer) != sc->object_list->end)
	{
		sc->showObject((Object*)pt->pointer);
	}
}

void showObject(Object* obj)
{
	switch(obj->type)
	{
	case OBJECT_TYPE_POLYGONE:
		showPolygone((Polygone*)obj);
		break;
	case OBJECT_TYPE_SPHERE:
		showSphere((Sphere*)obj);
		break;
	case OBJECT_TYPE_CONTAINER:
		showContainer((Container*)obj);
		break;
	}
}