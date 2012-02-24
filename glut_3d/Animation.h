#include "Camera\Vector.h"
#include "Object.h"

enum AnimFlag
{
	ANIMFLAG_NOTHING = 0x00,
	ANIMFLAG_INSTANTLY = 0x01,
};

struct _moveinfo
{
	//Start
	Vector3D start_pos;
	float start_rotAngle[3];
	Vector3D start_rotDir[3];

	//After

	Vector3D end_pos;
	float end_rotAngle[3];
	Vector3D end_rotDir[3];
};

struct _animation
{
	Object * obj;

};