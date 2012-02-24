

#ifndef SCENE_H
#define SCENE_H

#include "Object.h"

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
	int option;

	void (*showAllObject)(Scene*);
	void (*showObject)(Object*);

};

// CONSTRUTOR / DECONSTRUTOR
Scene * newScene(Scene*);
void deleteScene(Scene*);


//Function
void showAllObject(Scene*);
void showObject(Object*);

#endif