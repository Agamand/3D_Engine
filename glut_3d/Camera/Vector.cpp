#include <math.h>
#include <stdlib.h>
#include "Vector.h"


Vector3D::Vector3D()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	length = 0.0f;
}
Vector3D::Vector3D(double x,double y,double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	updateLength();
}

Vector3D::Vector3D(Vector3D const &a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	updateLength();
}

Vector3D Vector3D::operator+(Vector3D const &a)
{
	return Vector3D(x+a.x,y+a.y,z+a.z);
}
Vector3D Vector3D::operator-(Vector3D const &a)
{
	return Vector3D(x-a.x,y-a.y,z-a.z);
}
Vector3D Vector3D::operator*(double a)
{
	return Vector3D(x*a,y*a,z*a);
}
Vector3D Vector3D::operator/(double a)
{
	if(a!= 0.0f)
		return Vector3D(x/a,y/a,z/a);
	return *this;
}

Vector3D Vector3D::operator+=(Vector3D const &a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	return *this;
}
Vector3D Vector3D::operator-=(Vector3D const &a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	return *this;
}
Vector3D Vector3D::operator*=(double a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}
Vector3D Vector3D::operator/=(double a)
{
	x /= a;
	y /= a;
	z /= a;
	return *this;
}

bool Vector3D::operator==(Vector3D const &a)
{
	if(x != a.x)
		return false;

	if(y != a.y)
		return false;

	if(z != a.z)
		return false;

	return true;
}

Vector3D Vector3D::crossProduct(Vector3D const &a)
{
    return Vector3D(y*a.z - z*a.y,z*a.x - x*a.z,x*a.y - y*a.x);
}

double Vector3D::scaleProduct(Vector3D const &a)
{
	return x*a.x + y*a.y + z*a.z;
}

void Vector3D::updateLength()
{
	length = x*x + y*y + z*z;
	length = sqrt(length);
}
void Vector3D::normalise()
{
	updateLength();

	if(length == 0.0f)
		return;

	x /= length;
	y /= length;
	z /= length;
	updateLength();
}