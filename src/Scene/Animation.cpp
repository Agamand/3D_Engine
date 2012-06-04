#include <stdlib.h>
#include "Animation.h"
#include <algorithm>
#include <xfunctional>
#define ABS(x) x > 0.0f ? x : -x
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

bool vectorCompare(glm::vec3 v1, glm::vec3 v2)
{
	glm::vec3 v = v1 - v2;
	if(ABS(v.x) > 0.0005f)
		return false;
	if(ABS(v.y) > 0.0005f)
		return false;
	if(ABS(v.z) > 0.0005f)
		return false;
	return true;
}

bool quatCompare(glm::quat qt1,glm::quat qt2)
{
	if(ABS(qt1.w - qt2.w) > 0.0005f || !vectorCompare(glm::vec3(qt1.x,qt1.y,qt1.z),glm::vec3(qt2.x,qt2.y,qt2.z)))
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
	float t = time - mv_list[index].time;
	t = ((float)t)/((float)inter);
	if(t > 1.0f)
		t = 1.0f;
	MoveInfo mv;
	mv.rot = glm::mix(mv_list[index].rot,mv_list[index+1].rot,t);
	mv.pos = mv_list[index].pos;
	mv.time = time;
	return mv;
}


AnimationBone::AnimationBone(Bone* obj)
{
	this->bone = obj;
	addMoveInfoBone(MoveInfoBone(obj->posBase,obj->rotation,0));
}

void AnimationBone::update(int time)
{
	if(mv_set.size() < 2)
		return;

	MoveInfoBone mv = getInterpolateFor(time);
	bone->posBase = mv.pos;
	bone->rotation = mv.rot;
	bone->updateBoneMatrix();
			
}
void AnimationBone::addMoveInfoBone(MoveInfoBone mi)
{
	//if(!checkMoveInfo(mi))
		//return;

	mv_set[mi.time] = mi;
}

void AnimationBone::remMoveInfoBone(int time)
{
	if(mv_set.empty())
		return;

	mv_set.erase(time);
}	

bool AnimationBone::checkMoveInfoBone(MoveInfoBone mv)
{
	MoveInfoBone _mv;
	if(mv_set.empty())
		return true;

	_mv = getInterpolateFor(mv.time);
	       
	return !(quatCompare(mv.rot,_mv.rot) && vectorCompare(mv.pos,_mv.pos));
}

glm::quat slerp(glm::quat begin, glm::quat end, float t)
{
	float sin1,sin2;
	float a = glm::dot(begin,end);
	if(a > 1.0f)
		a = 1.0f;
	else if(a < -1.0f) 
		a = -1.0f;
	a = acos(a);
	sin1 = sin((1-t)*a)/sin(a);
	sin2 = sin(t*a)/sin(a);
	return (begin*sin1 + end*sin2);
}
AnimationBone::MoveInfoBone AnimationBone::getInterpolateFor(int time)
{
	if(mv_set.size() < 2)
		return (mv_set.begin()->second);


	MoveInfoBone before;
	MoveInfoBone after;	
	std::map<int,MoveInfoBone>::iterator test = mv_set.end();
	test--;
	if(time >= test->first)
	{
		return test->second;
	}

	for(std::map<int,MoveInfoBone>::iterator i = mv_set.begin(); i != mv_set.end(); i++)
	{
		if(time < i->first) 
		{
			after = i->second;
			i--;
			if(i == mv_set.end())
				return after;
			before = (i)->second;
			break;
		}
	}

	int inter = after.time - before.time;
	float t = time - before.time;
	t = ((float)t)/((float)inter);
	if(t > 1.0f)
		t = 1.0f;
	MoveInfoBone mv;
	mv.rot = slerp(before.rot,after.rot,t);
	mv.pos = glm::mix(before.pos,after.pos,t);
	mv.time = time;
	return mv;
}
