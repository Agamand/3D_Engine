

#include "Robot.h"

Robot::Robot()
{
	base = new Container();
	base->addObject(doigt_complete());
}


Object* Robot::doigtB()
{
	Container* _base = new Container();
	Container* ct = new Container();
	ct->addCylinder(0.05f,0.05f,0.1,20,20);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addSphere(0.05,20,20,M_PI);
	ct->setPosition(0.1f,0.0f,0.0f);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.05,20);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	/*ct = new Container();
	ct->addCylinder(0.05,0.05,0.05,6,6,M_PI/6);
	ct->setPosition(-0.05f,0.0f,0.0f);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(-M_PI/12,Vector3D(0.0f,0.0f,1.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addCylinder(0.05,0.05,0.05,6,6,M_PI/6);
	ct->setPosition(-0.05f,0.0f,0.0f);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(M_PI-M_PI/12,Vector3D(0.0f,0.0f,1.0f));
	_base->addObject(ct);*/


	


	Polygone* poly = new Polygone();
	poly->setColor(0xffff0000);
	double h = 0.05*cos(M_PI/12);
	double y = 0.05f*sin(M_PI/12);
	poly->addVertex(Polygone::Vertex(-0.05f,y,h));
	poly->addVertex(Polygone::Vertex(0.0f,y,h));
	poly->addVertex(Polygone::Vertex(0.0f,y,-h));
	poly->addVertex(Polygone::Vertex(-0.05f,y,-h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Polygone::Vertex(-0.05f,-y,h));
	poly->addVertex(Polygone::Vertex(0.0f,-y,h));
	poly->addVertex(Polygone::Vertex(0.0f,-y,-h));
	poly->addVertex(Polygone::Vertex(-0.05f,-y,-h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Polygone::Vertex(-0.05f,-y,h));
	poly->addVertex(Polygone::Vertex(0.0f,-y,h));
	poly->addVertex(Polygone::Vertex(0.0f,y,h));
	poly->addVertex(Polygone::Vertex(-0.05f,y,h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Polygone::Vertex(-0.05f,-y,-h));
	poly->addVertex(Polygone::Vertex(0.0f,-y,-h));
	poly->addVertex(Polygone::Vertex(0.0f,y,-h));
	poly->addVertex(Polygone::Vertex(-0.05f,y,-h));
	_base->addObject(poly);

	ct = new Container();
	ct->addCylinder(h,h,y*2,20,20,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,20,M_PI);//Cylinder(h/2,h/2,y*2,20,20,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,20,M_PI);
	ct->setPosition(-0.05f,-y,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);
	_base->setRepere(-0.05f,-y,0.0f);
	//_base->rotate(-45*TORAD,Vector3D(0.0f,1.0f,0.0));
	return _base;
}
Object* Robot::doigt()
{
	Container* _base = new Container();
	Container* ct = new Container();
	ct->addCylinder(0.05f,0.05f,0.3,20,20);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.05,20);
	ct->setPosition(0.3f,0.0f,0.0f);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.05,20);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	/*ct = new Container();
	ct->addCylinder(0.05,0.05,0.05,6,6,M_PI/6);
	ct->setPosition(-0.05f,0.0f,0.0f);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(-M_PI/12,Vector3D(0.0f,0.0f,1.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addCylinder(0.05,0.05,0.05,6,6,M_PI/6);
	ct->setPosition(-0.05f,0.0f,0.0f);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(M_PI-M_PI/12,Vector3D(0.0f,0.0f,1.0f));
	_base->addObject(ct);*/


	


	Polygone* poly = new Polygone();
	poly->setColor(0xffff0000);
	double h = 0.05*cos(M_PI/12);
	double y = 0.05f*sin(M_PI/12);
	poly->addVertex(Polygone::Vertex(-0.05f,y,h));
	poly->addVertex(Polygone::Vertex(0.0f,y,h));
	poly->addVertex(Polygone::Vertex(0.0f,y,-h));
	poly->addVertex(Polygone::Vertex(-0.05f,y,-h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Polygone::Vertex(-0.05f,-y,h));
	poly->addVertex(Polygone::Vertex(0.0f,-y,h));
	poly->addVertex(Polygone::Vertex(0.0f,-y,-h));
	poly->addVertex(Polygone::Vertex(-0.05f,-y,-h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Polygone::Vertex(-0.05f,-y,h));
	poly->addVertex(Polygone::Vertex(0.0f,-y,h));
	poly->addVertex(Polygone::Vertex(0.0f,y,h));
	poly->addVertex(Polygone::Vertex(-0.05f,y,h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Polygone::Vertex(-0.05f,-y,-h));
	poly->addVertex(Polygone::Vertex(0.0f,-y,-h));
	poly->addVertex(Polygone::Vertex(0.0f,y,-h));
	poly->addVertex(Polygone::Vertex(-0.05f,y,-h));
	_base->addObject(poly);

	ct = new Container();
	ct->addCylinder(h,h,y*2,20,20,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,20,M_PI);//Cylinder(h/2,h/2,y*2,20,20,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,20,M_PI);
	ct->setPosition(-0.05f,-y,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);
	_base->setRepere(-0.05f,-y,0.0f);
	//_base->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0));
	
	
	return _base;
}

Object* Robot::doigt_complete()
{
	Container* c1,*c2;
	c1 = (Container*)doigt();
	c2 = (Container*)doigtB();
	c1->addObject(c2);
	c2->setPosition(0.335,0.0,0.0);

	c2 = c1;
	c1 = (Container*)doigt();
	c2->setPosition(0.335,0.0,0.0);
	c1->addObject(c2);
	return c1;
}