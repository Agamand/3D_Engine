



#ifndef MATHPLUS_H
#define MATHPLUS_H
#define _USE_MATH_DEFINES
#include <math.h>
#include "Camera\Vector.h"
#include "Matrice.h"
#define TODEG 180/M_PI
#define TORAD M_PI/180
// Quaternion

#define TOROT(qt) qt.a*TODEG, qt.vector.x, qt.vector.y, qt.vector.z

typedef struct _quat
{
	double a;
	Vector3D vector;
	
}Quat;


Quat* newQuat(Quat*,double,double,double,double);
void deleteQuat(Quat*);

Quat quatConj(Quat);
double quatNorm(Quat);
void quatNormalize(Quat*);
Quat quatInv(Quat);
Quat quatProd(Quat,Quat);
Quat quatProdD(Quat,double);
Quat quatDivD(Quat,double);
double quatScaleProd(Quat,Quat);
Matrice* quatTomatrice(Quat);
Quat matriceToquat(Matrice*);
Quat toRot(Quat);


#endif