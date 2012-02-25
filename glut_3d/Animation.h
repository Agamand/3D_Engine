

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
	//Start
	Vector3D start_pos;
	Quat start_rot;

	//After
	Vector3D end_pos;
	Quat end_rot;
};

struct _animation //time in ms
{
	Object * obj;
	MoveInfo mv_info;
	int start_time; 
	int time, t;
	void (*update)(Animation*,int);

};

struct _animationscene
{
	ListCh* l_anim;
	int t;
	int start;
	void(*update)(AnimScene*,int);
	void (*reset)(AnimScene*);
};


Animation* newAnim(Animation*,Object*);
void deleteAnim(Animation*);

void update(Animation*,int);

void setStart(Animation*,Quat);
void setEnd(Animation*, Quat);


AnimScene* newAnimScene(AnimScene*);
void deleteAnimScene(AnimScene*);
void addAnim(AnimScene*,Animation*);
void delAnim(AnimScene*,Animation*);
void updateAll(AnimScene*, int);
void reset(AnimScene*);

#endif