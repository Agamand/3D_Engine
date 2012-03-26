



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
	Rot(double _a, Vector3D _v) 
	{ a = _a; v = _v; v.normalise();}
	double a;
	Vector3D v;
};

class Quat
{
public:
	Quat();
	Quat(double a, Vector3D v);
	Quat(Quat const &qt);
	Quat(Matrix m);
	~Quat() {;}
	Quat operator+(Quat const &a);
	Quat operator-(Quat const &a);
	Quat operator*(Quat const &a);
	Quat operator*(double const &a);
	Quat operator/(double const &a);
	Quat operator+=(Quat const &a);
	Quat operator-=(Quat const &a);
	Quat operator*=(Quat const &a);
	Quat operator*=(double const &a);
	Quat operator/=(double const &a);

	double ScaleProd(Quat q);
	Quat inv();	
	Quat conj();
	Matrix toMatrix();
	Quat interpolate(Quat q, double t);
	void normalise();
	Rot toRot();
	double norm();

	void setA(double a) { this->a = a; }
	double getA() { return a; }
	void setVector(Vector3D v) { vect = v; }
	Vector3D getVector() { return vect; }
private:
	double a;
	Vector3D vect;
};



int max3(double a, double b, double c);


#endif