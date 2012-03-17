

#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include "Animation.h"
#include <vector>

enum SceneOption
{
	NOTHING_OPTION = 0x0,
	ENABLE_LIGHT = 0x1,
	ENABLE_TEXTURE = 0x2,
};

class Scene
{
public:
	Scene();
	~Scene() {;}
	void start() { reset(); _start = true; }
	void update(int time,bool forced = false);
	void reset();
	void show();
	void add(Object* obj) { object_list.push_back(obj); }
	void del(Object* obj);
private:
	std::vector<Object*> object_list;
	int time;
	bool _start;
};
#endif