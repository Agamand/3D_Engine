#include <stdlib.h>
#include "Animation.h"


Animation* newAnim(Animation* anim,Object* obj)
{
	int i;
	if(!anim)
		anim = (Animation*)malloc(sizeof(Animation));

	anim->obj = obj;
	anim->t = 0;
	anim->mv_size = 0;
	for(i = 0; i < 256; i++)
		anim->mv_info[i].time = -1;

	initAnim(anim);
	return anim;
}

void initAnim(Animation* anim)
{
	anim->update = update;
}
void deleteAnim(Animation* anim)
{
	free(anim);
}

void update(Animation* anim,int value)
{
	Quat qt;
	double t;
	int i;
	int time;
	anim->t += value;

	if(anim->mv_size < 2)
		return;

	for(i = 0; i < anim->mv_size-1; i++)
	{
		if(anim->t >= anim->mv_info[i].time && anim->t <= anim->mv_info[i+1].time)
			break;

		if(i+1 == anim->mv_size-1)
			break;
	}
	time = anim->mv_info[i+1].time - anim->mv_info[i].time;
	t = anim->t - anim->mv_info[i].time;
	t = ((double)t)/((double)time);
	if(t > 1.0f)
		t = 1.0f;
	qt = interpolQuat(anim->mv_info[i].rot,anim->mv_info[i+1].rot,t);
	anim->obj->qtrot = qt;
	
}
Quat getInterpolateFor(Animation* anim, int time)
{
	Quat qt;
	double t;
	int i;
	int animtime;

	if(anim->mv_size == 1)
		return anim->mv_info[0].rot;
	for(i = 0; i < anim->mv_size-1; i++)
	{
		if(anim->t >= anim->mv_info[i].time && anim->t <= anim->mv_info[i+1].time)
			break;

		if(i+1 == anim->mv_size-1)
			break;
	}
	animtime = anim->mv_info[i+1].time - anim->mv_info[i].time;
	t = time - anim->mv_info[i].time;
	t = ((double)t)/((double)animtime);
	if(t > 1.0f)
		t = 1.0f;
	qt = interpolQuat(anim->mv_info[i].rot,anim->mv_info[i+1].rot,t);
	return qt;
}
int quatCompare(Quat qt1,Quat qt2)
{
	double a,x,y,z;
	a = qt1.vector.x-qt2.vector.x;
	x = qt1.vector.x-qt2.vector.x;
	y = qt1.vector.y-qt2.vector.y;
	z = qt1.vector.z-qt2.vector.z;

	a = a < 0 ? -a : a;
	x = x < 0 ? -x : x;
	y = y < 0 ? -y : y;
	z = z < 0 ? -z : z;
	if(a > 0.0005f)
		return 0;
	if(x > 0.0005f)
		return 0;
	if(y > 0.0005f)
		return 0;
	if(z > 0.0005f)
		return 0;

	return 1;
}
int checkAnim(Animation* anim,Quat qt, int time)
{
	Quat _qt;
	if(!anim->mv_size)
		return 1;

	_qt = getInterpolateFor(anim,time);

	return !quatCompare(qt,_qt);
}
void addMoveInfo(Animation* anim,Quat qt,int time)
{
	if(anim->mv_size >= 256)
		return;
	
	if(!checkAnim(anim,qt,time))
		return;

	remMoveInfo(anim,time);
	anim->mv_info[anim->mv_size].rot = qt;
	anim->mv_info[anim->mv_size].time = time;
	
	anim->mv_size++;
	orderMoveInfo(anim);
}
void updatePosition(AnimScene* anim,int time)
{
	Pointer* itr;
	Animation* an;
	if(anim->start)
		return;

	itr = anim->l_anim->begin;
	while((itr = itr->nextpointer) != anim->l_anim->end)
	{
		an = (Animation*)itr->pointer;

		addMoveInfo(an,an->obj->qtrot,time);
	}
}
void remMoveInfo(Animation*anim,int time)
{
	int i;
	if(anim->mv_size <= 0)
		return;

	for(i = 0; i < anim->mv_size; i++)
	{
		if(anim->mv_info[i].time == time)
		{
			anim->mv_info[i].time = -1;
			anim->mv_size--;
			break;
		}
	}
	orderMoveInfo(anim);
	
}

void orderMoveInfo(Animation*anim)
{
	qsort(&anim->mv_info,anim->mv_size,sizeof(MoveInfo),compareMoveInfo);
}
int compareMoveInfo(const void *Param1, const void *Param2)
{
	MoveInfo *mv1, *mv2;
	mv1 = (MoveInfo*)Param1;
	mv2 = (MoveInfo*)Param2;
	if(mv1->time != mv2->time && mv1->time < 0)
		return 1;

	if(mv1->time > mv2->time)
		return 1;
	else if(mv1->time < mv2->time)
		return -1;
	else return 0;
}


AnimScene* newAnimScene(AnimScene* anim)
{
	if(!anim)
		anim = (AnimScene*)malloc(sizeof(AnimScene));

	anim->l_anim = newListCh();
	anim->t = 0;
	anim->start = 0;
	anim->reset = reset;
	anim->update = updateAll;
	return anim;
}
void deleteAnimScene(AnimScene* anim)
{
	deleteListCh(anim->l_anim);
	free(anim);
}
void addAnim(AnimScene*anim,Animation* an)
{
	anim->l_anim->Append(anim->l_anim,an);
}
void delAnim(AnimScene*anim,Animation* an)
{
	anim->l_anim->Erase(anim->l_anim,an);
}
void updateAll(AnimScene* anim, int diff, int forceupdate)
{
	Pointer* itr;
	Animation* an;
	if(!anim->start && !forceupdate)
		return;
	anim->t += diff;
	itr = anim->l_anim->begin;
	while((itr = itr->nextpointer) != anim->l_anim->end)
	{
		an = (Animation*)itr->pointer;

		an->update(an,diff);
	}
}

void reset(AnimScene* anim)
{
	Pointer* itr;
	Animation* an;
	anim->start = 0;
	anim->t = 0;
	itr = anim->l_anim->begin;
	while((itr = itr->nextpointer) != anim->l_anim->end)
	{
		an = (Animation*)itr->pointer;
		an->t = 0;
		an->update(an,anim->t);
	}
}

Animation* getAnimFromObj(AnimScene* anim,Object* obj)
{
	Animation* an = NULL;
	Pointer *itr, *end;

	itr = anim->l_anim->begin;
	end = anim->l_anim->end;

	while((itr = itr->nextpointer) != end)
	{
		an = (Animation*)itr->pointer;
		if(an->obj == obj)
			return an;
	}
	return NULL;
}