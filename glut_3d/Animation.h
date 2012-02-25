

#ifndef ANIMATION_H
#define ANIMATION_H
#include "Camera\Vector.h"
#include "MathPlus.h"
#include "Object.h"

enum AnimFlag
{
	ANIMFLAG_NOTHING = 0x00,
	ANIMFLAG_INSTANTLY = 0x01,
};

typedef struct _moveinfo MoveInfo;
typedef struct _animation Animation;
typedef struct _animationscene AnimScene;

struct _moveinfo
{
	Vector3D pos;
	Quat rot;
	int time;
};

struct _animation //time in ms
{
	Object * obj;
	MoveInfo mv_info[256];
	int mv_size;
	int t;
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


Animation* newAnim(Animation*,Object*);
void deleteAnim(Animation*);

void update(Animation*,int);

void addMoveInfo(Animation*,Quat,int time);
void remMoveInfo(Animation*,int time);
void orderMoveInfo(Animation*);
int compareMoveInfo(const void *Param1, const void *Param2);

AnimScene* newAnimScene(AnimScene*);
void deleteAnimScene(AnimScene*);
void addAnim(AnimScene*,Animation*);
void delAnim(AnimScene*,Animation*);
void updateAll(AnimScene*, int, int);
void reset(AnimScene*);

#endif