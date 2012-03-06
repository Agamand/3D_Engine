

#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include "Animation.h"

typedef struct _scene Scene;

enum SceneOption
{
	NOTHING_OPTION = 0x0,
	ENABLE_LIGHT = 0x1,
	ENABLE_TEXTURE = 0x2,
};

struct _scene
{
	ListCh * object_list;
	AnimScene * anim;
	int option;

	void (*showAllObject)(Scene*,int*);
	void (*showObject)(Object*,int*);

};

// CONSTRUTOR / DECONSTRUTOR
Scene* newScene(Scene*);
void deleteScene(Scene*);
Scene* cpyScene(Scene*);

//Function
void showAllObject(Scene*,int*);
void showObject(Object*,int*);

Scene* loadScene(char*);
void saveScene(Scene*,char*);

#endif