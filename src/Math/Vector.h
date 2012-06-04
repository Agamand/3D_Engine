

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

class Matrix4;

class Vector3D
{
public:
	Vector3D();
	Vector3D(float x,float y,float z);
	Vector3D(Vector3D const &a);
	~Vector3D() {;}

	void setX(float x) { this->x = x; }
	float getX() { return x; }
	void setY(float y) { this->y = y; }
	float getY() { return y; }
	void setZ(float z) { this->z = z; }
	float getZ() { return z; }
	inline float magnitude() const 
	{
		return ::sqrtf(x*x + y*y + z*z);
	}

	inline float length() const
	{
		return magnitude();
	}

	Vector3D operator+(Vector3D const &a);
	Vector3D operator-(Vector3D const &a);
	Vector3D operator*(float a);
	Vector3D operator/(float a);
	Vector3D operator+=(Vector3D const &a);
	Vector3D operator-=(Vector3D const &a);
	Vector3D operator*=(float a);
	Vector3D operator/=(float a);
	Vector3D operator=(Vector3D const &a);
	inline const float operator[](int i) const
	{
		assert(i >= 0);
		assert(i < 3);
		return _array[i];
	}
	inline float operator[](int i)
	{
		assert(i >= 0);
		assert(i < 3);
		return _array[i];
	}
	bool operator==(Vector3D const &a);
	//Vector3D operator=(Vector3D &const a);
	float scaleProduct(Vector3D const &a);
	Vector3D crossProduct(Vector3D const &a);
	void normalise() const;
	bool isNull() { return x == 0 && y == 0 && z == 0;}

private:
	float &x,&y,&z;
	float _array[3];
};

ofstream& operator<<(ofstream &file, Vector3D  v);

ifstream& operator>>(ifstream &file, Vector3D  v);
#endif
