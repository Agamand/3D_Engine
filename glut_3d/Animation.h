

#ifndef ANIMATION_H
#define ANIMATION_H
#include "Camera\Vector.h"
#include "MathPlus.h"
#include "Object.h"
#include <map>

enum AnimFlag
{
	ANIMFLAG_NOTHING = 0x00,
	ANIMFLAG_INSTANTLY = 0x01,
};

class MoveInfo_compare
{
public:
    bool operator()(const int& a, const int& b)
    {
        return a < b;
    }
};

class Animation
{
public:

	struct MoveInfo
	{
		Vector3D pos;
		Quat rot;
		int time;
	};

	Animation();
	void update(int diff);
	void reset();
	void addMoveInfo(MoveInfo mi,int time);
	void remMoveInfo(int time);
	

private:
	std::map<int,MoveInfo,MoveInfo_compare> mv_list;
};/*
struct _animation //time in ms
{
	Object * obj;
	MoveInfo mv_info[256];
	int mv_size;
	
	void (*update)(Animation*,int);

};

struct _animationscene
{
	ListCh* l_anim;
	int t;
	int start;
	void(*update)(AnimScene*,int, int);
	void (*reset)(AnimScene*);
};
AnimScene* newAnimScene(AnimScene*);
void deleteAnimScene(AnimScene*);
void addAnim(AnimScene*,Animation*);
void delAnim(AnimScene*,Animation*);
void updateAll(AnimScene*, int, int);
void reset(AnimScene*);
void updatePosition(AnimScene* anim,int time);
Animation* getAnimFromObj(AnimScene* anim,Object* obj);
*/
#endif