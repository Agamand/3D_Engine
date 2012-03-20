
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Object.h"
#include "BMPloader.h"
#include "ObjectAccessor\ObjectAccessor.h"
#include "Matrix.h"
#include "Physics.h"
#include <glut.h>

#define R(dr,r0,i) (dr*i + r0)

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
	mass = NULL;
	guid = ObjectAccessor::getObjMgr()->nextGUID();
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

void Object::updateMass(int diff)
{
	if(!mass)
		return;

	mass->simulate(diff);
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
		{
			object_list[i]->setParent(NULL);
			object_list.erase(object_list.begin()+i);
		}
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
			poly->setColor(0xffffffff);
			poly->setTexture(texture);
			poly->addVertex(Polygone::Vertex(r*cosa*sin(j*M_PI/slice),r*sina*sin(j*M_PI/slice), r*cos(j*M_PI/slice),i/stack,1.0f-j/slice));
			poly->addVertex(Polygone::Vertex(r*cosa*sin((j+1)*M_PI/slice),r*sina*sin((j+1)*M_PI/slice), r*cos((j+1)*M_PI/slice),i/stack,1.0f-(j+1)/slice));
			poly->addVertex(Polygone::Vertex(r*cosa1*sin((j+1)*M_PI/slice),r*sina1*sin((j+1)*M_PI/slice), r*cos((j+1)*M_PI/slice),(i+1)/stack,1.0f-(j+1)/slice));
			poly->addVertex(Polygone::Vertex(r*cosa1*sin(j*M_PI/slice),r*sina1*sin(j*M_PI/slice), r*cos(j*M_PI/slice),(i+1)/stack,1.0f-j/slice));
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
	double dr = (r2-r1)/slice;
	for(int i = 0; i < stack;i++)
	{
		for(int j = 0; j < slice; j++)
		{
			Polygone* poly = new Polygone();
			poly->setColor(0xffff0000);
			poly->addVertex(Polygone::Vertex((dr*j + r1)*cos(i*angle/stack),(dr*j + r1)*sin(i*angle/stack), length/slice*j));
			poly->addVertex(Polygone::Vertex((dr*(j+1) + r1)*cos(i*angle/stack),(dr*(j+1) + r1)*sin(i*angle/stack), length/slice*(j+1)));
			poly->addVertex(Polygone::Vertex((dr*(j+1) + r1)*cos((i+1)*angle/stack),(dr*(j+1) + r1)*sin((i+1)*angle/stack), length/slice*(j+1)));
			poly->addVertex(Polygone::Vertex((dr*j + r1)*cos((i+1)*angle/stack),(dr*j + r1)*sin((i+1)*angle/stack), length/slice*j));
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
	glScaled(size,size,size);
	if(texture)
	{
		glBindTexture(GL_TEXTURE_2D,texture->getTextureID());
	}
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

Light::Light()
{
	Object::Object();
	spot = 180;
	dir = Vector3D(1.0f,0.0f,0.0f);
	n_light = ObjectAccessor::getObjMgr()->getScene()->getUnusableLight();
	ObjectAccessor::getObjMgr()->getScene()->enableLight(n_light);
}

Light::Light(Vector3D pos)
{
	Object::Object(pos);
	spot = 180;
	dir = Vector3D(1.0f,0.0f,0.0f);
	n_light = ObjectAccessor::getObjMgr()->getScene()->getUnusableLight();
	ObjectAccessor::getObjMgr()->getScene()->enableLight(n_light);
}

void Light::show()
{
	float pos[4],_color[4],_dir[3];
	int i;
	pos[0] = position.getX();
	pos[1] = position.getY();
	pos[2] = position.getZ();
	pos[3] = 1.0f;


	for(i = 0; i < 4; i++)
		_color[i] = ((char*)&color)[i]/255.0f;

	_dir[0] = dir.getX();
	_dir[1] = dir.getY();
	_dir[2] = dir.getZ();
	glEnable(GL_LIGHT0+n_light);
	glLightfv(GL_LIGHT0+n_light, GL_DIFFUSE, _color);   
	glLightfv(GL_LIGHT0+n_light, GL_POSITION, pos); 
	glLightfv(GL_LIGHT0+n_light, GL_SPOT_DIRECTION, _dir);
	glLightfv(GL_LIGHT0+n_light, GL_SPOT_CUTOFF, &spot);
}

void render_string(float x, float y, float z, const char* s)
{
    glDisable(GL_TEXTURE_2D);
	glColor3f(0,255,0);
	glRasterPos3f(x,y,z);


    while(*s)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *s);
        s++;
    }

	ObjectAccessor::getObjMgr()->getScene()->applyOption();
}


void showrepere()
{
	return;
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
	ObjectAccessor::getObjMgr()->getScene()->applyOption();
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