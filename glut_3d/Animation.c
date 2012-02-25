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
	anim->update = update;
	for(i = 0; i < 256; i++)
		anim->mv_info[i].time = -1;

	return anim;
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

void addMoveInfo(Animation* anim,Quat qt,int time)
{
	if(anim->mv_size >= 256)
		return;

	anim->mv_info[anim->mv_size].rot = qt;
	anim->mv_info[anim->mv_size].time = time;
	
	anim->mv_size++;
	orderMoveInfo(anim);
}
void remMoveInfo(Animation*anim,int time)
{
	int i;
	if(anim->mv_size <= 0)
		return;

	for(i = 0; i < anim->mv_size; i++)
	{
		if(anim->mv_info[anim->mv_size].time == time)
		{
			anim->mv_info[anim->mv_size].time = -1;
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