



#ifndef MATHPLUS_H
#define MATHPLUS_H
#define _USE_MATH_DEFINES


#include <math.h>
#include "Vector.h"
#include "Matrix.h"
#define TODEG 180/M_PI
#define TORAD M_PI/180
#define ABS(x) x > 0.0f ? x : -x
// Quaternion

#define TOROT(qt) qt.a*TODEG, qt.v.getX(), qt.v.getY(), qt.v.getZ()


struct Rot
{
	Rot(float _a, Vector3D _v) 
	{ a = _a; v = _v; v.normalise();}
	float a;
	Vector3D v;
};

class Quat
{
public:
	Quat();
	Quat(float a, Vector3D v);
	Quat(Quat const &qt);
	Quat(Matrix4 m);
	~Quat() {;}
	Quat operator+(Quat const &a);
	Quat operator-(Quat const &a);
	Quat operator*(Quat const &a);
	Quat operator*(float const &a);
	Quat operator/(float const &a);
	Quat operator+=(Quat const &a);
	Quat operator-=(Quat const &a);
	Quat operator*=(Quat const &a);
	Quat operator*=(float const &a);
	Quat operator/=(float const &a);

	float ScaleProd(Quat q);
	Quat inv();	
	Quat conj();
	Matrix4 toMatrix();
	Quat interpolate(Quat q, float t);
	void normalise();
	Rot toRot();
	float norm();
	bool isNull() { return a == 0.0f || vect.isNull();}
	Vector3D rotatePoint(Vector3D v);

	void setA(float a) { this->a = a; }
	float getA() { return a; }
	void setVector(Vector3D v) { vect = v; }
	Vector3D getVector() { return vect; }
private:
	float a;
	Vector3D vect;
};



int max3(float a, float b, float c);

ofstream& operator<<(ofstream &file, Quat q);

ifstream& operator>>(ifstream &file, Quat q);

#endif