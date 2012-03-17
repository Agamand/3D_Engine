#include "Other.h"



/*
Object * box(Point * center,Point* repere,float x_length, float y_length, float z_length)
{
	Point *_pt;
	Container * ct;
	Polygone *  poly;
	ct = newContainer(NULL,center,repere);

	_pt = newPoint(NULL,0.0f,0.0,0.0f);
	poly = newPolygone(NULL,_pt,255);
	_pt = newPoint(NULL,x_length,0.0f,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,x_length,y_length,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,y_length,0.0f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.0f,0.0,z_length);
	poly = newPolygone(NULL,_pt,255 + (255 << 8));
	_pt = newPoint(NULL,x_length,0.0f,z_length);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,x_length,y_length,z_length);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,y_length,z_length);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.0f,0.0,0.0f);
	poly = newPolygone(NULL,_pt,255 +(255 << 8) + (255 << 16));
	_pt = newPoint(NULL,x_length,0.0f,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,x_length,0.0f,z_length);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,0.0f,z_length);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.0f,y_length,0.0f);
	poly = newPolygone(NULL,_pt,(255 << 8)+ (255 << 16));
	_pt = newPoint(NULL,x_length,y_length,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,x_length,y_length,z_length);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,y_length,z_length);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);


	_pt = newPoint(NULL,0.0f,0.0f,0.0f);
	poly = newPolygone(NULL,_pt,255);
	_pt = newPoint(NULL,0.0f,y_length,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,y_length,z_length);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,0.0f,z_length);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,x_length,0.0f,0.0f);
	poly = newPolygone(NULL,_pt,(255 << 8));
	_pt = newPoint(NULL,x_length,y_length,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,x_length,y_length,z_length);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,x_length,0.0f,z_length);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);
	return (Object*)ct;
}

/*

Object *pied()
{
	Point pt,pt_2;
	Point *_pt;
	Container * ct;
	Polygone *  poly;
	newPoint(&pt,0.0f,0.0f,0.0f);
	newPoint(&pt_2,0.6f,0.5f,1.0f);
	ct = newContainer(NULL,&pt,&pt_2);

	_pt = newPoint(NULL,2.0f,1.0f,0.0f);
	poly = newPolygone(NULL,_pt,255);
	_pt = newPoint(NULL,2.0f,0.0f,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,0.0f,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,1.0f,0.0f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.0f,0.0f,0.0f);
	poly = newPolygone(NULL,_pt,255 + (127 << 8));
	_pt = newPoint(NULL,0.3f,0.2f,1.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.9f,0.2f,1.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,2.0f,0.0f,0.0f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.0f,1.0f,0.0f);
	poly = newPolygone(NULL,_pt,65535);
	_pt = newPoint(NULL,0.3f,0.8f,1.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.9f,0.8f,1.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,2.0f,1.0f,0.0f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.0f,0.0f,0.0f);
	poly = newPolygone(NULL,_pt,(255 << 8));
	_pt = newPoint(NULL,0.3f,0.2f,1.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.3f,0.8f,1.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,1.0f,0.0f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,2.0f,0.0f,0.0f);
	poly = newPolygone(NULL,_pt,(255 << 16));
	_pt = newPoint(NULL,0.9f,0.2f,1.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.9f,0.8f,1.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,2.0f,1.0f,0.0f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);


	return (Object*)ct;

}


Object* jambe()
{
	Point pt, pt_2;
	Point *_pt;
	Container * ct;
	Polygone *  poly;
	newPoint(&pt,0.0f,0.0f,0.0f);

	newPoint(&pt_2,0.5f,0.5f,3.0f);
	ct = newContainer(NULL,&pt,&pt_2);

	_pt = newPoint(NULL,0.2f,0.2f,0.0f);
	poly = newPolygone(NULL,_pt,255 + (127 << 8));
	_pt = newPoint(NULL,0.8f,0.2f,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,0.0f,1.6f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,0.0f,1.6f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.2f,0.8f,0.0f);
	poly = newPolygone(NULL,_pt,65535);
	_pt = newPoint(NULL,0.8f,0.8f,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,1.0f,1.6f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,1.0f,1.6f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);


	_pt = newPoint(NULL,0.8f,0.2f,0.0f);
	poly = newPolygone(NULL,_pt,(255 << 16));
	_pt = newPoint(NULL,0.8f,0.8f,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,1.0f,1.6f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,0.0f,1.6f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.2f,0.2f,0.0f);
	poly = newPolygone(NULL,_pt,(255 << 8));
	_pt = newPoint(NULL,0.2f,0.8f,0.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,1.0f,1.6f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,0.0f,1.6f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);


	//


	_pt = newPoint(NULL,0.0f,0.0f,2.0f);
	poly = newPolygone(NULL,_pt,255 + (127 << 8));
	_pt = newPoint(NULL,1.0f,0.0f,2.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,0.0f,1.6f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,0.0f,1.6f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.0f,1.0f,2.0f);
	poly = newPolygone(NULL,_pt,65535);
	_pt = newPoint(NULL,1.0f,1.0f,2.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,1.0f,1.6f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,1.0f,1.6f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);


	_pt = newPoint(NULL,1.0f,0.0f,2.0f);
	poly = newPolygone(NULL,_pt,(255 << 16));
	_pt = newPoint(NULL,1.0f,1.0f,2.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,1.0f,1.6f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,0.0f,1.6f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.0f,0.0f,2.0f);
	poly = newPolygone(NULL,_pt,(255 << 8));
	_pt = newPoint(NULL,0.0f,1.0f,2.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,1.0f,1.6f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,0.0f,1.6f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);


	//



	_pt = newPoint(NULL,0.2f,0.2f,3.0f);
	poly = newPolygone(NULL,_pt,255 + (127 << 8));
	_pt = newPoint(NULL,0.8f,0.2f,3.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,0.0f,2.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,0.0f,2.0f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.2f,0.8f,3.0f);
	poly = newPolygone(NULL,_pt,65535);
	_pt = newPoint(NULL,0.8f,0.8f,3.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,1.0f,2.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,1.0f,2.0f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);


	_pt = newPoint(NULL,0.8f,0.2f,3.0f);
	poly = newPolygone(NULL,_pt,(255 << 16));
	_pt = newPoint(NULL,0.8f,0.8f,3.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,1.0f,2.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,1.0f,0.0f,2.0f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);

	_pt = newPoint(NULL,0.2f,0.2f,3.0f);
	poly = newPolygone(NULL,_pt,(255 << 8));
	_pt = newPoint(NULL,0.2f,0.8f,3.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,1.0f,2.0f);
	polyAddPoint(poly,_pt);
	_pt = newPoint(NULL,0.0f,0.0f,2.0f);
	polyAddPoint(poly,_pt);

	contAddObject(ct,(Object*)poly);


	return (Object*)ct;

}



Object * jambe_complete()
{
	Object *obj, *_obj;

	_obj = pied();
	obj = jambe();

	((Container*)_obj)->center.x -=0.1f;
	((Container*)_obj)->center.z -= 1.0f;

	contAddObject((Container*)obj,_obj);

	_obj = obj;

	obj = jambe();

	((Container*)_obj)->center.z -= 3.0f;

	contAddObject((Container*)obj,_obj);

	((Container*)obj)->center.z += 4.0f;

	return obj;
}*//*

Object * doigt(float length)
{
	Point pt,pt_2;
	Container * ct;
	newPoint(&pt,0.0f,0.0f,0.0f);
	newPoint(&pt_2,0.0f,0.1f,0.1f);
	ct = box(&pt,&pt_2,length,0.1,0.1);
	return ct;
}

Object * doigt_complet(Doigt * d)
{
	Object *obj, *_obj;

	
	_obj = doigt(0.1f);
	d->doigt[2] = _obj;
	obj = doigt(0.3f);
	d->doigt[1] = obj;

	((Container*)_obj)->center.x +=0.35f;

	contAddObject((Container*)obj,_obj);

	_obj = obj;

	obj = doigt(0.4f);
	d->doigt[0] = obj;

	((Container*)_obj)->center.x +=0.45f;

	contAddObject((Container*)obj,_obj);

	return obj;
}

Object * pouce(Doigt * d)
{
	Object *obj, *_obj;

	_obj = doigt(0.3f);
	d->doigt[1] = _obj;
	obj = doigt(0.4f);
	d->doigt[0] = obj;

	((Container*)_obj)->center.x +=0.45f;
	rot(_obj,30,0.0,0.0,1.0);

	contAddObject((Container*)obj,_obj);


	return obj;
}
Object * mains()
{
	Point pt,pt_2;
	Container * ct;
	newPoint(&pt,0.0f,0.0f,0.0f);
	newPoint(&pt_2,0.0f,0.35f,0.05f);
	ct = box(&pt,&pt_2,0.7f,0.7f,0.1f);
	return ct;
}
Object * main_complete(Mains * m)
{
	Object *obj, *_obj;

	
	obj = mains();
	m->main = obj;
	_obj = doigt_complet(&m->doigt[0]);

	((Container*)_obj)->center.x +=0.75f;
	((Container*)_obj)->center.y +=0.0f;

	contAddObject((Container*)obj,_obj);

	_obj = doigt_complet(&m->doigt[1]);

	((Container*)_obj)->center.x +=0.75f;
	((Container*)_obj)->center.y +=0.2f;

	contAddObject((Container*)obj,_obj);

	_obj = doigt_complet(&m->doigt[2]);

	((Container*)_obj)->center.x +=0.75f;
	((Container*)_obj)->center.y +=0.4f;

	contAddObject((Container*)obj,_obj);

	_obj = doigt_complet(&m->doigt[3]);

	((Container*)_obj)->center.x +=0.75f;
	((Container*)_obj)->center.y +=0.6f;

	contAddObject((Container*)obj,_obj);

	_obj = pouce(&m->doigt[4]);

	((Container*)_obj)->center.x +=0.15f;
	((Container*)_obj)->center.y -=0.1f;
	rot(_obj,-30,0.0,0.0,1.0);

	contAddObject((Container*)obj,_obj);

	return obj;
}



Object * bras()
{
	Point pt,pt_2;
	Container * ct;
	newPoint(&pt,0.0f,0.0f,0.0f);
	newPoint(&pt_2,0.0f,0.3f,0.3f);
	ct = box(&pt,&pt_2,3.0f,0.6f,0.6f);
	return ct;
}
Object * bras_complet(Bras * b)
{
	Object *obj, *_obj;

	_obj = main_complete(&b->main);
	
	obj = bras();
	b->bras[1] = obj;

	((Container*)_obj)->center.x +=3.1f;
	((Container*)_obj)->center.y -=0.05f;
	((Container*)_obj)->center.z +=0.25f;
	rot(_obj,180,1.0,0.0,0.0);

	contAddObject((Container*)obj,_obj);

	_obj = obj;
	
	obj = bras();

	b->bras[0] = obj;

	((Container*)_obj)->center.x +=3.1f;
	//((Container*)_obj)->angle[1] = -60;

	contAddObject((Container*)obj,_obj);

	//((Container*)obj)->angle[2] = 90;
	//((Container*)obj)->angle[0] = -30;
	((Container*)obj)->center.z += 8.0f ;



	


	return obj;
}


Object * corps(Corps * c)
{
	Point pt,pt_2;
	Container * ct;
	Object * _obj;
	newPoint(&pt,0.0f,0.0f,0.0f);
	newPoint(&pt_2,0.5f,1.5f,0.5f);
	ct = box(&pt,&pt_2,1.0f,3.0f,1.0f);

	_obj = bras_complet(&c->bras[0]);
	contAddObject(ct,_obj);
	((Container*)_obj)->center.x = 0.5f;
	((Container*)_obj)->center.y = -0.7f;
	((Container*)_obj)->center.z = 0.5f;
	rot(_obj,-90,0.0,0.0,1.0);

	_obj = bras_complet(&c->bras[1]);
	contAddObject(ct,_obj);
	((Container*)_obj)->center.x = 0.5f;
	((Container*)_obj)->center.y = 3.1f;
	((Container*)_obj)->center.z = 0.5f;
	rot(_obj,90,0.0,0.0,1.0);
	return ct;
}

Object * pied(Pied* p)
{
	Point c,r;
	Object* pied;
	newPoint(&c,0.0f,0.0f,0.0f);
	newPoint(&r,0.4f,0.4f,0.3f);
	pied = box(&c,&r,2.0f,0.8f,0.2f);
	p->pied = pied;
	return pied;
}
Object * jambe()
{
	Point c,r;
	Object* jambe;
	newPoint(&c,0.0f,0.0f,0.0f);
	newPoint(&r,0.1f,0.1f,0.1f);
	jambe = box(&c,&r,0.2f,0.2f,-3.0f);
	return jambe;
}
Object * jambe_complet(Jambe*j)
{
	Object *_obj,*obj;

	obj = pied(&j->pied);
	_obj = jambe();
	((Container*)obj)->center.z -= 3.4f;
	((Container*)obj)->center.x -= 0.2f;
	((Container*)obj)->center.y -= 0.2f;
	j->jambe[1] = _obj;
	contAddObject((Container*)_obj,obj);
	obj = _obj;
	((Container*)obj)->center.z -= 3.2f;
	_obj = jambe();
	j->jambe[0] = _obj; 
	contAddObject((Container*)_obj,obj);
	return _obj;
}

Object* makeSphere(double angle_1, double angle_1to, double angle_2, double angle_2to, double stack, double slice)
{
	int i,j;
	Point* p;
	Container* c = ;
	Polygone* poly;
	for(i = 0; i < slice; i++)
		for(j = 0; j < stack; i++)
		{	
			
			poly = newPolygone(NULL,NULL,0);
			newPoint(&p,cos(i*2*M_PI),cos
		}
}*/