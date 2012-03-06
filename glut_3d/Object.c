
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Object.h"
#include "BMPloader.h"
#include "ObjectAccessor\ObjectAccessor.h"
#include "Matrice.h"



Cube* newCube(Cube * cube, Point p,int l[])
{
	int i;
	if(!cube)
		cube = (Cube*)malloc(sizeof(Cube));

	cube->center = p;
	for(i = 0; i < 3;i++)
		cube->l[i] = l[i];
	for(i = 0; i < 3;i++)
		cube->color[i] = 120;
}

Point * newPoint(Point* pt, float x, float y, float z)
{
	if(!pt)
		pt = (Point*)malloc(sizeof(Point));
	pt->x = x;
	pt->y = y;
	pt->z = z;
	return pt;
}
void deletePoint(Point* pt)
{
	free(pt);
}

Point * cpy(Point* pt)
{
	Point* npt;
	npt = newPoint(NULL,0,0,0);
	memcpy(npt,pt,sizeof(Point));
	return npt;
}



Polygone * newPolygone(Polygone* poly, Point* firstPoint, int color)
{
	int i;

	if(!poly)
		poly = (Polygone*)malloc(sizeof(Polygone));

	for(i = 0; i < 4; i++)
		poly->obj.color[i] = ((char*)&color)[i];

	poly->obj.type = OBJECT_TYPE_POLYGONE;
	poly->obj.size = 1.0f;

	poly->lPoint = newListCh();
	if(firstPoint)
		poly->lPoint->Append(poly->lPoint,firstPoint);
	return poly;
}


Container* newContainer(Container* ct,Point * center, Point * repere)
{
	int i;
	Animation* anim;
	if(!ct)
		ct = (Container*)malloc(sizeof(Container));

	for(i = 0; i < 4; i++)
		ct->obj.color[i] = 255;
	ct->obj.size = 1.0f;
	ct->obj.texture = NULL;
	ct->obj.type = OBJECT_TYPE_CONTAINER;
	ct->objectL = newListCh();
	ct->center = *center;
	ct->repere = *repere;
	newQuat(&ct->obj.qtrot,0.0f,0.0,0.0,0.0);
	anim = newAnim(NULL,ct);
	addMoveInfo(anim,ct->obj.qtrot,0);
	addAnim(Objmgr->scene->anim,anim);
	return ct;
}

void deleteContainer(Container* ct)
{
	deleteListCh(ct->objectL);
	free(ct);
}

void deletePolygone(Polygone* poly)
{
	Pointer * pt, *begin;
	begin = poly->lPoint->begin;
	while(poly->lPoint->size != 0)
	{
		pt = begin->nextpointer;
		deletePoint((Point*)pt->pointer);
		free(pt);
	}
	deleteListCh(poly->lPoint);
	free(poly);
}

void polyAddPoint(Polygone* poly,Point * pt)
{
	poly->lPoint->Append(poly->lPoint,pt);
}

void polyDelPoint(Polygone * poly, Point * pt)
{
	poly->lPoint->Erase(poly->lPoint,pt);
}

void showPolygone(Polygone* poly, int* name)
{
	Pointer* ptr;
	Point * pt;
	glBegin(GL_POLYGON);
	ptr = poly->lPoint->begin;
	if(name)
	{
		glLoadName(*name);
		*name++;
	}
	while((ptr = ptr->nextpointer) != poly->lPoint->end)
	{
		pt = (Point*)ptr->pointer;
		glColor3ub(poly->obj.color[0],poly->obj.color[1],poly->obj.color[2]);
		glVertex3f(pt->x,pt->y,pt->z);
	}
	glEnd();
}


Sphere* newSphere(Sphere* sph,Point * center, float r, char * texture, int color)
{
	int i;
	Texture * t;
	if(!sph)
		sph = (Sphere*)malloc(sizeof(Sphere));
	sph->obj.type = OBJECT_TYPE_SPHERE;


	sph->obj.texture = NULL;
	t = (Texture*)getTextureFromName(texture);
	if(t)
	{
		if(!t->isLoad)
			load(t);

		sph->obj.texture = t;
		sph->obj.texture->use++;
	}

	for(i = 0; i < 4; i++)
		sph->obj.color[i] = ((char*)&color)[i];

	newQuat(&sph->obj.qtrot,0.0f,0.0,0.0,0.0);

	sph->center = *center;
	sph->r = r;
	return sph;
}
void deleteSphere(Sphere* sph)
{
	if(sph->obj.texture)
		sph->obj.texture->use--;
	free(sph);
}

void showSphere(Sphere* sph,int* name)
{
	int i;
    GLUquadric* params = gluNewQuadric();
	glColor3ub(sph->obj.color[0],sph->obj.color[1],sph->obj.color[2]);


	glPushMatrix();
    
	if(name)
	{
		glLoadName(*name);
		*name++;
	}
	glTranslatef(sph->center.x,sph->center.y,sph->center.z);
	glRotated(TOROT(toRot(sph->obj.qtrot)));
		
	glEnable(GL_TEXTURE_2D);

	
	//init texture
	if(sph->obj.texture)
	{
		gluQuadricTexture(params,GL_TRUE);
		glBindTexture(GL_TEXTURE_2D,sph->obj.texture->textureID);
	}
	gluSphere(params,sph->r,100,100);

	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}


void contAddObject(Container* ct,Object* obj)
{
	ct->objectL->Append(ct->objectL,obj);
}
void contDelObject(Container* ct,Object* obj)
{
	ct->objectL->Erase(ct->objectL,obj);
}
void showContainer(Container* ct, int*name)
{
	int i;
	Pointer* itr;
	glPushMatrix();
    
	if(name)
	{
		glLoadName(*name);
		*name++;
	}
	glTranslatef(ct->center.x,ct->center.y,ct->center.z);
	glTranslatef(ct->repere.x,ct->repere.y,ct->repere.z);
	glRotated(TOROT(toRot(ct->obj.qtrot)));
	showrepere();
	glTranslatef(-ct->repere.x,-ct->repere.y,-ct->repere.z);
	itr = ct->objectL->begin;
	while((itr = itr->nextpointer) != ct->objectL->end)
	{
		showObject((Object*)itr->pointer,NULL);
	}

	glPopMatrix();
}

void rot(Object*obj,double angle, double x, double y, double z)
{
	Quat qt;
	newQuat(&qt,angle*TORAD,x,y,z); 
	obj->qtrot = quatProd(obj->qtrot,qt);
}

void render_string(float x, float y, float z, const char* s)
{
    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_DEPTH_TEST);
	glColor3f(0,255,0);
	glRasterPos3f(x,y,z);


    while(*s)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *s);
        s++;
    }
}


void showrepere()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3ub(255,0,0);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(1.0f,0.0f,0.0f);
	glEnd();
	render_string(1, 0, 0, "x");

	glBegin(GL_LINES);
	glColor3ub(0,255,0);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glEnd();
	render_string(0, 1, 0, "y");

	glBegin(GL_LINES);
	glColor3ub(0,0,255);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,1.0f);
	glEnd();
	render_string(0, 0, 1, "z");
}


/*
	C*E				-C*F			-D		0
	-B*D*E + A*F	B*D*F+ A*E		-B*C	0
	A*D*E + B*F		-A*D*F + B*E	A*C		0
	0				0				0		1

A       = cos(angle_x);
B       = sin(angle_x);
C       = cos(angle_y);
D       = sin(angle_y);
E       = cos(angle_z);
F       = sin(angle_z);


if C = 0 (angle_y = 0);

	0				0			-D		0
	-B*D*E + A*F	B*D*F+ A*E		-B*C	0
	A*D*E + B*F		-A*D*F + B*E	A*C		0
	0				0				0		1

*/
void getEulerAngle(double angles[3], GLdouble * tab)
{
	double A,B,C,D,E,F;
	Matrice * mat = ToMatrice(tab);

	D = -mat->mat[0][2];
	(angles)[1] = asin(D);
	C = cos(angles[1]);

	if(fabs(C) > 0.0f)
	{
		A = mat->mat[1][2]/C;
		B = -mat->mat[2][2]/C;
		E = mat->mat[0][0]/C;
		F = -mat->mat[0][1]/C;

		(angles)[0] = atan2(B,A);
		(angles)[2] = atan2(F,E);
	}else
	{
		(angles)[0] = 0.0f;
		E = mat->mat[1][1];
		F = mat->mat[1][0];

		(angles)[2]  = atan2(F, E);
	}
}