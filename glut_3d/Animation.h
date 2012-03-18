

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



class Animation
{
public:

	struct MoveInfo
	{
	public:
		MoveInfo()
		{
			pos = Vector3D();
			rot = Quat();
			time = -1;
		}
		MoveInfo(Vector3D pos, Quat rot, int time)
		{
			this->pos = pos;
			this->rot = rot;
			this->time = time;
		}
		MoveInfo(Object * obj, int time)
		{
			this->pos = obj->getPosition();
			this->rot = obj->getRotation();
			this->time = time;
		}
		Vector3D pos;
		Quat rot;
		int time;
	};

	Animation(Object* obj);
	void update(int time);
	void addMoveInfo(MoveInfo mi);
	void remMoveInfo(int time);
	bool checkMoveInfo(MoveInfo mv);
	MoveInfo getInterpolateFor(int time);
private:
	std::vector<MoveInfo> mv_list;
	Object* obj;
};

class MoveInfo_compare
{
public:
    bool operator()(const Animation::MoveInfo& a, const Animation::MoveInfo& b)
    {
        return a.time < b.time;
    }
};


/*
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