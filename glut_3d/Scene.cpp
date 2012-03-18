#include <stdlib.h>
#include <stdio.h>
#include "Scene.h"




Scene::Scene()
{
	time = 0;
	_start = false;
}


void Scene::update(int diff,bool forced)
{
	if(!_start && !forced)
		return;

	time += diff;

	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		object_list[i]->update(time);
	}
}

void Scene::reset()
{
	time = 0;
	_start = false;

	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		object_list[i]->update(0);
	}
}

void Scene::show()
{
	if(object_list.empty())
		return;

	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		object_list[i]->show();
	}
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

	updatePosition();
	this->time = time;
	update(0,true);
}

/*
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
void showAllObject(Scene*sc,int* name)
{
	Pointer * pt;
	pt = sc->object_list->begin;

	while((pt = pt->nextpointer) != sc->object_list->end)
	{
		sc->showObject((Object*)pt->pointer, name);
	}
}

void showObject(Object* obj,int*name)
{
	switch(obj->type)
	{
	case OBJECT_TYPE_POLYGONE:
		showPolygone((Polygone*)obj,name);
		break;
	case OBJECT_TYPE_SPHERE:
		showSphere((Sphere*)obj,name);
		break;
	case OBJECT_TYPE_CONTAINER:
		showContainer((Container*)obj,name);
		break;
	case OBJECT_TYPE_LIGHT:
		showLight((Light*)obj);
	}
}
Object* loadObject(FILE* fl,AnimScene* anims)
{
	Object* obj,*obj_bis;
	Container* cont;
	Polygone* poly;
	Animation* anim;
	Point* pt;
	int value,i;
		long point;
	fread(&value,sizeof(int),1,fl);
	fread(&value,sizeof(int),1,fl);
	fseek(fl,-sizeof(int),SEEK_CUR);
	switch(value)
	{
		case OBJECT_TYPE_CONTAINER:
			obj = (Object*)malloc(sizeof(Container));
			fread(obj,sizeof(Object),1,fl);
			cont = (Container*)obj;
			cont->objectL = newListCh();
			cont->showRep = 0;
			fread(&cont->center,sizeof(Point),1,fl);
			fread(&cont->repere,sizeof(Point),1,fl);
			fread(&value,sizeof(int),1,fl);
			fread(&value,sizeof(int),1,fl);
			for(i = 0; i < value; i++)
			{
				obj_bis = loadObject(fl,anims);
				if(obj_bis)
					cont->objectL->Append(cont->objectL,obj_bis);
			}
			fread(&value,sizeof(int),1,fl);
			fread(&value,sizeof(int),1,fl);
			if(value == 1)
			{
				anim = (Animation*)malloc(sizeof(Animation));
				fread(anim,sizeof(Animation),1,fl);
				anim->obj = obj;
				initAnim(anim);
				addAnim(anims,anim);
			}
			break;
		case OBJECT_TYPE_POLYGONE:
			obj = (Object*)malloc(sizeof(Polygone));
			fread(obj,sizeof(Object),1,fl);
			poly = (Polygone*)obj;
			poly->lPoint = newListCh();
			fread(&value,sizeof(int),1,fl);
			fread(&value,sizeof(int),1,fl);
			for(i = 0; i < value; i++)
			{
				pt = (Point*)malloc(sizeof(Point));
				fread(pt,sizeof(Point),1,fl);
				poly->lPoint->Append(poly->lPoint,pt);
			}
			fread(&value,sizeof(int),1,fl);
			fread(&value,sizeof(int),1,fl);
			if(value == 1)
			{
				anim = (Animation*)malloc(sizeof(Animation));
				fread(anim,sizeof(Animation),1,fl);
				anim->obj = obj;
				initAnim(anim);
				addAnim(anims,anim);
			}
			break;
		default:
			break;

	}
	return obj;
}
Scene* loadScene(char* filename)
{
	int i = 0;
	Object* obj;
	FILE* fl = NULL;
	Scene* sc = NULL;
	Pointer *itr, *end;
	int value;
	long size;

	if(!(fl = fopen(filename,"rb")))
		return NULL;
	fseek(fl,0,SEEK_END);
	size = ftell(fl);
	fseek(fl,0,SEEK_SET);
	fread(&value,sizeof(int),1,fl);

	if(value != FILE_SCENE)
	{
		fclose(fl);
		return NULL;
	}
	sc = newScene(NULL);
	fread(&sc->option,sizeof(int),1,fl);

	fread(&value,sizeof(int),1,fl);
	fread(&value,sizeof(int),1,fl);

	for(i = 0; i < value; i++)
	{
		obj = loadObject(fl,sc->anim);
		sc->object_list->Append(sc->object_list,obj);
	}
	fclose(fl);
	return sc;
}

void saveObject(FILE* fl,Object* obj, AnimScene* anims)
{
	int value;
	Polygone* poly = NULL;
	Container* cont = NULL;
	Animation * anim;
	Pointer* itr, *end;
	if(!fl)
		return;

	value = FILE_OBJECT;
	fwrite(&value,sizeof(int),1,fl);
	switch(obj->type)
	{
	case OBJECT_TYPE_CONTAINER:
		cont = (Container*)obj;
		fwrite(obj,sizeof(Object),1,fl);
		fwrite(&cont->center,sizeof(Point),1,fl);
		fwrite(&cont->repere,sizeof(Point),1,fl);
		value = FILE_LISTCH;
		fwrite(&value,sizeof(int),1,fl);
		fwrite(&cont->objectL->size,sizeof(int),1,fl);
		itr = cont->objectL->begin;
		end = cont->objectL->end;
		while((itr = itr->nextpointer) != end)
		{
			saveObject(fl,(Object*)itr->pointer,anims);
		}
		value = FILE_ANIM;
		fwrite(&value,sizeof(int),1,fl);
		if(anim = getAnimFromObj(anims,obj))
		{
			value = 1;
			fwrite(&value,sizeof(int),1,fl);
			fwrite(anim,sizeof(Animation),1,fl);
		}else
		{
			value = 0;
			fwrite(&value,sizeof(int),1,fl);
		}
		break;
	case OBJECT_TYPE_POLYGONE:
		poly = (Polygone*)obj;
		fwrite(obj,sizeof(Object),1,fl);
		value = FILE_LISTCH;
		fwrite(&value,sizeof(int),1,fl);
		fwrite(&poly->lPoint->size,sizeof(int),1,fl);
		itr = poly->lPoint->begin;
		end = poly->lPoint->end;
		while((itr = itr->nextpointer) != end)
		{
			fwrite(itr->pointer,sizeof(Point),1,fl);
		}
		value = FILE_ANIM;
		fwrite(&value,sizeof(int),1,fl);
		if(anim = getAnimFromObj(anims,obj))
		{
			value = 1;
			fwrite(&value,sizeof(int),1,fl);
			fwrite(anim,sizeof(Animation),1,fl);
		}else
		{
			value = 0;
			fwrite(&value,sizeof(int),1,fl);
		}
		break;
	default:
		break;
	}
}

void saveScene(Scene* sc,char* filename)
{
	FILE* fl = NULL;
	Pointer* itr, *end;
	int value;
	if(!(fl = fopen(filename,"rb+")))
		fl = fopen(filename,"wb+");

	if(!fl)
		return;

	value = FILE_SCENE;
	fwrite(&value,sizeof(int),1,fl);
	fwrite(&sc->option,sizeof(int),1,fl);

	value = FILE_LISTCH;
	fwrite(&value,sizeof(int),1,fl);
	fwrite(&sc->object_list->size,sizeof(int),1,fl);
	itr = sc->object_list->begin;
	end = sc->object_list->end;
	while((itr = itr->nextpointer) != end)
	{
		saveObject(fl,(Object*)itr->pointer,sc->anim);
	}
	fclose(fl);

}
*/