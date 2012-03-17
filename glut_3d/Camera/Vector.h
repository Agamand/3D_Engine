

#ifndef VECTOR_H
#define VECTOR_H

class Vector3D
{
public:
	Vector3D();
	Vector3D(double x,double y,double z);
	Vector3D(Vector3D const &a);
	~Vector3D() {;}

	void setX(double x) { this->x = x; }
	double getX() { return x; }
	void setY(double y) { this->y = y; }
	double getY() { return y; }
	void setZ(double z) { this->z = z; }
	double getZ() { return z; }
	double getLength() { updateLength(); return length; }

	Vector3D operator+(Vector3D const &a);
	Vector3D operator-(Vector3D const &a);
	Vector3D operator*(double a);
	Vector3D operator/(double a);
	Vector3D operator+=(Vector3D const &a);
	Vector3D operator-=(Vector3D const &a);
	Vector3D operator*=(double a);
	Vector3D operator/=(double a);
	bool operator==(Vector3D const &a);
	//Vector3D operator=(Vector3D &const a);
	double scaleProduct(Vector3D const &a);
	Vector3D crossProduct(Vector3D const &a);
	void updateLength();
	void normalise();
private:
	double x,y,z;
	double length;
};

#endif
