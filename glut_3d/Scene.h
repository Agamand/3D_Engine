

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

#define MAX_LIGHT 8

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
	void setTime(int time);
	int getTime() { return time; }
	void incTime(int time = 100) { setTime(this->time + time); }
	void updatePosition();
	int getUnusableLight();
	bool isEnable(int light) { if(light >= MAX_LIGHT || light < 0) return false; _light[light];}
	void enableLight(int n) { if(n >= MAX_LIGHT || n < 0) return; _light[n] = true;}
	void disableLight(int n) { if(n >= MAX_LIGHT || n < 0) return; _light[n] = false;}
private:
	std::vector<Object*> object_list;
	int time;
	bool _start;
	bool _light[MAX_LIGHT];
};
#endif