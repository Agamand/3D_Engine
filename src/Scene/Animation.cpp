#include <stdlib.h>
#include "Animation.h"
#include <algorithm>
Animation::Animation(Object* obj)
{
	this->obj = obj;
	addMoveInfo(MoveInfo(obj->getPosition(),obj->getRotation(),0));
}

void Animation::update(int time)
{
	if(mv_list.size() < 2)
		return;

	MoveInfo mv = getInterpolateFor(time);
	obj->setPosition(mv.pos);
	obj->setRotation(mv.rot);
			
}
void Animation::addMoveInfo(MoveInfo mi)
{
	if(!checkMoveInfo(mi))
		return;

	remMoveInfo(mi.time);

	mv_list.push_back(mi);
	std::sort (mv_list.begin(),mv_list.end(),MoveInfo_compare());
}
void Animation::remMoveInfo(int time)
{
	if(mv_list.empty())
		return;

	for(std::size_t i = 0; i < mv_list.size();)
	{
		if(mv_list[i].time == time)
		{
			mv_list.erase(mv_list.begin()+i);
		}
		else
		{
			i++;
		}
	}
}	

bool vectorCompare(Vector3D v1, Vector3D v2)
{
	Vector3D v = v1 - v2;
	if(ABS(v.getX()) > 0.0005f)
		return false;
	if(ABS(v.getY()) > 0.0005f)
		return false;
	if(ABS(v.getZ()) > 0.0005f)
		return false;
	return true;
}

bool quatCompare(Quat qt1,Quat qt2)
{
	Quat qt = qt1 - qt2;
	if(ABS(qt.getA()) > 0.0005f || !vectorCompare(qt1.getVector(),qt2.getVector()))
		return false;
	return true;
}

bool Animation::checkMoveInfo(MoveInfo mv)
{
	MoveInfo _mv;
	if(mv_list.empty())
		return true;

	_mv = getInterpolateFor(mv.time);
	       
	return !(quatCompare(mv.rot,_mv.rot) && vectorCompare(mv.pos,_mv.pos));
}
Animation::MoveInfo Animation::getInterpolateFor(int time)
{
	if(mv_list.size() < 2)
		return mv_list[0];

	int index = 0;
	for(std::size_t i = 0; i < mv_list.size(); i++)
	{
		if(time >= mv_list[i].time && time <= mv_list[i+1].time || i+1 == mv_list.size()-1)
		{
			index = i;
			break;
		}			
	}

	int inter = mv_list[index+1].time - mv_list[index].time;
	double t = time - mv_list[index].time;
	t = ((double)t)/((double)inter);
	if(t > 1.0f)
		t = 1.0f;
	MoveInfo mv;
	mv.rot = mv_list[index].rot.interpolate(mv_list[index+1].rot,t);
	mv.pos = mv_list[index].pos;
	mv.time = time;
	return mv;
}
/*
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
}*/