#include <stdlib.h>
#include <math.h>
#include "MathPlus.h"
#include "Matrice.h"



Quat* newQuat(Quat* qt, double a, double x, double y, double z)
{
	double sin_a,cos_a;
	if(!qt)
		qt = (Quat*)malloc(sizeof(Quat));

	sin_a = sin(a / 2);
	cos_a = cos(a / 2);

	qt->a = cos_a;
	newVector3D(&qt->vector,x * sin_a,y* sin_a,z* sin_a);
	quatNormalize(qt);
}

void deleteQuat(Quat* qt)
{
	if(!qt)
		return;

	free(qt);
}

Quat quatConj(Quat qt)
{


	newQuat(&qt,qt.a,-qt.vector.x,-qt.vector.y,-qt.vector.z);
	quatNormalize(&qt);
	return qt;
}

double quatNorm(Quat qt)
{

	return sqrt(qt.a*qt.a + qt.vector.length*qt.vector.length);
}
void quatNormalize(Quat* qt)
{
	double norme = quatNorm(*qt);
	if(norme > 0.0f)
		*qt = quatDivD(*qt,norme);
}
Quat quatProdD(Quat qt,double a)
{
	qt.a *= a;
	vectorMutl(qt.vector,a);
	return qt;
}
Quat quatDivD(Quat qt,double a)
{
	qt.a /= a;
	vectorDiv(qt.vector,a);
	return qt;
}
Quat quatInv(Quat qt)
{	
	qt = quatDivD(quatConj(qt),quatNorm(qt)*quatNorm(qt));
	quatNormalize(&qt);
	return qt; 
}
Quat quatProd(Quat qt, Quat a)
{
	Quat qtr;
	Vector3D v;
	qtr.a = qt.a*a.a - vectorScaleProduct(qt.vector,a.vector);
	v = vectorMutl(a.vector,qt.a);
	qtr.vector = v;
	v = vectorMutl(qt.vector,a.a);
	qtr.vector = vectorAdd(qtr.vector,v);
	v = vectorCrossProduct(qt.vector,a.vector);
	qtr.vector = vectorAdd(qtr.vector,v);
	quatNormalize(&qtr);
	return qtr;
}
double quatScaleProd(Quat qt,Quat a)
{
	return qt.a*a.a + qt.vector.x*a.vector.x + qt.vector.y*a.vector.y + qt.vector.z*a.vector.z;
}


Matrice* quatTomatrice(Quat qt)
{
	Matrice* mat;
	

	double xx      = qt.vector.x * qt.vector.x;
	double xy      = qt.vector.x * qt.vector.y;
	double xz      = qt.vector.x * qt.vector.z;
	double xa      = qt.vector.x * qt.a;

	double yy      = qt.vector.y * qt.vector.y;
	double yz      = qt.vector.y * qt.vector.z;
	double ya      = qt.vector.y * qt.a;

	double zz      = qt.vector.z * qt.vector.z;
	double za      = qt.vector.z * qt.a;
	mat = newMatrice(4,4);
	mat->mat[0][0]  = 1 - 2 * ( yy + zz );
	mat->mat[0][1]  =     2 * ( xy - za );
	mat->mat[0][2]  =     2 * ( xz + ya );

	mat->mat[1][0]  =     2 * ( xy + za );
	mat->mat[1][1]  = 1 - 2 * ( xx + zz );
	mat->mat[1][2]  =     2 * ( yz - xa );

	mat->mat[2][0]  =     2 * ( xz - ya );
	mat->mat[2][1]  =     2 * ( yz + xa );
	mat->mat[2][2] = 1 - 2 * ( xx + yy );

	mat->mat[0][3]  = mat->mat[1][3] = mat->mat[2][3] = mat->mat[3][0] = mat->mat[3][1] = mat->mat[3][2] = 0;
	mat->mat[3][3] = 1;
	
	return mat;
}

int max3(double a, double b, double c)
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

Quat matriceToquat(Matrice*mat)
{
	Quat qt;
	double t,s,x,y,z,a;

	if(!mat)
		return ;
	t = matTrace(mat);
	if(t > 0)
	{
		s = 1/( 2 * sqrt(t));
		x = (mat->mat[2][1] - mat->mat[1][2])*s;
		y = (mat->mat[0][2] - mat->mat[2][0])*s;
		z = (mat->mat[1][0] - mat->mat[0][1])*s;
		qt.a =  1/(4*s);
		newVector3D(&qt.vector,x,y,z);
	}
	else
	{
		switch(max3(mat->mat[0][0],mat->mat[1][1],mat->mat[2][2]))
		{
		case 0:
			s = sqrt(1.0f + mat->mat[0][0] - mat->mat[1][1] - mat->mat[2][2]);
			x = 1/(2*s);
			y = (mat->mat[0][1] + mat->mat[1][0])/s;
			z = (mat->mat[0][2] + mat->mat[2][0])/s;
			qt.a = (mat->mat[1][2] + mat->mat[2][1])/s;
			break;
		case 1:
			s = sqrt(1.0f - mat->mat[0][0] + mat->mat[1][1] - mat->mat[2][2]);
			x = (mat->mat[0][1] + mat->mat[1][0])/s;
			y = 1/(2*s);
			z = (mat->mat[0][2] + mat->mat[2][0])/s;
			qt.a = (mat->mat[1][2] + mat->mat[2][1])/s;
			break;
		case 2:
			s = sqrt(1.0f - mat->mat[0][0] - mat->mat[1][1] + mat->mat[2][2]);
			
			x = (mat->mat[0][2] + mat->mat[2][0])/s;
			y = (mat->mat[1][2] + mat->mat[2][1])/s;
			z = 1/(2*s);
			qt.a = (mat->mat[0][1] + mat->mat[1][0])/s;
			break;
		}
		newVector3D(&qt.vector,x,y,z);
	}
	quatNormalize(&qt);
	return qt;
}

Quat toRot(Quat qt)
{

	quatNormalize(&qt);

	qt.a = acos(qt.a) * 2;

	qt.vector = normalize(&qt.vector);
	return qt;
}