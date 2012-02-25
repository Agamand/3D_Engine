#include <stdlib.h>
#include "Animation.h"


Animation* newAnim(Animation* anim,Object* obj)
{
	if(!anim)
		anim = (Animation*)malloc(sizeof(Animation));

	anim->obj = obj;
	anim->start_time = 0;
	anim->t = 0;
	anim->time = 10000;
	//anim->start = start;
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

	anim->t += value;

	if(anim->t > anim->time)
		anim->t = anim->time;

	if(anim->t <= anim->time)
	{


		t = ((double)anim->t)/((double)anim->time);
		qt = interpolQuat(anim->mv_info.start_rot,anim->mv_info.end_rot,t);
		anim->obj->qtrot = qt;
	}
	
}
//void start(Animation* anim);
void setStart(Animation* anim, Quat qt)
{
	anim->mv_info.start_rot = qt;
}
void setEnd(Animation* anim, Quat qt)
{
	anim->mv_info.end_rot = qt;
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
void updateAll(AnimScene* anim, int diff)
{
	Pointer* itr;
	Animation* an;
	if(!anim->start)
		return;
	anim->t += diff;
	itr = anim->l_anim->begin;
	while((itr = itr->nextpointer) != anim->l_anim->end)
	{
		an = (Animation*)itr->pointer;
		if(an->start_time > anim->t || an->t == an->time)
			continue;

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