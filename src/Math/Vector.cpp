#include <math.h>
#include <stdlib.h>
#include "Vector.h"
#include "Matrix.h"


Vector3D::Vector3D() : x(_array[0]),y(_array[1]),z(_array[2])
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}
Vector3D::Vector3D(float x,float y,float z) : x(_array[0]),y(_array[1]),z(_array[2])
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::Vector3D(Vector3D const &a) : x(_array[0]),y(_array[1]),z(_array[2])
{
	x = a.x;
	y = a.y;
	z = a.z;
}

Vector3D Vector3D::operator+(Vector3D const &a)
{
	return Vector3D(x+a.x,y+a.y,z+a.z);
}
Vector3D Vector3D::operator-(Vector3D const &a)
{
	return Vector3D(x-a.x,y-a.y,z-a.z);
}
Vector3D Vector3D::operator*(float a)
{
	return Vector3D(x*a,y*a,z*a);
}
Vector3D Vector3D::operator/(float a)
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
Vector3D Vector3D::operator*=(float a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}
Vector3D Vector3D::operator/=(float a)
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

Vector3D Vector3D::operator=(Vector3D const &a)
{
	memcpy(_array,a._array,sizeof(float)*3);
	return *this;
}

Vector3D Vector3D::crossProduct(Vector3D const &a)
{
    return Vector3D(y*a.z - z*a.y,z*a.x - x*a.z,x*a.y - y*a.x);
}

float Vector3D::scaleProduct(Vector3D const &a)
{
	return x*a.x + y*a.y + z*a.z;
}

void Vector3D::normalise() const
{
	float _length = length();
	x /= _length;
	y /= _length;
	z /= _length;
}

ofstream& operator<<(ofstream &file, Vector3D  v)
{
	file << v.getX() << v.getY() << v.getZ();
	return file;
}

ifstream& operator>>(ifstream &file, Vector3D  v)
{
	float a;
	file >> a;
	v.setX(a);
	file >> a;
	v.setY(a);
	file >> a;
	v.setZ(a);
	return file;
}