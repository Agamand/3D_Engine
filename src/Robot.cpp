
#include "Robot.h"
#include "ObjectAccessor\ObjectAccessor.h"
#define TORAD (M_PI/180)


void link1b(Mesh* m, int b, glm::mat4 inverse)
{

	std::vector<Vertex*> list_v = m->getVertex();
	
	for(size_t i = 0; i < list_v.size(); i++)
	{
		m->linkVertex(i,b,1,inverse);
	}
}

void link3b(Mesh* m,int b1,int b2,int b3, float begin, float end)
{
	std::vector<Vertex*> list_v = m->getVertex();
	
	for(size_t i = 0; i < list_v.size(); i++)
	{
		float step = (end - list_v[i]->z);
		float p1;
		float p2;
		if(list_v[i]->z >= begin && list_v[i]->z < end)
		{
			p1 = 1-(step)/(end-begin);
			p2 = p1*p1;
			m->linkVertex(i,b1,0.5 * p2 - p1 + 0.5,glm::mat4(1.0f));
			m->linkVertex(i,b2,-p2 + p1 + 0.5,glm::mat4(1.0f));
			if(b3 != -1)
				m->linkVertex(i,b3,0.5 * p2,glm::mat4(1.0f));
		}
	}
}
Robot::Robot()
{
	base = new Container();
	//base->setPosition(0,0,10);
	
	for(int i = 0; i < 12; i++)
		_doigt[i] = NULL;

	//Shader* shader = new Shader("../../src/Shader/shading.vert","../../src/Shader/shading.frag");//new Shader("../../src/Shader/light2.vert","../../src/Shader/light2.frag");
	//base->addObject(corps());
	//base->rotate(M_PI_2,glm::vec3(0.0f,1.0f,0.0f));
	//base->setPosition(0.0,0.0f,1.0f);
	//base->useShader(shader);
	generateBone();
	generateRobot();
	// link robot >> bone
	bonebase->moveTo(glm::vec3(0,-9.0f,1.45f));
	bonebase->rotate(-90,glm::vec3(0,0,1));
	Bone* bras1 = (*(*bonebase)[0])[0];
	Bone* bras2 = (*(*bonebase)[1])[0];
	Bone* abras1 = (*bras1)[0];
	Bone* abras2 = (*bras2)[0];

	bras1->rotate(70,glm::vec3(1,0,0));
	bras2->rotate(-70,glm::vec3(1,0,0));
	abras1->rotate(30,glm::vec3(1,0,0));
	abras2->rotate(-30,glm::vec3(1,0,0));

}

void Robot::generateBone()
{
	bonebase = new Bone(1.4f);
	base->setMainBone(bonebase);
	Bone* hautgauche = new Bone(0.80f,bonebase);
	hautgauche->rotate(90+30,(glm::vec3(1,0,0)));
	Bone* hautdroit = new Bone(0.80f,bonebase);
	hautdroit->rotate(-(90+30),(glm::vec3(1,0,0)));
	Bone* brasgauche = new Bone(0.7f,hautgauche);
	brasgauche->rotate(-30,(glm::vec3(1,0,0)));
	Bone* brasdroit = new Bone(0.7f,hautdroit);
	brasdroit->rotate(30,(glm::vec3(1,0,0)));
	Bone* avantbrasgauche = new Bone(0.6f,brasgauche);
	Bone* avantbrasdroit = new Bone(0.6f,brasdroit);
	Bone* maingauche = new Bone(0.05f,avantbrasgauche);
	Bone* maindroit = new Bone(0.05f,avantbrasdroit);
	//main gauche
	Bone* doigtgauche1 = new Bone(0.07,maingauche);
	doigtgauche1->moveTo(glm::vec3(0.0,0.08,0.05));
	Bone* doigtgauche11 = new Bone(0.04,doigtgauche1);
	Bone* doigtgauche111 = new Bone(0.04,doigtgauche11);
	Bone* doigtgauche2 = new Bone(0.07,maingauche);
	doigtgauche2->moveTo(glm::vec3(0.08*sin((2*M_PI/3)),0.08*cos((2*M_PI/3)),0.05));
	Bone* doigtgauche22 = new Bone(0.04,doigtgauche2);
	Bone* doigtgauche222 = new Bone(0.04,doigtgauche22);
	Bone* doigtgauche3 = new Bone(0.07,maingauche);
	doigtgauche3->moveTo(glm::vec3(0.08*sin(-(2*M_PI/3)),0.08*cos(-(2*M_PI/3)),0.05));
	Bone* doigtgauche33 = new Bone(0.04,doigtgauche3);
	Bone* doigtgauche333 = new Bone(0.04,doigtgauche33);
	//main droite
	Bone* doigtdroite1 = new Bone(0.07,maindroit);
	doigtdroite1->moveTo(glm::vec3(0.0,-0.08,0.05));
	Bone* doigtdroite11 = new Bone(0.04,doigtdroite1);
	Bone* doigtdroite111 = new Bone(0.04,doigtdroite11);
	Bone* doigtdroite2 = new Bone(0.07,maindroit);
	doigtdroite2->moveTo(glm::vec3(-0.08*sin(-(2*M_PI/3)),-0.08*cos(-(2*M_PI/3)),0.05));
	Bone* doigtdroite22 = new Bone(0.04,doigtdroite2);
	Bone* doigtdroite222 = new Bone(0.04,doigtdroite22);
	Bone* doigtdroite3 = new Bone(0.07,maindroit);
	doigtdroite3->moveTo(glm::vec3(-0.08*sin((2*M_PI/3)),-0.08*cos((2*M_PI/3)),0.05));
	Bone* doigtdroite33 = new Bone(0.04,doigtdroite3);
	Bone* doigtdroite333 = new Bone(0.04,doigtdroite33);

	Bone* cuisseG = new Bone(0.7f,bonebase);
	cuisseG->moveTo(glm::vec3(0,0.3f,-1.4f));
	cuisseG->rotate(180,glm::vec3(1,0,0));
	Bone* cuisseD = new Bone(0.7f,bonebase);
	cuisseD->moveTo(glm::vec3(0,-0.3f,-1.4f));
	cuisseD->rotate(180,glm::vec3(1,0,0));
	Bone* jambeG = new Bone(0.61f,cuisseG);
	Bone* jambeD = new Bone(0.61f,cuisseD);
	Bone* piedG = new Bone(0.14f,jambeG);
	Bone* piedD = new Bone(0.14f,jambeD);

	Bone* tete = new Bone(0.5f,bonebase);
	Bone* eye1 = new Bone(0.1f,tete);
	eye1->moveTo(glm::vec3(0.3*cos(M_PI/8.0f),0.3*sin(M_PI/8.0f),-0.15));
	Bone* eye2 = new Bone(0.1f,tete);
	eye2->moveTo(glm::vec3(0.3*cos(-M_PI/8.0f),0.3*sin(-M_PI/8.0f),-0.15));

}

void Robot::generateRobot()
{
	corps();
}
void Robot::corps()
{
	glm::mat4 inverse = bonebase->getInverseMatrix();
	Texture* t = ObjectAccessor::getObjMgr()->getTexture("../../src/img/bender.bmp");
	
	Mesh* m;
	m = CreateCylinder(0.25f*2,0.35f*2,0.6f*2,20,20);
	if(t)
		m->setTexture(t);
	base->addObject(m);
	m->addBone(bonebase,inverse);
	link1b(m,0,inverse);

	m = CreateDisk(0.5f,20);
	if(t)
		m->setTexture(t);
	base->addObject(m);
	m->addBone(bonebase,inverse);
	m->rotate(180,glm::vec3(1.0f,0.0f,0.0f));
	link1b(m,0,inverse);

	m = CreateCylinder(0.35f*2,0.15f*2,0.1f*2,20,20);
	m->setPosition(0.0f,0.0f,0.6f*2); // 
	if(t)
		m->setTexture(t);
	base->addObject(m);
	m->addBone(bonebase,inverse);
	link1b(m,0,inverse);

	m = CreateSphere(0.14f,20,20);
	if(t)
		m->setTexture(t);
	m->setPosition(0.0f,0.30f*2,0.5f*2);
	base->addObject(m);
	m->addBone(bonebase,inverse);
	link1b(m,0,inverse);

	m = CreateSphere(0.14f,20,20);
	if(t)
		m->setTexture(t);
	m->setPosition(0.0f,-0.30f*2,0.5f*2);
	base->addObject(m);
	m->addBone(bonebase,inverse);
	link1b(m,0,inverse);

	bras(false);
	bras(true);

	mains(false);
	mains(true);

	doigt(false,0);
	doigt(false,1);
	doigt(false,2);

	doigt(true,0);
	doigt(true,1);
	doigt(true,2);

	tete();

	jambe();

	pied();
	/*ct = (Container*)tete();
	ct->setPosition(0.0,0.0,1.4f);
	_base->addObject(ct);

	ct = (Container*)bras_complete();
	ct->setPosition(0,0.35f*2,0.5*2);
	ct->setSize(2.0f);
	ct->rotate(M_PI_2,glm::vec3(0.0f,0.0f,1.0f));
	ct->rotate(M_PI/6,glm::vec3(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	ct = (Container*)bras_complete();
	ct->setPosition(0,-0.35f*2-0.03f,0.5*2);
	ct->setSize(2.0f);
	ct->setSymetrie(1.0f,1.0f,1.0f);
	ct->rotate(M_PI_2,glm::vec3(0.0f,0.0f,1.0f));
	ct->rotate(M_PI/6,glm::vec3(0.0f,1.0f,0.0f));
	_base->addObject(ct);


	ct = static_cast<Container*>(jambe_complete());
	ct->setPosition(0,0.15f*2,0);
	ct->setSize(2.0f);
	ct->rotate(M_PI_2,glm::vec3(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	ct = static_cast<Container*>(jambe_complete());
	ct->setPosition(0,-0.15f*2,0);
	ct->setSize(2.0f);
	ct->rotate(M_PI_2,glm::vec3(0.0f,1.0f,0.0f));
	_base->addObject(ct);*/
}
void Robot::bras(bool droit)
{
	Texture* t = ObjectAccessor::getObjMgr()->getTexture("../../src/img/bender.bmp");
	Mesh* m = CreateCylinder(0.1f,0.1f,1.4f,20,20);
	m->setTexture(t);
	if(droit)
	{
		Bone* bone1 = (*bonebase)[1];
		Bone* bone2 = (*bone1)[0];
		Bone* bone3 = (*bone2)[0];
		Bone* bone4 = (*bone3)[0];
		glm::mat4 inverse1 = bone1->getInverseMatrix();
		glm::mat4 inverse2 = bone2->getInverseMatrix();
		glm::mat4 inverse3 = bone3->getInverseMatrix();
		glm::mat4 inverse4 = bone4->getInverseMatrix();
		m->addBone(bone1,inverse1);
		m->addBone(bone2,inverse2);
		m->addBone(bone3,inverse3);
		m->addBone(bone4,inverse4);
		m->setPosition(0.0f,0.30f*2,0.5f*2);
		m->rotate(-90,glm::vec3(1.0f,0.0f,0.0f));

		link3b(m,0,1,2,0.0f,0.7f);
		link3b(m,1,2,3,0.7f,1.41f);
	}else
	{
		Bone* bone1 = (*bonebase)[0];
		Bone* bone2 = (*bone1)[0];
		Bone* bone3 = (*bone2)[0];
		Bone* bone4 = (*bone3)[0];
		glm::mat4 inverse1 = bone1->getInverseMatrix();
		glm::mat4 inverse2 = bone2->getInverseMatrix();
		glm::mat4 inverse3 = bone3->getInverseMatrix();
		glm::mat4 inverse4 = bone4->getInverseMatrix();
		m->addBone(bone1,inverse1);
		m->addBone(bone2,inverse2);
		m->addBone(bone3,inverse3);
		m->addBone(bone4,inverse4);
		m->setPosition(0.0f,-0.30f*2,0.5f*2);
		m->rotate(90,glm::vec3(1.0f,0.0f,0.0f));

		link3b(m,0,1,2,0,0.7f);
		link3b(m,1,2,3,0.7f,1.41f);
	}
	base->addObject(m);

}
void Robot::mains(bool droit)
{
	Texture* t = ObjectAccessor::getObjMgr()->getTexture("../../src/img/bender.bmp");
	Mesh* m = CreateCylinder(0.1f,0.11f,0.1f,20,20);
	m->setTexture(t);
	Mesh* d = CreateDisk(0.11,20);
	d->setTexture(t);
	if(droit)
	{
		Bone* bone = (*(*(*(*bonebase)[1])[0])[0])[0];
		glm::mat4 inverse = bone->getInverseMatrix();

		m->addBone(bone,inverse);

		m->setPosition(0.0f,0.30f*2+1.4f,0.5f*2);
		m->rotate(-90,glm::vec3(1.0f,0.0f,0.0f));

		d->addBone(bone,inverse);

		d->setPosition(0.0f,0.30f*2+1.4f+0.1f,0.5f*2);
		d->rotate(-90,glm::vec3(1.0f,0.0f,0.0f));
		link1b(m,0,inverse);
		link1b(d,0,inverse);
	}else
	{
		Bone* bone = (*(*(*(*bonebase)[0])[0])[0])[0];
		glm::mat4 inverse = bone->getInverseMatrix();

		m->addBone(bone,inverse);

		m->setPosition(0.0f,-0.30f*2-1.4f,0.5f*2);
		m->rotate(90,glm::vec3(1.0f,0.0f,0.0f));

		d->addBone(bone,inverse);
		d->setPosition(0.0f,-0.30f*2-1.4f-0.1f,0.5f*2);
		d->rotate(90,glm::vec3(1.0f,0.0f,0.0f));
		link1b(m,0,inverse);
		link1b(d,0,inverse);
	}
	base->addObject(m);
	base->addObject(d);
}
void Robot::doigt(bool droit, int index)
{
	Texture* t = ObjectAccessor::getObjMgr()->getTexture("../../src/img/bender.bmp");
	Mesh* d = CreateCylinder(0.02,0.02,0.14,20,20);
	Mesh* s = CreateSphere(0.02,10,10,M_PI);

	d->setTexture(t);
	s->setTexture(t);

	if(droit)
	{
		Bone* main =  (*(*(*(*bonebase)[1])[0])[0])[0];
		Bone* b1 = (*main)[index];
		Bone* b2 = (*b1)[0];
		Bone* b3 = (*b2)[0];

		glm::mat4 inverse_main = main->getInverseMatrix();
		glm::mat4 inverse1 = b1->getInverseMatrix();
		glm::mat4 inverse2 = b2->getInverseMatrix();
		glm::mat4 inverse3 = b3->getInverseMatrix();

		d->rotate(-90,glm::vec3(1.0f,0.0f,0.0f));
		//s->rotate(-90,glm::vec3(1.0f,0.0f,0.0f));
		switch(index)
		{
		case 0:
			d->setPosition(0.0f,2.1f,1.08f);
			s->setPosition(0.0f,2.24f,1.08f);
			break;
		case 1:
			d->setPosition(0.08*sin(2*M_PI/3),2.1f,1.0f+0.08*cos(2*M_PI/3));
			s->setPosition(0.08*sin(2*M_PI/3),2.24f,1.0f+0.08*cos(2*M_PI/3));
			break;
		case 2:
			d->setPosition(0.08*sin(-2*M_PI/3),2.1f,1.0f+0.08*cos(-2*M_PI/3));
			s->setPosition(0.08*sin(-2*M_PI/3),2.24f,1.0f+0.08*cos(-2*M_PI/3));
			break;
		}
		s->addBone(b3,inverse3);
		link1b(s,0,inverse3);
		d->addBone(main,inverse_main);
		d->addBone(b1,inverse1);
		d->addBone(b2,inverse2);
		d->addBone(b3,inverse3);
		link3b(d,0,1,2,0,0.06f);
		link3b(d,1,2,3,0.06,0.1f);
		link3b(d,2,3,-1,0.1,0.15f);
	}else
	{
		Bone* main =  (*(*(*(*bonebase)[0])[0])[0])[0];
		Bone* b1 = (*main)[index];
		Bone* b2 = (*b1)[0];
		Bone* b3 = (*b2)[0];

		glm::mat4 inverse_main = main->getInverseMatrix();
		glm::mat4 inverse1 = b1->getInverseMatrix();
		glm::mat4 inverse2 = b2->getInverseMatrix();
		glm::mat4 inverse3 = b3->getInverseMatrix();

		d->rotate(90,glm::vec3(1.0f,0.0f,0.0f));
		s->rotate(180,glm::vec3(1.0f,0.0f,0.0f));
		switch(index)
		{
		case 0:
			d->setPosition(0.0f,-2.1f,1.08f);
			s->setPosition(0.0f,-2.24f,1.08f);
			break;
		case 1:
			d->setPosition(0.08*sin(2*M_PI/3),-2.1f,1.0f+0.08*cos(2*M_PI/3));
			s->setPosition(0.08*sin(2*M_PI/3),-2.24f,1.0f+0.08*cos(2*M_PI/3));
			break;
		case 2:
			d->setPosition(0.08*sin(-2*M_PI/3),-2.1f,1.0f+0.08*cos(-2*M_PI/3));
			s->setPosition(0.08*sin(-2*M_PI/3),-2.24f,1.0f+0.08*cos(-2*M_PI/3));
			break;
		}
		s->addBone(b3,inverse3);
		link1b(s,0,inverse3);
		d->addBone(main,inverse_main);
		d->addBone(b1,inverse1);
		d->addBone(b2,inverse2);
		d->addBone(b3,inverse3);
		link3b(d,0,1,2,0,0.06f);
		link3b(d,1,2,3,0.06f,0.1f);
		link3b(d,2,3,-1,0.1f,0.15f);
	}
	base->addObject(s);
	base->addObject(d);
}

void Robot::tete()
{

	Bone* bonetete = (*bonebase)[4];
	Bone* boneeye1 = (*bonetete)[0];
	Bone* boneeye2 = (*bonetete)[1];
	Texture* t1 = ObjectAccessor::getObjMgr()->getTexture("../../src/img/bender.bmp");
	Texture* t = ObjectAccessor::getObjMgr()->getTexture("../../src/img/eyes.bmp");
	//Tête
	Mesh * m = CreateCylinder(0.3f, 0.3f,0.5f,20,20);
	m->setTexture(t1);
	Mesh * m2 = CreateSphere(0.3f,20,10, M_PI);

	m->addBone(bonetete,bonetete->getInverseMatrix());
	m2->addBone(bonetete,bonetete->getInverseMatrix());

	link1b(m,0,bonetete->getInverseMatrix());
	link1b(m2,0,bonetete->getInverseMatrix());

	m2->setTexture(t1);
	m->setPosition(0,0,1.4f);
	m2->setPosition(0,0,1.9f);
	m2->rotate(90,glm::vec3(1,0,0));

	base->addObject(m);
	base->addObject(m2);
	
	Mesh* eye1 = CreateSphere(0.1f,20,20);
	eye1->setTexture(t);
	Mesh* eye2 = CreateSphere(0.1f,20,20);
	eye2->setTexture(t);

	eye1->rotate(180,glm::vec3(0,0,1));
	eye2->rotate(180,glm::vec3(0,0,1));



	eye1->addBone(boneeye1,boneeye1->getInverseMatrix());
	eye2->addBone(boneeye2,boneeye2->getInverseMatrix());

	boneeye1->rotate(-40,glm::vec3(0,1,0));
	boneeye2->rotate(-40,glm::vec3(0,1,0));

	link1b(eye1,0,boneeye1->getInverseMatrix());
	link1b(eye2,0,boneeye2->getInverseMatrix());


	eye1->setPosition(0.3*cos(M_PI/8.0f),0.3*sin(M_PI/8.0f),1.75f);
	eye2->setPosition(0.3*cos(-M_PI/8.0f),0.3*sin(-M_PI/8.0f),1.75f);
	base->addObject(eye1);
	base->addObject(eye2);
}
void Robot::jambe()
{
	Bone* boneg0 = (*bonebase)[2];
	Bone* boned0 = (*bonebase)[3];
	Bone* boneg1 = (*boneg0)[0];
	Bone* boned1 = (*boned0)[0];
	Bone* boneg2 = (*boneg1)[0];
	Bone* boned2 = (*boned1)[0];
	glm::mat4 inversebase = bonebase->getInverseMatrix();
	glm::mat4 inverseg0 = boneg0->getInverseMatrix();
	glm::mat4 inversed0 = boned0->getInverseMatrix();
	glm::mat4 inverseg1 = boneg1->getInverseMatrix();
	glm::mat4 inversed1 = boned1->getInverseMatrix();
	glm::mat4 inverseg2 = boneg2->getInverseMatrix();
	glm::mat4 inversed2 = boned2->getInverseMatrix();
	Texture* t = ObjectAccessor::getObjMgr()->getTexture("../../src/img/bender.bmp");
	Mesh * j1 = CreateCylinder(0.1f,0.1f,1.4f,20,20);
	Mesh * j2 = CreateCylinder(0.1f,0.1f,1.4f,20,20);
	j1->rotate(180,glm::vec3(1,0,0));
	j2->rotate(180,glm::vec3(1,0,0));

	j1->addBone(bonebase,inversebase);
	j1->addBone(boneg0,inverseg0);
	j1->addBone(boneg1,inverseg1);
	j1->addBone(boneg2,inverseg2);

	j2->addBone(bonebase,inversebase);
	j2->addBone(boned0,inversed0);
	j2->addBone(boned1,inversed1);
	j2->addBone(boned2,inversed2);

	link3b(j1,0,1,2,0,0.7f);
	link3b(j1,1,2,3,0.7f,1.45f);


	link3b(j2,0,1,2,0,0.7f);
	link3b(j2,1,2,3,0.7f,1.45f);

	j1->setTexture(t);
	j2->setTexture(t);
	j1->setPosition(0,0.3f,0);
	j2->setPosition(0,-0.3f,0);
	base->addObject(j1);
	base->addObject(j2);

}

void Robot::pied()
{
	Bone* bone0 = (*(*(*bonebase)[2])[0])[0];
	Bone* bone1 = (*(*(*bonebase)[3])[0])[0];
	glm::mat4 inverse0 = bone0->getInverseMatrix();
	glm::mat4 inverse1 = bone1->getInverseMatrix();
	Texture* t = ObjectAccessor::getObjMgr()->getTexture("../../src/img/bender.bmp");
	Mesh* p1 = CreateSphere(0.14f,10,10,M_PI);
	Mesh* p2 = CreateSphere(0.14f,10,10,M_PI);
	p1->addBone(bone0,inverse0);
	p2->addBone(bone1,inverse1);
	link1b(p1,0,inverse0);
	link1b(p2,0,inverse1);
	p1->setTexture(t);
	p2->setTexture(t);
	p1->setPosition(0,0.3f,-1.45f);
	p2->setPosition(0,-0.3f,-1.45f);
	p1->rotate(90,glm::vec3(1,0,0));
	p2->rotate(90,glm::vec3(1,0,0));
	base->addObject(p1);
	base->addObject(p2);


	p1 = CreateDisk(0.14f,20);
	p2 = CreateDisk(0.14f,20);
	p1->addBone(bone0,inverse0);
	p2->addBone(bone1,inverse1);
	link1b(p1,0,inverse0);
	link1b(p2,0,inverse1);
	p1->setPosition(0,0.3f,-1.45f);
	p2->setPosition(0,-0.3f,-1.45f);
	base->addObject(p1);
	base->addObject(p2);
}
/*
Object* Robot::doigtB()
{
	Container* _base = new Container();
	Container* ct = new Container();
	ct->addCylinder(0.05f,0.05f,0.1,40,1);
	ct->rotate(90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addSphere(0.05,20,20,M_PI);
	ct->setPosition(0.1f,0.0f,0.0f);
	ct->rotate(-90*TORAD,glm::vec3(0.0f,0.0f,1.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.05,40);
	ct->rotate(90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	/*ct = new Container();
	ct->addCylinder(0.05,0.05,0.05,6,6,M_PI/6);
	ct->setPosition(-0.05f,0.0f,0.0f);
	ct->rotate(90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	ct->rotate(-M_PI/12,glm::vec3(0.0f,0.0f,1.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addCylinder(0.05,0.05,0.05,6,6,M_PI/6);
	ct->setPosition(-0.05f,0.0f,0.0f);
	ct->rotate(90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	ct->rotate(M_PI-M_PI/12,glm::vec3(0.0f,0.0f,1.0f));
	_base->addObject(ct);*


	


	Polygone* poly = new Polygone();
	poly->setColor(0xffff0000);
	float h = 0.05*cos(M_PI/12);
	float y = 0.05f*sin(M_PI/12);
	poly->addVertex(Vertex(-0.05f,y,h));
	poly->addVertex(Vertex(0.0f,y,h));
	poly->addVertex(Vertex(0.0f,y,-h));
	poly->addVertex(Vertex(-0.05f,y,-h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Vertex(-0.05f,-y,h));
	poly->addVertex(Vertex(0.0f,-y,h));
	poly->addVertex(Vertex(0.0f,-y,-h));
	poly->addVertex(Vertex(-0.05f,-y,-h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Vertex(-0.05f,-y,h));
	poly->addVertex(Vertex(0.0f,-y,h));
	poly->addVertex(Vertex(0.0f,y,h));
	poly->addVertex(Vertex(-0.05f,y,h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Vertex(-0.05f,-y,-h));
	poly->addVertex(Vertex(0.0f,-y,-h));
	poly->addVertex(Vertex(0.0f,y,-h));
	poly->addVertex(Vertex(-0.05f,y,-h));
	_base->addObject(poly);

	ct = new Container();
	ct->addCylinder(h,h,y*2,20,1,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,10,M_PI);//Cylinder(h/2,h/2,y*2,20,20,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,10,M_PI);
	ct->setPosition(-0.05f,-y,0.0f);
	ct->rotate(-90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);
	_base->setRepere(-0.05f,-y,0.0f);
	//_base->rotate(-45*TORAD,glm::vec3(0.0f,1.0f,0.0));
	return _base;
}
Object* Robot::doigt()
{
	Container* _base = new Container();
	Container* ct = new Container();
	ct->addCylinder(0.05f,0.05f,0.3,20,1);
	ct->rotate(90,glm::vec3(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.05,20);
	ct->setPosition(0.3f,0.0f,0.0f);
	ct->rotate(90,glm::vec3(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.05,20);
	ct->rotate(90,glm::vec3(0.0f,1.0f,0.0f));
	_base->addObject(ct);

	/*ct = new Container();
	ct->addCylinder(0.05,0.05,0.05,6,6,M_PI/6);
	ct->setPosition(-0.05f,0.0f,0.0f);
	ct->rotate(90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	ct->rotate(-M_PI/12,glm::vec3(0.0f,0.0f,1.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addCylinder(0.05,0.05,0.05,6,6,M_PI/6);
	ct->setPosition(-0.05f,0.0f,0.0f);
	ct->rotate(90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	ct->rotate(M_PI-M_PI/12,glm::vec3(0.0f,0.0f,1.0f));
	_base->addObject(ct);*


	


	Polygone* poly = new Polygone();
	poly->setColor(0xffff0000);
	float h = 0.05*cos(M_PI/12);
	float y = 0.05f*sin(M_PI/12);
	poly->addVertex(Vertex(-0.05f,y,h));
	poly->addVertex(Vertex(0.0f,y,h));
	poly->addVertex(Vertex(0.0f,y,-h));
	poly->addVertex(Vertex(-0.05f,y,-h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Vertex(-0.05f,-y,h));
	poly->addVertex(Vertex(0.0f,-y,h));
	poly->addVertex(Vertex(0.0f,-y,-h));
	poly->addVertex(Vertex(-0.05f,-y,-h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Vertex(-0.05f,-y,h));
	poly->addVertex(Vertex(0.0f,-y,h));
	poly->addVertex(Vertex(0.0f,y,h));
	poly->addVertex(Vertex(-0.05f,y,h));
	_base->addObject(poly);

	poly = new Polygone();
	poly->setColor(0xffff0000);
	poly->addVertex(Vertex(-0.05f,-y,-h));
	poly->addVertex(Vertex(0.0f,-y,-h));
	poly->addVertex(Vertex(0.0f,y,-h));
	poly->addVertex(Vertex(-0.05f,y,-h));
	_base->addObject(poly);

	ct = new Container();
	ct->addCylinder(h,h,y*2,10,1,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,10,M_PI);//Cylinder(h/2,h/2,y*2,20,20,M_PI);
	ct->setPosition(-0.05f,y,0.0f);
	ct->rotate(-90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(h,10,M_PI);
	ct->setPosition(-0.05f,-y,0.0f);
	ct->rotate(-90*TORAD,glm::vec3(0.0f,1.0f,0.0f));
	ct->rotate(90*TORAD,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);
	_base->setRepere(-0.05f,-y,0.0f);
	//_base->rotate(90*TORAD,glm::vec3(0.0f,1.0f,0.0));
	
	
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



Object* Robot::tete()
{
	Texture* t = ObjectAccessor::getObjMgr()->getTexture("../../src/img/bender.bmp");
	Container* _base = new Container();
	Container* ct = new Container();
	ct->addCylinder(0.3,0.3,0.5,40,1);
	if(t)
		ct->setTexture(t);
	_base->addObject(ct);

	ct = new Container();
	ct->addSphere(0.3f,20,20,M_PI);
	ct->setPosition(0.0,0.0,0.5f);
	ct->rotate(M_PI/2,glm::vec3(1.0f,0.0f,0.0f));
	if(t)
		ct->setTexture(t);
	_base->addObject(ct);

	ct = static_cast<Container*>(eye());
	ct->setPosition(0.3f*cos(M_PI/8.0f),0.3f*sin(M_PI/8.0f),0.35f);
	_base->addObject(ct);

	ct = static_cast<Container*>(eye());
	ct->setPosition(0.3f*cos(M_PI/8.0f),-0.3f*sin(M_PI/8.0f),0.35f);
	_base->addObject(ct);

	return _base;
}

Object* Robot::eye()
{
	Texture* t = ObjectAccessor::getObjMgr()->getTexture("../../src/img/eyes.bmp");
	Container* ct = new Container();
	ct->addSphere(0.1f,10,10);
	ct->setBind(false);
	ct->rotate(M_PI,glm::vec3(0,0,1.0f));
	if(t)
		ct->setTexture(t);
	return static_cast<Object*>(ct);
	
}

Object* Robot::old_bras()
{
	Container* _base = new Container();
	Box* b = new Box(glm::vec3(),glm::vec3(0.4f,0.03f,0.1f));
	_base->addObject(b);

	Container* ct = new Container();
	ct->addCylinder(0.03,0.03,0.05,40,1);
	ct->setPosition(0.435,-0.01,0.05);
	ct->rotate(-M_PI/2,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.03f,40);
	ct->setPosition(0.435,-0.01,0.05);
	ct->rotate(M_PI/2,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.03f,40);
	ct->setPosition(0.435,0.04,0.05);
	ct->rotate(-M_PI/2,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addSphere(0.06,20,20);
	ct->setPosition(-0.035,0.015,0.05);
	_base->addObject(ct);
	_base->setRepere(-0.035,0.03f/2,0.05);
	return _base;
}

Object* Robot::avant_bras()
{
	Container* _base = new Container();

	Box* b = new Box(glm::vec3(),glm::vec3(0.4f,0.03f,0.1f));
	_base->addObject(b);

	Container* ct = new Container();
	ct->addCylinder(0.06,0.06,0.05,40,1);
	ct->setPosition(-0.035,-0.01,0.05);
	ct->rotate(-M_PI/2,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addCylinder(0.03,0.03,0.05,40,1);
	ct->setPosition(-0.035,-0.01,0.05);
	ct->rotate(-M_PI/2,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);


	ct = new Container();
	ct->addCylinder(0.06,0.03,0.00,40,1);
	ct->setPosition(-0.035,-0.01,0.05);
	ct->rotate(M_PI/2,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	ct = new Container();
	ct->addCylinder(0.06,0.03,0.00,40,1);
	ct->setPosition(-0.035,0.04,0.05);
	ct->rotate(-M_PI/2,glm::vec3(1.0f,0.0f,0.0f));
	_base->addObject(ct);

	_base->setRepere(-0.035,0.00,0.05);

	ct->addSphere(0.2,20,20,M_PI);
	ct->rotate(M_PI_2,glm::vec3(0,0.0,1));

	return _base;
}


Object* Robot::bras_complete()
{
	Container* _base;
//	_base = (Container*)bras();
	_bras[0] = _base;
	Container* ct = (Container*)avant_bras();
	ct->setPosition(0.47f,0.0,0.0);
	_bras[1] = ct;
	_base->addObject(ct);
	return _base;
}

Object* Robot::mains()
{
	float y = 0.1f*sin(M_PI/12);
	float _y = (0.2f-(y+0.05f))/2;
	Container* _base = new Container();
	Polygone* poly  = new Polygone();
	poly->addVertex(Vertex(0.0f,0.0f,0.0f));
	poly->addVertex(Vertex(0.0f,0.05f,0.0f));
	poly->addVertex(Vertex(0.0f,0.05f,0.1f));
	poly->addVertex(Vertex(0.0f,0.0f,0.08f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Vertex(-0.1f,0.0f,0.08f));
	poly->addVertex(Vertex(-0.1f,0.05f,0.08f));
	poly->addVertex(Vertex(0.0f,0.05f,0.1f));
	poly->addVertex(Vertex(0.0f,0.0f,0.08f));
	_base->addObject(poly);

	for(int i = 0; i < 3; i++)
	{
		float offset = (y+_y*2)*i;
		poly  = new Polygone();
		poly->addVertex(Vertex(-0.1f,y+_y+0.05f+offset,0.08f));
		poly->addVertex(Vertex(-0.1f,y+0.05f+offset,0.08f));
		poly->addVertex(Vertex(0.0f,y+0.05f+offset,0.1f));
		poly->addVertex(Vertex(0.0f,y+_y+0.05f+offset,0.08f));
		_base->addObject(poly);
	}


	poly  = new Polygone();
	poly->addVertex(Vertex(-0.1f,0.55f+y,0.08f));
	poly->addVertex(Vertex(-0.1f,0.50f+y,0.08f));
	poly->addVertex(Vertex(0.0f,0.50f+y,0.1f));
	poly->addVertex(Vertex(0.0f,0.55f+y,0.08f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Vertex(-0.1f,0.2f,0.08f));
	poly->addVertex(Vertex(-0.1f,0.05f+y+_y,0.08f));
	poly->addVertex(Vertex(0.0f,0.05f+y+_y,0.08f));
	poly->addVertex(Vertex(0.0f,0.2f,0.1f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Vertex(-0.1f,0.35f,0.08f));
	poly->addVertex(Vertex(-0.1f,0.2f+y+_y,0.08f));
	poly->addVertex(Vertex(0.0f,0.2f+y+_y,0.08f));
	poly->addVertex(Vertex(0.0f,0.35f,0.1f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Vertex(-0.1f,0.5f,0.08f));
	poly->addVertex(Vertex(-0.1f,0.35f+y+_y,0.08f));
	poly->addVertex(Vertex(0.0f,0.35f+y+_y,0.08f));
	poly->addVertex(Vertex(0.0f,0.5f,0.1f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Vertex(0.0f,0.0f,0.08f));
	poly->addVertex(Vertex(-0.4f,0.0f,0.08f));
	poly->addVertex(Vertex(-0.4f,0.0f,0.0f));
	poly->addVertex(Vertex(0.0f,0.0f,0.0f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Vertex(-0.9f,0.1f,0.08f));
	poly->addVertex(Vertex(-0.4f,0.0f,0.08f));
	poly->addVertex(Vertex(-0.4f,0.0f,0.0f));
	poly->addVertex(Vertex(-0.9f,0.1f,0.0f));
	_base->addObject(poly);

	poly  = new Polygone();
	poly->addVertex(Vertex(0.0f,0.55f+y,0.08f));
	poly->addVertex(Vertex(-0.4f,0.55f+y,0.08f));
	poly->addVertex(Vertex(-0.4f,0.55f+y,0.0f));
	poly->addVertex(Vertex(0.0f,0.55f+y,0.0f));
	_base->addObject(poly);

	Container* ct = (Container*)doigt_complete();
	ct->setPosition(0.0f,0.05f,0.05f);
	ct->setPosition(ct->getPosition()-ct->getRepere());
	_base->addObject(ct);
	poly  = new Polygone();
	poly->addVertex(Vertex(0.0f,y+_y+0.05f,0.0f));
	poly->addVertex(Vertex(0.0f,y+0.05f,0.0f));
	poly->addVertex(Vertex(0.0f,y+0.05f,0.1f));
	poly->addVertex(Vertex(0.0f,y+_y+0.05f,0.08f));
	_base->addObject(poly);


	poly  = new Polygone();
	poly->addVertex(Vertex(0.0f,y+_y+0.05f,0.0f));
	poly->addVertex(Vertex(0.0f,0.2f,0.0f));
	poly->addVertex(Vertex(0.0f,0.2f,0.1f));
	poly->addVertex(Vertex(0.0f,y+_y+0.05f,0.08f));
	_base->addObject(poly);

	ct = (Container*)doigt_complete();
	ct->setPosition(0.0f,0.2f,0.05f);
	ct->setPosition(ct->getPosition()-ct->getRepere());
	_base->addObject(ct);

	poly  = new Polygone();
	poly->addVertex(Vertex(0.0f,y+_y+0.2f,0.0f));
	poly->addVertex(Vertex(0.0f,y+0.2f,0.0f));
	poly->addVertex(Vertex(0.0f,y+0.2f,0.1f));
	poly->addVertex(Vertex(0.0f,y+_y+0.2f,0.08f));
	_base->addObject(poly);


	poly  = new Polygone();
	poly->addVertex(Vertex(0.0f,y+_y+0.2f,0.0f));
	poly->addVertex(Vertex(0.0f,0.35f,0.0f));
	poly->addVertex(Vertex(0.0f,0.35f,0.1f));
	poly->addVertex(Vertex(0.0f,y+_y+0.2f,0.08f));
	_base->addObject(poly);

	ct = (Container*)doigt_complete();
	ct->setPosition(0.0f,0.35f,0.05f);
	ct->setPosition(ct->getPosition()-ct->getRepere());
	_base->addObject(ct);

	poly  = new Polygone();
	poly->addVertex(Vertex(0.0f,y+_y+0.35f,0.0f));
	poly->addVertex(Vertex(0.0f,y+0.35f,0.0f));
	poly->addVertex(Vertex(0.0f,y+0.35f,0.1f));
	poly->addVertex(Vertex(0.0f,y+_y+0.35f,0.08f));
	_base->addObject(poly);


	poly  = new Polygone();
	poly->addVertex(Vertex(0.0f,y+_y+0.35f,0.0f));
	poly->addVertex(Vertex(0.0f,0.5f,0.0f));
	poly->addVertex(Vertex(0.0f,0.5f,0.1f));
	poly->addVertex(Vertex(0.0f,y+_y+0.35f,0.08f));
	_base->addObject(poly);


	ct = (Container*)doigt_complete();
	ct->setPosition(0.0f,0.5f,0.05f);
	ct->setPosition(ct->getPosition()-ct->getRepere());
	_base->addObject(ct);

	poly  = new Polygone();
	poly->addVertex(Vertex(0.0f,0.5f+y,0.0f));
	poly->addVertex(Vertex(0.0f,0.55f+y,0.0f));
	poly->addVertex(Vertex(0.0f,0.55f+y,0.08f));
	poly->addVertex(Vertex(0.0f,0.5f+y,0.1f));
	_base->addObject(poly);




	return _base;
}

Object* Robot::jambe_complete()
{
	Container* _base;
//	_base = (Container*)bras();
	Container* ct = (Container*)avant_bras();
	ct->setPosition(0.47f,0.0,0.0);
	_base->addObject(ct);
	Container* _ct = static_cast<Container*>(pied());
	_ct->setPosition(0.47f,0.015,0.05);
	_ct->setRepere(-0.2*0.7f,0,0);
	_ct->setSize(0.7f);
	ct->addObject(_ct);
	return _base;
}
Object* Robot::pied()
{
	Container* _base = new Container();
	Container* ct = new Container();
	ct->addSphere(0.2,20,20,M_PI);
	ct->rotate(M_PI_2,glm::vec3(0,0.0,1));
	_base->addObject(ct);

	ct = new Container();
	ct->addDisk(0.2,20);
	ct->rotate(M_PI_2,glm::vec3(0,1.0,0));
	_base->addObject(ct);
	return _base;
}*/

Object* Robot::operator[] (int i)
{
	i %=12;
	if(i != i)
		return _bras[i];
	else
		return _doigt[i];
}
