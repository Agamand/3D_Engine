
#include "Robot.h"

Robot::Robot()
{
	base = new Container();
	for(int i = 0; i < 12; i++)
		_doigt[i] = NULL;
	base->addObject(mains());


}


Object* Robot::doigtB()
{
	Container* _base = new Container();
	Container* ct = new Container();
	ct->addCylinder(0.05f,0.05f,0.1,40,1);
	ct->rotate(90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addSphere(0.05,20,20,M_PI);
	ct->setPosition(0.1f,0.0f,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,0.0f,1.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.05,40);
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
	ct->addCylinder(h,h,y*2,20,1,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,10,M_PI);//Cylinder(h/2,h/2,y*2,20,20,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,10,M_PI);
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
	ct->addCylinder(0.05f,0.05f,0.3,20,1);
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
	ct->addCylinder(h,h,y*2,10,1,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,10,M_PI);//Cylinder(h/2,h/2,y*2,20,20,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,Vector3D(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,10,M_PI);
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
	int i = 0;
	if(_doigt[2] != NULL)
		i = 3;
	if(_doigt[5] != NULL)
		i = 6;
	if(_doigt[8] != NULL)
		i = 9;
	Container* c1,*c2;
	c1 = (Container*)doigt();
	c2 = (Container*)doigtB();
	c1->addObject(c2);
	c2->setPosition(0.335,0.0,0.0);
	_doigt[i++] = c2;
	_doigt[i++] = c1;
	c2 = c1;
	c1 = (Container*)doigt();
	_doigt[i++] = c1;
	c2->setPosition(0.335,0.0,0.0);
	c1->addObject(c2);
	return c1;
}

Object* Robot::corps()
{
	Container* _base = new Container();
	Container* ct = new Container();
	ct->addCylinder(0.25f*2,0.35f*2,0.6f*2,40,20);

	_base->addObject(ct);

	ct = new Container();
	ct->addCylinder(0.35f*2,0.15f*2,0.1f*2,40,20);
	ct->setPosition(0.0f,0.0f,0.6f*2);

	_base->addObject(ct);
	ct = (Container*)tete();
	ct->setPosition(0.0,0.0,1.4f);
	_base->addObject(ct);

	ct = (Container*)bras_complete();
	ct->setPosition(-0.1525*2,0.035*2,0.5*2);
	_base->addObject(ct);

	return _base;
}

Object* Robot::tete()
{
	Container* _base = new Container();
	Container* ct = new Container();
	ct->addCylinder(0.3,0.3,0.5,40,20);
	_base->addObject(ct);

	ct = new Container();
	ct->addSphere(0.3f,40,40,M_PI);
	ct->setPosition(0.0,0.0,0.5f);
	ct->rotate(M_PI/2,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);
	return _base;
}

Object* Robot::bras()
{
	Container* _base = new Container();
	Polygone* poly = new Polygone();
	poly->setColor(0xff0000ff);
	poly->addVertex(Polygone::Vertex(0.0,0.03,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.03,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.03,0.1));
	poly->addVertex(Polygone::Vertex(0.0,0.03,0.1));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xff00ff00);
	poly->addVertex(Polygone::Vertex(0.0,0.0,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.0,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.0,0.1));
	poly->addVertex(Polygone::Vertex(0.0,0.0,0.1));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffffff00);
	poly->addVertex(Polygone::Vertex(0.0,0.00,0.0));
	poly->addVertex(Polygone::Vertex(0.0,0.03,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.03,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.00,0.0));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Polygone::Vertex(0.0,0.0,0.1));
	poly->addVertex(Polygone::Vertex(0.0,0.03,0.1));
	poly->addVertex(Polygone::Vertex(0.4,0.03,0.1));
	poly->addVertex(Polygone::Vertex(0.4,0.0,0.1));
	_base->addObject(poly);


	Container* ct = new Container();
	ct->addCylinder(0.03,0.03,0.05,40,20);
	ct->setPosition(0.435,-0.01,0.05);
	ct->rotate(-M_PI/2,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.03f,40);
	ct->setPosition(0.435,-0.01,0.05);
	ct->rotate(-M_PI/2,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.03f,40);
	ct->setPosition(0.435,0.04,0.05);
	ct->rotate(-M_PI/2,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addSphere(0.06,40,40);
	ct->setPosition(-0.035,0.015,0.05);
	_base->addObject(ct);
	_base->setRepere(-0.035,0.00,0.05);
	return _base;
}

Object* Robot::avant_bras()
{
	Container* _base = new Container();
	Polygone* poly = new Polygone();
	poly->setColor(0xff0000ff);
	poly->addVertex(Polygone::Vertex(0.0,0.03,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.03,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.03,0.1));
	poly->addVertex(Polygone::Vertex(0.0,0.03,0.1));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xff00ff00);
	poly->addVertex(Polygone::Vertex(0.0,0.0,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.0,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.0,0.1));
	poly->addVertex(Polygone::Vertex(0.0,0.0,0.1));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffffff00);
	poly->addVertex(Polygone::Vertex(0.0,0.00,0.0));
	poly->addVertex(Polygone::Vertex(0.0,0.03,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.03,0.0));
	poly->addVertex(Polygone::Vertex(0.4,0.00,0.0));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Polygone::Vertex(0.0,0.0,0.1));
	poly->addVertex(Polygone::Vertex(0.0,0.03,0.1));
	poly->addVertex(Polygone::Vertex(0.4,0.03,0.1));
	poly->addVertex(Polygone::Vertex(0.4,0.0,0.1));
	_base->addObject(poly);


	Container* ct = new Container();
	ct->addCylinder(0.06,0.06,0.05,40,1);
	ct->setPosition(-0.035,-0.01,0.05);
	ct->rotate(-M_PI/2,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addCylinder(0.03,0.03,0.05,40,1);
	ct->setPosition(-0.035,-0.01,0.05);
	ct->rotate(-M_PI/2,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);


	ct = new Container();
	ct->addCylinder(0.06,0.03,0.00,40,1);
	ct->setPosition(-0.035,-0.01,0.05);
	ct->rotate(-M_PI/2,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addCylinder(0.06,0.03,0.00,40,1);
	ct->setPosition(-0.035,0.04,0.05);
	ct->rotate(-M_PI/2,Vector3D(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	_base->setRepere(-0.035,0.00,0.05);



	return _base;
}


Object* Robot::bras_complete()
{
	Container* _base;
	_base = (Container*)bras();
	_bras[0] = _base;
	Container* ct = (Container*)avant_bras();
	ct->setPosition(0.47f,0.0,0.0);
	_bras[1] = ct;
	_base->addObject(ct);
	return _base;
}

Object* Robot::mains()
{
	double y = 0.1f*sin(M_PI/12);
	double _y = (0.2f-(y+0.05f))/2;
	Container* _base = new Container();
	Polygone* poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(0.0f,0.0f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.05f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.05f,0.1f));
	poly->addVertex(Polygone::Vertex(0.0f,0.0f,0.08f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(-0.1f,0.0f,0.08f));
	poly->addVertex(Polygone::Vertex(-0.1f,0.05f,0.08f));
	poly->addVertex(Polygone::Vertex(0.0f,0.05f,0.1f));
	poly->addVertex(Polygone::Vertex(0.0f,0.0f,0.08f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(-0.1f,0.2f,0.08f));
	poly->addVertex(Polygone::Vertex(-0.1f,0.05f+y+_y,0.08f));
	poly->addVertex(Polygone::Vertex(0.0f,0.05f+y+_y,0.08f));
	poly->addVertex(Polygone::Vertex(0.0f,0.2f,0.1f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(-0.1f,0.35f,0.08f));
	poly->addVertex(Polygone::Vertex(-0.1f,0.2f+y+_y,0.08f));
	poly->addVertex(Polygone::Vertex(0.0f,0.2f+y+_y,0.08f));
	poly->addVertex(Polygone::Vertex(0.0f,0.35f,0.1f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(-0.1f,0.5f,0.08f));
	poly->addVertex(Polygone::Vertex(-0.1f,0.35f+y+_y,0.08f));
	poly->addVertex(Polygone::Vertex(0.0f,0.35f+y+_y,0.08f));
	poly->addVertex(Polygone::Vertex(0.0f,0.5f,0.1f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(0.0f,0.0f,0.08f));
	poly->addVertex(Polygone::Vertex(-0.4f,0.0f,0.08f));
	poly->addVertex(Polygone::Vertex(-0.4f,0.0f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.0f,0.0f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(-0.9f,0.1f,0.08f));
	poly->addVertex(Polygone::Vertex(-0.4f,0.0f,0.08f));
	poly->addVertex(Polygone::Vertex(-0.4f,0.0f,0.0f));
	poly->addVertex(Polygone::Vertex(-0.9f,0.1f,0.0f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(0.0f,0.55f+y,0.08f));
	poly->addVertex(Polygone::Vertex(-0.4f,0.55f+y,0.08f));
	poly->addVertex(Polygone::Vertex(-0.4f,0.55f+y,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.55f+y,0.0f));
	_base->addObject(poly);

	Container* ct = (Container*)doigt_complete();
	ct->setPosition(0.0f,0.05f,0.05f);
	ct->setPosition(ct->getPosition()-ct->getRepere());
	_base->addObject(ct);
	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.05f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,y+0.05f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,y+0.05f,0.1f));
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.05f,0.08f));
	_base->addObject(poly);


	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.05f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.2f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.2f,0.1f));
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.05f,0.08f));
	_base->addObject(poly);

	ct = (Container*)doigt_complete();
	ct->setPosition(0.0f,0.2f,0.05f);
	ct->setPosition(ct->getPosition()-ct->getRepere());
	_base->addObject(ct);

	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.2f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,y+0.2f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,y+0.2f,0.1f));
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.2f,0.08f));
	_base->addObject(poly);


	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.2f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.35f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.35f,0.1f));
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.2f,0.08f));
	_base->addObject(poly);

	ct = (Container*)doigt_complete();
	ct->setPosition(0.0f,0.35f,0.05f);
	ct->setPosition(ct->getPosition()-ct->getRepere());
	_base->addObject(ct);

	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.35f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,y+0.35f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,y+0.35f,0.1f));
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.35f,0.08f));
	_base->addObject(poly);


	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.35f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.5f,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.5f,0.1f));
	poly->addVertex(Polygone::Vertex(0.0f,y+_y+0.35f,0.08f));
	_base->addObject(poly);


	ct = (Container*)doigt_complete();
	ct->setPosition(0.0f,0.5f,0.05f);
	ct->setPosition(ct->getPosition()-ct->getRepere());
	_base->addObject(ct);

	poly  = new Polygone();
	poly->addVertex(Polygone::Vertex(0.0f,0.5f+y,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.55f+y,0.0f));
	poly->addVertex(Polygone::Vertex(0.0f,0.55f+y,0.08f));
	poly->addVertex(Polygone::Vertex(0.0f,0.5f+y,0.1f));
	_base->addObject(poly);




	return _base;
}

Object* Robot::operator[] (int i)
{
	i %=12;
	if(i != i)
		return _bras[i];
	else
		return _doigt[i];
}
