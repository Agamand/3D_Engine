
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Object.h"
#include "BMPloader.h"
#include "ObjectAccessor\ObjectAccessor.h"
#include "Matrix.h"
#include <glut.h>


/*	GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
	GLfloat mat_diffuse[] = {0.1, 0.5, 0.8, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat no_shininess[] = {0.0};
	GLfloat low_shininess[] = {8.0};
	GLfloat high_shininess[] = {100.0};
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};*/


Object::Object() : parent(NULL), texture(NULL), type(OBJECT_TYPE_NONE)
{
	color = 0xffffffff;
	position = Vector3D();
	repere = position;
	rotation = Quat();
	size = 1.0f;
	animation =  new Animation(this);
}

Object::Object(Vector3D _position)
{
	Object::Object();
	position = _position;
	repere = position;
}

Object::Object(Vector3D _position, Vector3D _repere)
{
	Object::Object();
	position = _position;
	repere = _repere;
}

Object::~Object()
{
	parent = NULL;
	//if(texture)
		//delete texture;
}

void Object::update(int time)
{
	animation->update(time);
	updateChild(time);
}

void Object::updatePosition(int time)
{
	Animation::MoveInfo mv(position,rotation,time);
	animation->addMoveInfo(mv);
	updatePositionChild(time);
}

Container::Container()
{
	Object::Object();
}

Container::Container(Vector3D _position)
{
	Object::Object(_position);
}

Container::Container(Vector3D _position, Vector3D _repere)
{
	Object::Object(_position, _repere);
}

void Container::delObject(Object* obj)
{
	if(object_list.empty())
		return;

	for(std::size_t i = 0; i < object_list.size();)
	{
		if(obj == (object_list[i]))
			object_list.erase(object_list.begin()+i);
		else i++;
	}
}

void Container::updateChild(int time)
{
	for(std::size_t i = 0; i < object_list.size(); i++)
		object_list[i]->update(time);
}

void Container::updatePositionChild(int time)
{
	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		object_list[i]->updatePosition(time);
	}
}

void Container::show()
{
	glPushMatrix();
	glTranslatef(position.getX(),position.getY(),position.getZ());
	glTranslatef(repere.getX(),repere.getY(),repere.getZ());
	glRotated(TOROT(rotation.toRot()));
	//if(ct->showRep)
	showrepere();
	glTranslatef(-repere.getX(),-repere.getY(),-repere.getZ());
	for(std::size_t i = 0; i < object_list.size(); i++)
	{
		object_list[i]->show();
	}
	glPopMatrix();
}

void Container::addSphere(double r,float stack, float slice,double angle)
{
	double cosa = 1.0f;
	double sina = 0.0f;
	double cosa1 = cos(angle/stack);
	double sina1 = sin(angle/stack);
	for(int i = 0; i < stack; i++)
	{
		for(int j = 0; j < slice; j++)
		{

			Polygone* poly = new Polygone();
			poly->setColor(0xffff0000);
			poly->addVertex(Polygone::Vertex(r*cosa*cos(j*angle/slice),r*sina*cos(j*M_PI/slice), r*sin(j*M_PI/slice)));
			poly->addVertex(Polygone::Vertex(r*cosa*cos((j+1)*angle/slice),r*sina*cos((j+1)*M_PI/slice), r*sin((j+1)*M_PI/slice)));
			poly->addVertex(Polygone::Vertex(r*cosa1*cos((j+1)*angle/slice),r*sina1*cos((j+1)*M_PI/slice), r*sin((j+1)*M_PI/slice)));
			poly->addVertex(Polygone::Vertex(r*cosa1*cos(j*angle/slice),r*sina1*cos(j*M_PI/slice), r*sin(j*M_PI/slice)));
			addObject(poly);
		}

	cosa = cosa1;
	sina = sina1;
	cosa1 = cos((i+2)*angle/stack);
	sina1 = sin((i+2)*angle/stack);
	}

}

void Container::addCylinder(double r1,double r2, double length,float stack, float slice, double angle)
{
	double dr = (r2-r1)/stack;
	for(int i = 0; i < stack;i++)
	{
		for(int j = 0; j < slice; j++)
		{
			double r = dr*i + r1;
			Polygone* poly = new Polygone();
			poly->setColor(0xffff0000);
			poly->addVertex(Polygone::Vertex(r*cos(i*angle/stack),r*sin(i*angle/stack), length/slice*j));
			poly->addVertex(Polygone::Vertex(r*cos(i*angle/stack),r*sin(i*angle/stack), length/slice*(j+1)));
			poly->addVertex(Polygone::Vertex(r*cos((i+1)*angle/stack),r*sin((i+1)*angle/stack), length/slice*(j+1)));
			poly->addVertex(Polygone::Vertex(r*cos((i+1)*angle/stack),r*sin((i+1)*angle/stack), length/slice*j));
			addObject(poly);
		}
	}

}

void Container::addDisk(double r,float stack,double angle)
{
		for(int i = 0; i < stack; i++)
		{
			Polygone* poly = new Polygone();
			poly->setColor(0xffff0000);
			poly->addVertex(Polygone::Vertex(r*cos(i*angle/stack),r*sin(i*angle/stack), 0.0f));
			poly->addVertex(Polygone::Vertex(0.0f,0.0f, 0.0f));
			poly->addVertex(Polygone::Vertex(r*cos((i+1)*angle/stack),r*sin((i+1)*angle/stack), 0.0f));
			addObject(poly);
		}
}

void Container::addTorus(double r1, double r2, float side, float ring, double angle1, double angle2, double angle1_beg)
{
	r2 += r1*2;
	for(int i = 0; i <	1; i++)
	{
	/*	Matrix m1 = Matrix::getRotateMatrix2(i*angle/ring);
		Matrix m2 = Matrix::getRotateMatrix2((i+1)*angle/ring);
		*/


		for(int j = 0; j < side; j++)
		{

			Polygone* poly = new Polygone();
			poly->setColor(0xff00ff00);
			/*poly->addVertex(Polygone::Vertex(r2*cos(i*angle2/ring)*r1*cos(j*angle1/side),r2*sin(i*angle2/ring)*r1*cos(j*angle1/side), r1*sin(j*angle1/side)));
			poly->addVertex(Polygone::Vertex(r2*cos(i*angle2/ring)*r1*cos((j+1)*angle1/side),r2*sin(i*angle2/ring)*r1*cos((j+1)*angle1/side), r1*sin((j+1)*angle1/side)));
			poly->addVertex(Polygone::Vertex(r2*cos((i+1)*angle2/ring)*r1*cos((j+1)*angle1/side),r2*sin((i+1)*angle2/ring)*r1*cos((j+1)*angle1/side), r1*sin((j+1)*angle1/side)));
			poly->addVertex(Polygone::Vertex(r2*cos((i+1)*angle2/ring)*r1*cos(j*angle1/side),r2*sin((i+1)*angle2/ring)*r1*cos(j*angle1/side),r1*sin(j*angle1/side)));*/
			addObject(poly);
		}
	}
}
Polygone::Polygone()
{
	Object::Object();
}

Polygone::Polygone(Vector3D _position)
{
	Object::Object(_position);
}

Polygone::Polygone(Vector3D _position, Vector3D _repere)
{
	Object::Object(_position, _repere);
}

Polygone::~Polygone()
{
	if(vertex_list.size())
		return;

	for(std::size_t i = 0; i < vertex_list.size(); i++)
		delete vertex_list[i];
}

void Polygone::show()
{
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glBegin(GL_POLYGON);
	for(std::size_t i = 0; i < vertex_list.size(); i++)
	{
		
		glColor4ub(TOCOLOR4(color));
		glTexCoord2f(vertex_list[i]->u,vertex_list[i]->v);
		glVertex3d(vertex_list[i]->x,vertex_list[i]->y,vertex_list[i]->z);
	}
	glEnd();
}

void Polygone::delVertex(Vertex v)
{
	if(vertex_list.empty())
		return;

	for(std::size_t i = 0; i < vertex_list.size(); i++)
	{
		if(v == (*vertex_list[i]))
		{
			vertex_list.erase(vertex_list.begin()+i);
			delete vertex_list[i];
		}
	}
}



/*Cube* newCube(Cube * cube, Point p,int l[])
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
	ct->showRep = 0;
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
	Object* obj = (Object*)poly;
	glBegin(GL_POLYGON);
	ptr = poly->lPoint->begin;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
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
	Object* obj = (Object*)sph;
    GLUquadric* params = gluNewQuadric();
	glColor3ub(sph->obj.color[0],sph->obj.color[1],sph->obj.color[2]);


	glPushMatrix();
    
	if(name)
	{
		glPushName(*name);
		obj->name = *name;
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
	if(name)
		glPopName();
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
	int _name = 1;
	Object* obj = (Object*)ct;
	glPushMatrix();
	
    
	if(name)
	{
		glLoadName(*name);
		obj->name = *name;
		*name++;
		//glPopName();
	}
	glTranslatef(ct->center.x,ct->center.y,ct->center.z);
	glTranslatef(ct->repere.x,ct->repere.y,ct->repere.z);
	glRotated(TOROT(toRot(ct->obj.qtrot)));
	if(ct->showRep)
		showrepere();
	glTranslatef(-ct->repere.x,-ct->repere.y,-ct->repere.z);
	itr = ct->objectL->begin;
	while((itr = itr->nextpointer) != ct->objectL->end)
	{
		showObject((Object*)itr->pointer,&_name);
	}

	glPopMatrix();
}

void rot(Object*obj,double angle, double x, double y, double z)
{
	Quat qt;
	newQuat(&qt,angle*TORAD,x,y,z); 
	obj->qtrot = quatProd(obj->qtrot,qt);
}

*/void render_string(float x, float y, float z, const char* s)
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
	//glEnable(GL_LIGHTING);
}/*


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

*//*
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


Light* newLight(Light * l,Vector3D center,Vector3D rep, int color, int n_light)
{
	int i;
	if(!l)
		l = (Light*)malloc(sizeof(Light));

	newVector3D(&l->dir,0.0f,0.0f,0.0f);
	l->spot = 180.0f;
	for(i = 0; i < 4; i++)
		l->obj.color[i] = ((char*)&color)[i];

	l->center = center;
	l->rep = rep;
	l->n_light = n_light;

	return l;

}
void deleteLight(Light* l)
{
	free(l);
}

void showLight(Light* l)
{
	float pos[4],color[4],dir[3];
	int i;
	pos[0] = l->center.x;
	pos[1] = l->center.y;
	pos[2] = l->center.z;
	pos[3] = 1.0f;


	for(i = 0; i < 4; i++)
		color[i] = l->obj.color[i]/255.0f;

	dir[0] = l->dir.x;
	dir[1] = l->dir.y;
	dir[2] = l->dir.z;
	glEnable(l->n_light);
	glLightfv(l->n_light, GL_DIFFUSE, color);   
	glLightfv(l->n_light, GL_POSITION, pos); 
	glLightfv(l->n_light, GL_SPOT_DIRECTION, dir);
	glLightfv(l->n_light, GL_SPOT_CUTOFF, &l->spot);
}
*/