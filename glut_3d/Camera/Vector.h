

#ifndef VECTOR_H
#define VECTOR_H

typedef struct _vector3d Vector3D;

struct _vector3d
{
	float x,y,z;
	float length;
};

//CONSTRUTOR / DESTRUCTOR

Vector3D * newVector3D(Vector3D* v,float x, float y, float z);
void deleteVector3D(Vector3D* v);

// OPERATOR

Vector3D vectorAdd(Vector3D v, Vector3D a);
Vector3D vectorSous(Vector3D v, Vector3D a);
Vector3D vectorMutl(Vector3D v,float a);
Vector3D vectorDiv(Vector3D v,float a);
float    vectorScaleProduct(Vector3D v, Vector3D a);
Vector3D vectorCrossProduct(Vector3D v, Vector3D a);

// FUNCTION
void updateLength(Vector3D* v);
Vector3D normalize(Vector3D* v);


#endif