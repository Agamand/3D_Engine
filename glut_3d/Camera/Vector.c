#include <math.h>
#include <stdlib.h>
#include "Vector.h"



//CONSTRUTOR / DESTRUCTOR

Vector3D * newVector3D(Vector3D* v,float x, float y, float z)
{
	if(!v)
		v = (Vector3D*)malloc(sizeof(Vector3D));

	v->x = x;
	v->y = y;
	v->z = z;
	updateLength(v);
	return v;
}

void deleteVector3D(Vector3D* v)
{
	free(v);
}

// OPERATOR

Vector3D vectorAdd(Vector3D v, Vector3D a)
{
	Vector3D r;
	r.x = v.x + a.x;
	r.y = v.y + a.y;
	r.z = v.z + a.z;
	updateLength(&r);
	return r;
}
Vector3D vectorSous(Vector3D v, Vector3D a)
{
	Vector3D r;
	r.x = v.x - a.x;
	r.y = v.y - a.y;
	r.z = v.z - a.z;
	updateLength(&r);
	return r;
}
Vector3D vectorMutl(Vector3D v,float a)
{
	Vector3D r;
	r.x = v.x*a;
	r.y = v.y*a;
	r.z = v.z*a;
	updateLength(&r);
	return r;
}
Vector3D vectorDiv(Vector3D v,float a)
{
	Vector3D r;
	r.x = v.x/a;
	r.y = v.y/a;
	r.z = v.z/a;
	updateLength(&r);
	return r;
}

Vector3D vectorCrossProduct(Vector3D v, Vector3D a)
{
    Vector3D r;
    r.x = v.y*a.z - v.z*a.y;
    r.y = v.z*a.x - v.x*a.z;
    r.z = v.x*a.y - v.y*a.x;
	updateLength(&r);
    return r;
}

// FUNCTION

void updateLength(Vector3D* v)
{
	v->length = v->x*v->x + v->y*v->y + v->z*v->z;
	v->length = sqrtf(v->length);

}
Vector3D normalize(Vector3D* v)
{
	Vector3D nv;
	updateLength(v);

	nv = *v;
	if(nv.length == 0.0f)
		return nv;
	nv.x /= nv.length;
	nv.y /= nv.length;
	nv.z /= nv.length;
	return nv;
}

float vectorScaleProduct(Vector3D v, Vector3D a)
{
	float result = 0.0f;
	result = v.x*a.x + v.y*a.y + v.z*a.z;
	return result;
}