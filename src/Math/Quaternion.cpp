#include <stdlib.h>
#include <math.h>
#include "Quaternion.h"


Quat::Quat()
{
	a = 1;
	vect = glm::vec3(0.0f,0.0f,0.0f);
}

Quat::Quat(float a, glm::vec3 v)
{
	float sin_a,cos_a;
	sin_a = sin(a / 2);
	cos_a = cos(a / 2);

	this->a = cos_a;
	vect = glm::vec3(v);
	vect *= sin_a;
	normalise();
}

Quat::Quat(Quat const &qt)
{
	a = qt.a;
	vect = glm::vec3(qt.vect);
}

Quat::Quat(Matrix4 m)
{
	float t,s,x,y,z,a;
	t = m.trace();

	if(t > 0)
	{
		s = 1/( 2 * sqrt(t));
		x = (m[2][1] - m[1][2])*s;
		y = (m[0][2] - m[2][0])*s;
		z = (m[1][0] - m[0][1])*s;
		a =  1/(4*s);
		vect = glm::vec3(x,y,z);
	}
	else
	{
		switch(max3(m[0][0],m[1][1],m[2][2]))
		{
		case 0:
			s = sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]);
			x = 1/(2*s);
			y = (m[0][1] + m[1][0])/s;
			z = (m[0][2] + m[2][0])/s;
			a = (m[1][2] + m[2][1])/s;
			break;
		case 1:
			s = sqrt(1.0f - m[0][0] + m[1][1] - m[2][2]);
			x = (m[0][1] + m[1][0])/s;
			y = 1/(2*s);
			z = (m[0][2] + m[2][0])/s;
			a = (m[1][2] + m[2][1])/s;
			break;
		case 2:
			s = sqrt(1.0f - m[0][0] - m[1][1] + m[2][2]);
			x = (m[0][2] + m[2][0])/s;
			y = (m[1][2] + m[2][1])/s;
			z = 1/(2*s);
			a = (m[0][1] + m[1][0])/s;
			break;
		}
		vect = glm::vec3(x,y,z);
	}
	normalise();
}

Quat Quat::operator+(Quat const &a)
{
	Quat q(*this);
	q += a;
	return q;
}

Quat Quat::operator-(Quat const &a)
{
	Quat q(*this);
	q -= a;
	return q;
}

Quat Quat::operator*(Quat const &a)
{
	Quat q(*this);
	q *= a;
	return q;
}

Quat Quat::operator*(float const &a)
{
	Quat q(*this);
	q *= a;
	return q;
}

Quat Quat::operator/(float const &a)
{
	Quat q(*this);
	q /= a;
	return q;
}

Quat Quat::operator+=(Quat const &a)
{
	this->a += a.a;
	this->vect += a.vect;
	return *this;
}

Quat Quat::operator-=(Quat const &a)
{
	this->a -= a.a;
	this->vect -= a.vect;
	return *this;
}
Quat Quat::operator*=(Quat const &a)
{
	Quat qt(*this);
	glm::vec3 v;
	this->a = qt.getA()*a.a - qt.getVector().scaleProduct(a.vect);
	vect = a.vect;
	vect *= qt.getA();
	vect += (qt.getVector()*a.a) + (qt.getVector().crossProduct(a.vect));
	return *this;
}

Quat Quat::operator*=(float const &a)
{
	this->a *= a;
	this->vect *=a;
	return *this;
}

Quat Quat::operator/=(float const &a)
{
	if(a == 0.0f)
		return *this;
	this->a /= a;
	this->vect /=a;
	return *this;
}

float Quat::ScaleProd(Quat q)
{
	normalise();
	q.normalise();
	return a*q.getA() + vect.scaleProduct(q.getVector());
}

Quat Quat::inv()
{
	float norm_2;
	Quat qt(conj());
	norm_2 = norm()*norm();
	qt /= norm_2;
	normalise();
	return qt;
}

Quat Quat::conj()
{
	Quat q(*this);
	q.getVector().setX(-vect.getX());
	q.getVector().setY(-vect.getY());
	q.getVector().setZ(-vect.getZ());
	return q;
}

Matrix4 Quat::toMatrix()
{
	normalise();
	Matrix4 mat;

	float xx      = vect.getX() * vect.getX();
	float xy      = vect.getX() * vect.getY();
	float xz      = vect.getX() * vect.getZ();
	float xa      = vect.getX() * a;

	float yy      = vect.getY() * vect.getY();
	float yz      = vect.getY() * vect.getZ();
	float ya      = vect.getY() * a;

	float zz      = vect.getZ() * vect.getZ();
	float za      = vect.getZ() * a;

	mat[0][0]  = 1 - 2 * ( yy + zz );
	mat[0][1]  =     2 * ( xy - za );
	mat[0][2]  =     2 * ( xz + ya );

	mat[1][0]  =     2 * ( xy + za );
	mat[1][1]  = 1 - 2 * ( xx + zz );
	mat[1][2]  =     2 * ( yz - xa );

	mat[2][0]  =     2 * ( xz - ya );
	mat[2][1]  =     2 * ( yz + xa );
	mat[2][2] = 1 - 2 * ( xx + yy );

	mat[0][3]  = mat[1][3] = mat[2][3] = mat[3][0] = mat[3][1] = mat[3][2] = 0;
	mat[3][3] = 1;
	
	return mat;
}

Quat Quat::interpolate(Quat q, float t)
{
	float sin1,sin2;
	float a = ScaleProd(q);
	if(a > 1.0f)
		a = 1.0f;
	else if(a < -1.0f)
		a = -1.0f;
	a = acos(a);
	sin1 = sin((1-t)*a)/sin(a);
	sin2 = sin(t*a)/sin(a);
	return (*this*sin1 + q*sin2);
}

void Quat::normalise()
{
	float norme = norm();
	if(norme > 0.0f)
		*this /= norme;
}

Rot Quat::toRot()
{
	normalise();
	return Rot(acos(a) * 2,vect);
}

float Quat::norm()
{
	return sqrt(a*a + vect.length()*vect.length());
}

glm::vec3 Quat::rotatePoint(glm::vec3 v)
{
	Matrix4 m = toMatrix();
	return m*v;
}

int max3(float a, float b, float c)
{
	if(a >= b)
	{
		if( a >= c)
			return 0;
		else return 2;
	}
	else
	{
		if(b >= c)
			return 1;
		else 
			return 2;
	}
}

ofstream& operator<<(ofstream &file, Quat q)
{
	file << q.getA();
	file << q.getVector();
	return file;
}

ifstream& operator>>(ifstream &file, Quat q)
{
	float a;
	glm::vec3 v;
	file >> a;
	q.setA(a);
	file >> v;
	q.setVector(v);
	return file;
}