

#ifndef ANIMATION_H
#define ANIMATION_H

#include "../Object/Object.h"
#include "../Bone.h"
#include <map>
#include <set>


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
			pos = glm::vec3();
			rot = glm::quat();
			time = -1;
		}
		MoveInfo(glm::vec3 pos, glm::quat rot, int time)
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
		glm::vec3 pos;
		glm::quat rot;
		int time;
		bool operator<(const MoveInfo &a)
		{
			return this->time < a.time;
		}
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


class AnimationBone
{
public:
	struct MoveInfoBone
	{
	public:
		MoveInfoBone(int time = -1)
		{
			pos = glm::vec3();
			rot = glm::quat();
			time = time;
		}
		MoveInfoBone(glm::vec3 pos, glm::quat rot, int time)
		{
			this->pos = pos;
			this->rot = rot;
			this->time = time;
		}
		MoveInfoBone(Bone * _bone, int time)
		{
			this->pos = _bone->posBase;
			this->rot = _bone->rotation;
			this->time = time;
		}
		glm::vec3 pos;
		glm::quat rot;
		int time;
		bool operator<(const MoveInfoBone &a)
		{
			return this->time < a.time;
		}
		bool operator==(const MoveInfoBone &a)
		{
			return this->time == a.time;
		}
		bool operator>(const MoveInfoBone &a)
		{
			return this->time > a.time;
		}
		bool operator<(const int t)
		{
			return this->time < t;
		}
		bool operator==(const int t)
		{
			return this->time == t;
		}
		bool operator>(const int t)
		{
			return this->time > t;
		}
	};

	AnimationBone(Bone *_bone);
	void update(int time);
	void addMoveInfoBone(MoveInfoBone mi);
	void remMoveInfoBone(int time);
	bool checkMoveInfoBone(MoveInfoBone mv);
	MoveInfoBone getInterpolateFor(int time);
private:
	std::map<int,MoveInfoBone> mv_set;
	Bone* bone;
};

class MoveInfo_compare
{
public:
    bool operator()(const Animation::MoveInfo& a, const Animation::MoveInfo& b)
    {
        return a.time < b.time;
    }
};

#endif