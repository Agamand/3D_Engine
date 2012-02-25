
#ifndef OBJECT_H
#define OBJECT_H

#include "Util\List.h"
#include "Texture.h"
#include "Camera\Vector.h"
#include <glut.h>
#include "MathPlus.h"

typedef struct _cube Cube;
typedef struct _point Point;
typedef struct _object Object;
typedef struct _polygone Polygone;
typedef struct _sphere Sphere;
typedef struct _container Container;
typedef struct _3ds Object_3ds;

enum ObjectType
{
	OBJECT_TYPE_POLYGONE,
	OBJECT_TYPE_SPHERE,
	OBJECT_TYPE_CONTAINER,
	OBJECT_TYPE_3DS,
};

struct _point
{
	float x,y,z;
};

struct _cube
{
	Point center;
	int l[3];
	char color[3];
};

struct _object
{
	int type;
	float size;
	char color[3];
	Texture* texture;
	Quat qtrot;
};

struct _polygone
{
	Object obj;
	ListCh * lPoint;
};

struct _sphere
{
	Object obj;
	Point center;
	float r;
};

struct _container
{
	Object obj;
	Point center;
	Point repere;
	ListCh * objectL;
};

struct _3ds
{
	Object obj;
	Point center;
	Point repere;
	float angle[3];
	ListCh * objectL;
};

//struct _pointLinker

// CONSTRUCTOR / DECONSTRUCTOR

Point * newPoint(Point*, float x, float y, float z);
void deletePoint(Point*);
Point* cpyPoint(Point*);


Cube* newCube(Cube *, Point,int*);


Object* cpyObject(Point*);

Polygone * newPolygone(Polygone*, Point*, int);
void deletePolygone(Polygone*);


Sphere* newSphere(Sphere* sph,Point * center, float r, char * texture, int color);
void deleteSphere(Sphere* sph);

Container* newContainer(Container* ct,Point * center, Point * repere);
void deleteContainer(Container* ct);

// FUNCTION

GLuint loadTexture(char *);
void getEulerAngle(double*,double*);
void showrepere();
void render_string(float x, float y, float z, const char* s);

void polyAddPoint(Polygone*,Point*);
void polyDelPoint(Polygone*,Point*);
void showPolygone(Polygone*);

void showSphere(Sphere*);

void contAddObject(Container*,Object*);
void contDelObject(Container*,Object*);
void showContainer(Container*);
void rot(Object*obj,double angle, double x, double y, double z);


void traceCube(Cube*);

#endif