
#include "Scene_demo.h"
#include "ObjectAccessor\ObjectAccessor.h"

Object* bouteille(glm::vec3 pos)
{
	Container* c = new Container(pos);
    Mesh* m;

	m = CreateCylinder(1.0,1.0,3.0,20,10);
	c->addObject(m);

	m = CreateSphere(1.0f,20.0,20.0);
	m->setPosition(0.0,0.0,3.0);
	c->addObject(m);

	m = CreateCylinder(0.5,0.4,1.5,20.0,10.0);
	m->setPosition(0.0,0.0,3.7f);
	c->addObject(m);

  /*  glPushMatrix();
    glRotatef(90.0, 1.0, 0.0 ,0.0);
    glTranslatef(0.0,0.0,-2.3);
    glutSolidTorus(0.1,0.35,20.0,20.0);
    glTranslatef(0.0,0.0,-0.2);
    glutSolidTorus(0.1,0.3,20.0,20.0);
    glPopMatrix();*/
	return c;
}
/*
Object* bague(glm::vec3 pos)
{

	Container* c = new Container(pos);
    Mesh* m;


    //lutSolidTorus(0.2,1.0,100.0,100.0);
    glPushMatrix();
    glTranslatef(0.0,1.5,0.0);
    glRotatef(90.0, 1.0, 0.0 ,0.0);
    glutSolidCone(1.0,0.5,100.0,5.0);
    glTranslatef(0.0,0.0,0.0);
    gluCylinder(parame,1.0,1.0,0.2,100.0,1.0);
    glPushMatrix();
    glScalef( 1.0, 1.0, 0.0);
    //attention
    glutSolidSphere(1.005,20.0,20.0);
    glPopMatrix();

	c->addObject(BagueB(glm::vec3(0.0,0.0,-0.1)));

}

Object* BagueB(glm::vec3 pos)
{
	Container* c = new Container(pos);
    Mesh* m;

	m = CreateBox(0.2,1.2,0.4);
	m->setPosition(-0.3,0,0);
	c->addObject(m);

	m = CreateBox(0.7,0.2,0.4);
	m->setPosition(0.0,0.5,0.0);
	c->addObject(m);

	m = CreateBox(0.9,0.2,0.4);
	m->setPosition(0.1,0.0,0.0);
	c->addObject(m);

	m = CreateBox(0.9,0.2,0.4);
	m->setPosition(0.1,-0.5,0.0);
	c->addObject(m);

	m = CreateBox(0.2,0.5,0.4);
	m->setPosition(0.25,0.25,0.0);
	c->addObject(m);

	m = CreateBox(0.2,0.5,0.4);
	m->setPosition(0.5,-0.25,0.0);
	c->addObject(m);

	return c;
}
/*
void futBiere()
{
    GLUquadric* params;
    params = gluNewQuadric();
    glPushMatrix();
    glRotatef(270.0, 1.0, 0.0 ,0.0);
    glTranslatef(0.0,0.0,1.5);
    glutSolidTorus(0.1,1.5,100.0,100.0);
    gluCylinder(params,1.5,1.0,1.5,100.0,1.0);
    glTranslatef(0.0,0.0,-1.5);
    glutSolidTorus(0.1,1.6,100.0,100.0);
    gluCylinder(params,1.5,1.5,1.5,100.0,1.0);
    glRotatef(180, 1.0, 0.0 ,0.0);
    gluCylinder(params,1.5,1.0,1.5,100.0,1.0);
    glPushMatrix();
    glTranslatef(0.0,0.0,-3.0);
    glScalef( 1.0, 1.0, 0.0);
    //attention
    glutSolidSphere(1.0,20.0,20.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,1.5);
    glScalef( 1.0, 1.0, 0.0);
    //attention
    glutSolidSphere(1.0,20.0,20.0);
    glPopMatrix();
    glTranslatef(0.0,0.0,-3.3);
    glTranslatef(0.0,0.7,0.0);
    gluCylinder(params,0.1,0.1,0.5,100.0,1.0);
    glTranslatef(0.0,-0.7,0.0);
    glScalef( 0.2,0.2,0.2);
    robinet();
    glPopMatrix();
}
void robinet()
{
    GLUquadric* params;
    params = gluNewQuadric();
    glutSolidTorus(0.5,1.5,100.0,8.0);
    gluCylinder(params,0.2,0.2,4.0,100.0,1.0);
    glPushMatrix();
    glTranslatef(0.0,1.0,0.0);
    glRotatef(90, 1.0, 0.0 ,0.0);
    gluCylinder(params,0.2,0.2,2.0,100.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.0,0.0,0.0);
    glRotatef(90, 1.0, 0.0 ,0.0);
    glRotatef(90, 0.0, 1.0 ,0.0);
    gluCylinder(params,0.2,0.2,2.0,100.0,1.0);
    glPopMatrix();
}

void cigarette()
{
    GLUquadric* params;
    params = gluNewQuadric();
    glColor3f(0.2,0.2,0.2);
    gluCylinder(params,0.25,0.25,0.2,100.0,1.0);
    glTranslatef(0.0,0.0,0.2);
    glColor3f(1.0,1.0,1.0);
    gluCylinder(params,0.25,0.25,3.0,100.0,1.0);
    glTranslatef(0.0,0.0,3.0);
    glColor3f(1.0,0.5,0.0);
    gluCylinder(params,0.25,0.25,1.0,100.0,1.0);
    glTranslatef(0.0,0.0,1.0);
    glPushMatrix();
    glScalef( 1.0, 1.0, 0.0);
    glColor3f(1.0,1.0,1.0);
    //glutSolidSphere(0.25,20.0,20.0);
    Sphere(0.25,20.0,20.0);
    glPopMatrix();
    glColor3f(1.0,0.0,0.0);
    glTranslatef(0.0,0.0,-4.2);
    glScalef( 1.0, 1.0, 0.5);
    glutSolidSphere(0.25,20.0,20.0);
    glColor3f(1.0,1.0,1.0);
}*/
Object* chaise(glm::vec3 pos)
{
	Texture* t1 = ObjectAccessor::getObjMgr()->getTexture("../../src/img/chaise1.bmp");
	Mesh* m;
	Container* c = new Container(pos); 

	//siege
	m = CreateBox(2.0,2.0,0.4);
	m->setTexture(t1);
	m->setPosition(0.0,0.0,1.7);
	c->addObject(m);

	//dossier
	m = CreateBox(2.0,0.4,1.0);
	m->setTexture(t1);
	m->setPosition(0.0,-0.75,3.9);
	c->addObject(m);

	//support dossier
	m = CreateCylinder(0.2,0.2,1.5,20.0,1.0);
	m->setTexture(t1);
	m->setPosition(0.0,-0.75,1.9);
	c->addObject(m);
	//pied

	m = CreateCylinder(0.2,0.2,1.5,20.0,1.0);
	m->setPosition(0.75,0.75,0);
	m->setTexture(t1);
	c->addObject(m);

	m = CreateCylinder(0.2,0.2,1.5,20.0,1.0);
	m->setPosition(0.75,-0.75,0);
	m->setTexture(t1);
	c->addObject(m);

	m = CreateCylinder(0.2,0.2,1.5,20.0,1.0);
	m->setPosition(-0.75,0.75,0);
	m->setTexture(t1);
	c->addObject(m);

	m = CreateCylinder(0.2,0.2,1.5,20.0,1.0);
	m->setPosition(-0.75,-0.75,0);
	m->setTexture(t1);
	c->addObject(m);

	return c;
}
Object* table(glm::vec3 pos)
{
	Texture* t1 = ObjectAccessor::getObjMgr()->getTexture("../../src/img/metal.bmp");
	Texture* t2 = ObjectAccessor::getObjMgr()->getTexture("../../src/img/table.bmp");
	Mesh* m;
	Container* c = new Container(pos); 

	m = CreateCylinder(2.0,0.2,0.5,20.0,10.0);
	c->addObject(m);
	m->setTexture(t1);

	m = CreateCylinder(0.2,0.2,3.3,20.0,1.0);
	m->setPosition(0.0,0.0,0.5);
	c->addObject(m);
	m->setTexture(t1);

	m = CreateBox(4.0,4.0,0.2);
	m->setPosition(0.0,0.0,4.0);
	c->addObject(m);
	m->setTexture(t2);
	return c;
}

Object* enstabcha(glm::vec3 pos)
{
	Container* m;
	Container* c = new Container(pos);
	m = static_cast<Container*>(table());
	c->addObject(m);

	m = static_cast<Container*>(chaise(glm::vec3(0.0,4.0,0.0)));
	m->rotate(180,glm::vec3(0,0,1));
	c->addObject(m);

	m = static_cast<Container*>(chaise(glm::vec3(0.0,-4.0,0.0)));
	c->addObject(m);
	return c;
}
/*
void scene()
{
    int i;
    glPushMatrix();
    glPushMatrix();
    glTranslatef(8.0,0.0,0.0);
    enstabcha();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8.0,0.0,0.0);
    enstabcha();
    glPopMatrix();
    glPushMatrix();
    enstabcha();
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glPushMatrix();
    glTranslatef(4.0,0.0,12.0);
    ensbanqtab();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8.0,0.0,12.0);
    ensbanqtab();
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.0,4.0,-15.0);
    bar();
    glPopMatrix();
    glPushMatrix();
    sol();
    mur();
    plafond();
    glPopMatrix();
    glPushMatrix();
    glScalef( 0.75, 0.75, 0.75);
    glTranslatef(-19.0,1.0,-11.0);
    for(i=0; i<9; i++)
    {
        chaise2();
        glTranslatef(5.0*1.25,0.0,0.0);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20.0,5.1,15.0);
    baril_cigarette();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(21.5,1.0,5.0);
    tas_de_parpaing();
    glPopMatrix();
    glPushMatrix();
    mur_fond();
    mur_porte();
    glPopMatrix();
}*/
Object* banquette(glm::vec3 pos)
{
	Mesh* m;
	Texture* t1 = ObjectAccessor::getObjMgr()->getTexture("../../src/img/banquette.bmp");
	Texture* t2 = ObjectAccessor::getObjMgr()->getTexture("../../src/img/cousin banquette.bmp");
	Container* c = new Container(pos); 


	m = CreateBox(4.0,8.0,2.0);
	m->setTexture(t1);
	c->addObject(m);


	m = CreateBox(1.0,8.0,3.0);
	m->setPosition(1.5,0.0,2.0);
	m->setTexture(t1);
	c->addObject(m);

	m = CreateBox(0.8*3.5,0.8*8.0,0.8*0.5);
	m->setPosition(-0.5,0.0,1.0);
	m->setTexture(t2);
	c->addObject(m);

	m = CreateBox(0.8,0.8*8.0,0.8*2.2);
	m->setPosition(1.3,0.0,2.3);
	m->setTexture(t2);
	c->addObject(m);

	return c;
}

Object* ensbanqtab(glm::vec3 pos)
{
	Container* m;
	Container* c = new Container(pos);
	m = static_cast<Container*>(table(glm::vec3(4.0,0,0)));
	c->addObject(m);

	m = static_cast<Container*>(table(glm::vec3(4.0,4.0,0)));
	c->addObject(m);


	m = static_cast<Container*>(banquette(glm::vec3(0.0,2.0,1.0)));
	m->rotate(180,glm::vec3(0,0,1));
	c->addObject(m);

	m = static_cast<Container*>(banquette(glm::vec3(8.0,2.0,1.0)));
	c->addObject(m);

	return c;
}
#define COEF 0.75
Object* bar(glm::vec3 pos)
{
	Mesh* m;
	Texture* t1 = ObjectAccessor::getObjMgr()->getTexture("../../src/img/chaise1.bmp");
	Container* c = new Container(pos); 

	m = CreateBox(48.0,4.0,10.0*COEF);
	m->setPosition(0.0,-1.0,0.0);
	m->setTexture(t1);
	c->addObject(m);

	/*m = CreateCylinder(0.1,0.1,48.0,20.0,1.0);
	m->setPosition(-24.0,1.0,5.0);
	m->rotate(90.0, glm::vec3(0.0,1.0,0.0));
	c->addObject(m);

	m = CreateCylinder(0.2,0.2,48.0,20.0,1.0);
	m->setPosition(-24.0,2.0,4.0);
	m->rotate(90.0, glm::vec3(0.0, 1.0,0.0));
	c->addObject(m);

	m = CreateCylinder(0.2,0.1,1.0,20.0,1.0);
	m->setPosition(0.0,1.0,4.0);
	m->rotate(90.0, glm::vec3(0.0, 1.0,0.0));
	c->addObject(m);

	m = CreateCylinder(0.2,0.1,1.0,20.0,1.0);
	m->setPosition(-15.0,1.0,4.0);
	m->rotate(90.0, glm::vec3(0.0, 1.0,0.0));
	c->addObject(m);



	m = CreateCylinder(0.2,0.1,1.0,20.0,1.0);
	m->setPosition(15.0,1.0,4.0);
	m->rotate(90.0, glm::vec3(0.0, 1.0,0.0));
	c->addObject(m);*/



	m = CreateBox(48.0,1.0,1.0);
	m->setPosition(0.0,1.0,-4.0);
	m->setTexture(t1);
	m->rotate(45.0, glm::vec3(1.0, 0.0,0.0));
	c->addObject(m);

	return c;
	/*

    glPushMatrix();
    glScalef(1.0,0.75,1.0);

    //evier
    glPushMatrix();
    glTranslatef(0.0,2.0,-5.25);
    glRotatef(90.0, -1.0, 0.0 ,0.0);
    glRotatef(180.0, 0.0, 0.0 ,1.0);
    glScalef( 1.0,1.0,1.0);
    ens_evier();
    glPopMatrix();
    //plan de travail
    glPushMatrix();
    glTranslatef(4.0,3.5,-3.0);
    glRotatef(90.0, -1.0, 0.0 ,0.0);
    glBegin(GL_POLYGON) ;
    glVertex2f(0.0F,0.0F) ;
    glVertex2f(0.0F,4.2F) ;
    glVertex2f(20.0F,4.2F) ;
    glVertex2f(20.0F,0.0F) ;
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-24.0,3.5,-3.0);
    glRotatef(90.0, -1.0, 0.0 ,0.0);
    glBegin(GL_POLYGON) ;
    glVertex2f(0.0F,0.0F) ;
    glVertex2f(0.0F,4.2F) ;
    glVertex2f(20.0F,4.2F) ;
    glVertex2f(20.0F,0.0F) ;
    glEnd();
    glPopMatrix();
    //rebord plan de travail
    glPushMatrix();
    glTranslatef(-24.0,3.3,-7.2);
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    gluCylinder(params,0.2,0.2,48.0,50.0,1.0);
    glPopMatrix();
    //étagère haut
    glPushMatrix();
    glTranslatef(0.0,-0.5,-5.0);
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    //glScalef( 4.2,0.2,48.0);
    cube(4.2,0.2,48.0);
    glPopMatrix();
    //étagère bas
    glPushMatrix();
    glTranslatef(0.0,-4.0,-5.0);
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    //glScalef( 4.2,0.2,48.0);
    cube(4.2,0.2,48.0);
    glPopMatrix();
    //cache bas
    glPushMatrix();
    glTranslatef(0.0,-4.5,-6.8);
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    //glScalef( 0.2,1.0,48.0);
    cube(0.2,1.0,48.0);
    glPopMatrix();
    //accesoire
    glPushMatrix();
    glTranslatef(1.0,0.25,-4.0);
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    glRotatef(4.5, 1.0, 0.0 ,0.0);
    glScalef( 0.2,0.2,0.2);
    batte_cloute();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0,-3.25,-4.0);
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    glRotatef(4.5, 1.0, 0.0 ,0.0);
    glScalef( 0.2,0.2,0.2);
    batte_baseball();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(23.0,-0.4,-6.0);
    glRotatef(90.0, -1.0, 0.0 ,0.0);
    glScalef(0.25,0.25,0.25);
    for(i=0; i<9; i++)
    {
        verre1();
        glTranslatef(-4.0,0.0,0.0);
    }
    glTranslatef(4.0,-5.0,0.0);
    for(i=0; i<9; i++)
    {
        verre1();
        glTranslatef(4.0,0.0,0.0);
    }
    glTranslatef(-4.0,-5.0,0.0);
    for(i=0; i<9; i++)
    {
        verre1();
        glTranslatef(-4.0,0.0,0.0);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(23.0,-1.9,-6.0);
    //glRotatef(90.0, -1.0, 0.0 ,0.0);
    glScalef(0.25,0.25,0.25);
    for(i=0; i<9; i++)
    {
        verre2();
        glTranslatef(-4.0,0.0,0.0);
    }
    glTranslatef(4.0,0.0,5.0);
    for(i=0; i<9; i++)
    {
        verre2();
        glTranslatef(4.0,0.0,0.0);
    }
    glTranslatef(-4.0,0.0,5.0);
    for(i=0; i<9; i++)
    {
        verre2();
        glTranslatef(-4.0,0.0,0.0);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(14.0,-0.4,-6.5);
    glRotatef(90.0, -1.0, 0.0 ,0.0);
    glScalef(0.25,0.25,0.25);
    for(i=0; i<9; i++)
    {
        verre3();
        glTranslatef(-4.0,0.0,0.0);
    }
    glTranslatef(4.0,-5.0,0.0);
    for(i=0; i<9; i++)
    {
        verre3();
        glTranslatef(4.0,0.0,0.0);
    }
    glTranslatef(-4.0,-5.0,0.0);
    for(i=0; i<9; i++)
    {
        verre3();
        glTranslatef(-4.0,0.0,0.0);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(14.0,-3.9,-6.5);
    glRotatef(90.0, -1.0, 0.0 ,0.0);
    glScalef(0.4,0.4,0.4);
    for(i=0; i<9; i++)
    {
        verre4();
        glTranslatef(-2.2,0.0,0.0);
    }
    glTranslatef(2.2,-2.5,0.0);
    for(i=0; i<9; i++)
    {
        verre4();
        glTranslatef(2.2,0.0,0.0);
    }
    glTranslatef(-2.2,-2.5,0.0);
    for(i=0; i<9; i++)
    {
        verre4();
        glTranslatef(-2.2,0.0,0.0);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.0,-2.4,-6.5);
    glScalef(0.5,0.5,0.5);
    for(i=0; i<16; i++)
    {
        bouteille();
        glTranslatef(-3.0,0.0,0.0);
    }
    glTranslatef(3.0,0.0,2.5);
    for(i=0; i<16; i++)
    {
        bouteille();
        glTranslatef(3.0,0.0,0.0);
    }
    glTranslatef(-3.0,0.0,2.5);
    for(i=0; i<16; i++)
    {
        bouteille();
        glTranslatef(-3.0,0.0,0.0);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2.5,1.1,-6.5);
    glScalef(0.5,0.5,0.5);
    for(i=0; i<15; i++)
    {
        bouteille();
        glTranslatef(-3.0,0.0,0.0);
    }
    glTranslatef(3.0,0.0,2.5);
    for(i=0; i<15; i++)
    {
        bouteille();
        glTranslatef(3.0,0.0,0.0);
    }
    glTranslatef(-3.0,0.0,2.5);
    for(i=0; i<15; i++)
    {
        bouteille();
        glTranslatef(-3.0,0.0,0.0);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,5.0,-1.0);
    //glRotatef(90.0, -1.0, 0.0 ,0.0);
    glScalef(0.5,0.5,0.5);
    cendrier_cigar();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-10.0,5.0,-1.0);
    glRotatef(90.0, -1.0, 0.0 ,0.0);
    glScalef(0.5,0.5,0.5);
    cendrier();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(10.0,6.5,-1.0);
    //glRotatef(90.0, -1.0, 0.0 ,0.0);
    glScalef(0.5,0.5,0.5);
    bouteille();
    glPopMatrix();
    glPopMatrix();*/

}
#define COEF2 0.8
Object* ampoule(glm::vec3 pos)
{
	Container* c = new Container(pos);
	Mesh* m;

	m = CreateSphere(COEF2*1.5,20,20);
	m->setPosition(0,0,0.5);
	c->addObject(m);

	m = CreateCylinder(COEF2*0.5,COEF2*0.5,COEF2*1.0,20.0,1.0);
	m->setPosition(0,0,-1.60+0.25*COEF2);
	c->addObject(m);

	m = CreateCylinder(COEF2*0.25,COEF2*0.5,COEF2*0.25,20.0,10.0);
	m->setPosition(0,0,-1.60);
	c->addObject(m);

	m = CreateSphere(COEF2*0.25,20.0,20.0);
	m->setPosition(0,0,-1.60);
	c->addObject(m);
	return c;
}


Object* lustre(glm::vec3 pos)
{
	Object* amp;
	Container* c = new Container(pos);
	Mesh* m;

	m = CreateCylinder(5.0*COEF2,0.0*COEF2,3.0*COEF2,20.0,10.0);
	c->addObject(m);

	m = CreateCylinder(0.1*COEF2,0.1*COEF2,3.0*COEF2,20.0,1.0);
	m->setPosition(0.0,0.0,2.8);
	c->addObject(m);

	amp = ampoule(glm::vec3(0,0,0.5));
	amp->rotate(180,glm::vec3(1,0,0));
	c->addObject(amp);

	return c;
}/*
void ens_evier()
{
    GLUquadric* params;
    params = gluNewQuadric();
    //bac
    glPushMatrix();
    //glRotatef(90.0, 1.0, 0.0 ,0.0);
    glRotatef(45.0, 0.0, 0.0 ,1.0);
    gluCylinder(params,1.4,2.0,1.5,4.0,1.0);
    glPopMatrix();
    //fond
    glPushMatrix();
    //glRotatef(45.0, 0.0, 0.0 ,1.0);
    glBegin(GL_POLYGON) ;
    glVertex2f(-1.0F,-1.0F) ;
    glVertex2f(-1.0F,1.0F) ;
    glVertex2f(1.0F,1.0F) ;
    glVertex2f(1.0F,-1.0F) ;
    glEnd() ;
    glPopMatrix();
    //bouchon
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    glScalef(1.0,1.0,0.5);
    glutSolidSphere(0.25,20.0,20.0);
    glPopMatrix();
    //tube évacuation
    glPushMatrix();
    glTranslatef(0.0,0.0,-7.0);
    gluCylinder(params,0.25,0.25,7.0,9.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,1.5);
    glRotatef(45.0, 0.0, 0.0 ,1.0);
    glutSolidTorus(0.1,2.0,4.0,4.0);
    glPopMatrix();
    //plan de travail
    glPushMatrix();
    glTranslatef(-4.3,-4.3,1.5);
    glScalef(1.9,1.9,1.0);
    glBegin(GL_POLYGON) ;
    glVertex2f(0.0F,1.25F) ;
    glVertex2f(4.5F,1.25F) ;
    glVertex2f(4.5F,1.5F) ;
    glVertex2f(0.0F,1.5F) ;
    glEnd();
    glBegin(GL_POLYGON) ;
    glVertex2f(0.0F,3.0F) ;
    glVertex2f(4.5F,3.0F) ;
    glVertex2f(4.5F,3.5F) ;
    glVertex2f(0.0F,3.5F) ;
    glEnd() ;
    glBegin(GL_POLYGON) ;
    glVertex2f(0.0F,1.5F) ;
    glVertex2f(1.5F,1.5F) ;
    glVertex2f(1.5F,3.0F) ;
    glVertex2f(0.0F,3.0F) ;
    glEnd() ;
    glBegin(GL_POLYGON) ;
    glVertex2f(3.0F,1.5F) ;
    glVertex2f(4.5F,1.5F) ;
    glVertex2f(4.5F,3.0F) ;
    glVertex2f(3.0F,3.0F) ;
    glEnd() ;
    glPopMatrix();
    //robinet
    glPushMatrix();
    glTranslatef(0.0,2.0,1.5);
    gluCylinder(params,0.1,0.1,1.5,20.0,1.0);
    glTranslatef(0.0,0.0,1.5);
    glutSolidSphere(0.2,8.0,8.0);
    glTranslatef(0.0,-1.0,0.0);
    glPushMatrix();
    //glScalef(0.2,2.0,0.1);
    cube(0.2,2.0,0.1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,-0.9,-0.1);
    gluCylinder(params,0.05,0.05,0.1,20.0,1.0);
    glPopMatrix();
    glPopMatrix();
    //eau chaude
    glPushMatrix();
    glTranslatef(-1.0,2.0,1.75);
    //glColor3f(1.0,0.0,0.0);
    gluCylinder(params,0.1,0.2,0.2,6.0,1.0);
    glPushMatrix();
    glScalef(1.0,1.0,0.1);
    glutSolidSphere(0.1,6.0,6.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,0.2);
    glScalef(1.0,1.0,0.1);
    glutSolidSphere(0.2,6.0,6.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,-0.25);
    gluCylinder(params,0.05,0.05,0.25,20.0,1.0);
    glPopMatrix();
    glPopMatrix();
    //eau froide
    glPushMatrix();
    glTranslatef(1.0,2.0,1.75);
    //glColor3f(0.0,0.0,1.0);
    gluCylinder(params,0.1,0.2,0.2,6.0,1.0);
    glPushMatrix();
    glScalef(1.0,1.0,0.1);
    glutSolidSphere(0.1,6.0,6.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,0.2);
    glScalef(1.0,1.0,0.1);
    glutSolidSphere(0.2,6.0,6.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,-0.25);
    gluCylinder(params,0.05,0.05,0.25,20.0,1.0);
    glPopMatrix();
    glPopMatrix();
}
void verre1()
{
    glPushMatrix();
    glBegin(GL_POLYGON) ;
    glVertex2f(1.0F,0.0F);
    glVertex2f(2.0F,0.0F);
    glVertex2f(3.0F,1.0F);
    glVertex2f(3.0F,2.0F);
    glVertex2f(2.0F,3.0F);
    glVertex2f(1.0F,3.0F);
    glVertex2f(0.0F,2.0F);
    glVertex2f(0.0F,1.0F);
    glEnd() ;
    //face 1
    glBegin(GL_POLYGON) ;
    glVertex3f(1.0F,0.0F,0.0F);
    glVertex3f(2.0F,0.0F,0.0F);
    glVertex3f(2.0F,0.0F,3.0F);
    glVertex3f(1.0F,0.0F,3.0F);
    glEnd() ;
    //face 2
    glBegin(GL_POLYGON) ;
    glVertex3f(2.0F,0.0F,0.0F);
    glVertex3f(3.0F,1.0F,0.0F);
    glVertex3f(3.0F,1.0F,3.0F);
    glVertex3f(2.0F,0.0F,3.0F);
    glEnd() ;
    //face 3
    glBegin(GL_POLYGON) ;
    glVertex3f(3.0F,1.0F,0.0F);
    glVertex3f(3.0F,2.0F,0.0F);
    glVertex3f(3.0F,2.0F,3.0F);
    glVertex3f(3.0F,1.0F,3.0F);
    glEnd() ;
    //face 4
    glBegin(GL_POLYGON) ;
    glVertex3f(3.0F,2.0F,0.0F);
    glVertex3f(2.0F,3.0F,0.0F);
    glVertex3f(2.0F,3.0F,3.0F);
    glVertex3f(3.0F,2.0F,3.0F);
    glEnd() ;
    //face 5
    glBegin(GL_POLYGON) ;
    glVertex3f(2.0F,3.0F,0.0F);
    glVertex3f(1.0F,3.0F,0.0F);
    glVertex3f(1.0F,3.0F,3.0F);
    glVertex3f(2.0F,3.0F,3.0F);
    glEnd() ;
    //face 6
    glBegin(GL_POLYGON) ;
    glVertex3f(1.0F,3.0F,0.0F);
    glVertex3f(0.0F,2.0F,0.0F);
    glVertex3f(0.0F,2.0F,3.0F);
    glVertex3f(1.0F,3.0F,3.0F);
    glEnd() ;
    //face 7
    glBegin(GL_POLYGON) ;
    glVertex3f(0.0F,2.0F,0.0F);
    glVertex3f(0.0F,1.0F,0.0F);
    glVertex3f(0.0F,1.0F,3.0F);
    glVertex3f(0.0F,2.0F,3.0F);
    glEnd() ;
    //face 8
    glBegin(GL_POLYGON) ;
    glVertex3f(0.0F,1.0F,0.0F);
    glVertex3f(1.0F,0.0F,0.0F);
    glVertex3f(1.0F,0.0F,3.0F);
    glVertex3f(0.0F,1.0F,3.0F);
    glEnd() ;
    glPopMatrix();
}
void verre2()
{
    GLUquadric* params;
    params = gluNewQuadric();
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0 ,0.0);
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    gluCylinder(params,1.0,1.0,3.0,20.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,3.0);
    gluCylinder(params,1.0,0.1,2.0,20.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,5.0);
    gluCylinder(params,0.1,0.1,2.0,20.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,7.0);
    gluCylinder(params,0.1,1.0,1.0,20.0,1.0);
    glPopMatrix();
    glPopMatrix();

}
void verre3()
{
    GLUquadric* params;
    params = gluNewQuadric();
    glPushMatrix();
    //glColor3f(0.2,0.2,0.2);
    gluDisk(params,0.0,1.0,20.0,1.0);
    //glColor3f(1.0,0.2,0.2);
    gluCylinder(params,1.0,1.0,3.0,20.0,1.0);
    glPopMatrix();
}
void verre4()
{
    int i;
    GLUquadric* params;
    params = gluNewQuadric();
    glPushMatrix();
    gluDisk(params,0.0,1.0,20.0,1.0);
    gluCylinder(params,1.0,1.0,0.2,20.0,1.0);
    glTranslatef(0.0,0.0,0.1);
    gluDisk(params,0.0,1.0,20.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,0.1);
    for(i=0; i<10; i++)
    {
        glTranslatef(0.0,0.0,0.2);
        glutSolidTorus(0.1,0.9,20.0,20.0);
    }
    glPopMatrix();
}
void batte_baseball()
{
    GLUquadric* params;
    params = gluNewQuadric();
    glPushMatrix();
    glutSolidSphere(3.0,20.0,20.0);
    glPopMatrix();
    glPushMatrix();
    gluCylinder(params,3.005,0.75,20.0,20.0,1.0);
    glTranslatef(0.0,0.0,20.0);
    gluCylinder(params,0.75,0.75,5.0,20.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,25.0);
    glutSolidTorus(0.4,0.75,100.0,100.0);
    glPopMatrix();
}
void clou()
{
    GLUquadric* params;
    params = gluNewQuadric();
    glPushMatrix();
    gluCylinder(params,0.5,0.5,0.1,20.0,1.0);
    gluDisk(params,0.0,0.5,20.0,1.0);
    glTranslatef(0.0,0.0,0.1);
    gluDisk(params,0.0,0.5,20.0,1.0);
    glPopMatrix();
    //piquant
    glPushMatrix();
    gluCylinder(params,0.3,0.0,5.0,20.0,1.0);
    glPopMatrix();
}
void batte_cloute()
{
    batte_baseball();
    //tete clou
    glPushMatrix();
    glTranslatef(-3.5,0.0,0.0);
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    glScalef( 2.0, 2.0, 2.0);
    clou();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3.5,0.0,2.0);
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    glScalef( 2.0, 2.0, 2.0);
    clou();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3.5,0.0,4.0);
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    glScalef( 2.0, 2.0, 2.0);
    clou();
    glPopMatrix();
}
void parpaing()
{
    glPushMatrix();
    //glScalef(7.2,1.8,0.2);
    cube(7.2,1.8,0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,2.0);
    //glScalef(7.2,1.8,0.2);
    cube(7.2,1.8,0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,1.0);
    //glScalef(6.8,1.8,0.2);
    cube(6.8,1.8,0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3.3,0.0,1.0);
    //glScalef(0.2,1.8,2.0);
    cube(0.2,1.8,2.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.3,0.0,1.0);
    //glScalef(0.2,1.8,2.0);
    cube(0.2,1.8,2.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.3,0.0,1.0);
    //glScalef(0.2,1.8,2.0);
    cube(0.2,1.8,2.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3.3,0.0,1.0);
    //glScalef(0.2,1.8,2.0);
    cube(0.2,1.8,2.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,-0.8,1.0);
    //glScalef(6.8,0.2,2.0);
    cube(6.8,0.2,2.0);
    glPopMatrix();
}
void tas_de_parpaing()
{
    glPushMatrix();
    parpaing();
    glTranslatef(0.0,0.0,-2.5);
    parpaing();
    glTranslatef(0.0,0.0,-2.5);
    parpaing();
    glPopMatrix();
    glPushMatrix();
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    glTranslatef(1.5,1.8,1.5);
    parpaing();
    glTranslatef(0.0,0.0,-2.5);
    parpaing();
    glTranslatef(0.0,0.0,-2.5);
    parpaing();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,3.6,0.0);
    parpaing();
    glTranslatef(0.0,0.0,-2.5);
    parpaing();
    glTranslatef(0.0,0.0,-2.5);
    parpaing();
    glPopMatrix();
    glPushMatrix();
    glRotatef(90.0, 0.0, 1.0 ,0.0);
    glTranslatef(1.5,5.4,1.5);
    parpaing();
    glTranslatef(0.0,0.0,-2.5);
    parpaing();
    glTranslatef(0.0,0.0,-2.5);
    parpaing();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5.0,2.7,0.0);
    glRotatef(90.0, 0.0, 0.0 ,1.0);
    parpaing();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5.0,3.05,-4.0);
    glRotatef(90.0, 0.0, 0.0 ,1.0);
    glRotatef(45.0, 0.0, -1.0 ,0.0);
    parpaing();
    glPopMatrix();
}
void baril()
{
    GLUquadric* params;
    params = gluNewQuadric();
    glPushMatrix();
    gluCylinder(params,2.0,2.0,5.0,20.0,1.0);
    gluDisk(params,0.0,2.0,20.0,1.0);
    glTranslatef(0.0,0.0,5.0);
    gluDisk(params,0.0,2.0,20.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5,0.0,-0.2);
    gluCylinder(params,0.2,0.2,0.2,20.0,1.0);
    gluDisk(params,0.0,0.2,20.0,1.0);
    glRotatef(90.0, 1.0, 0.0 ,0.0);
    glutSolidTorus(0.025,0.1,100.0,100.0);
    glPopMatrix();
    glPushMatrix();
    glutSolidTorus(0.1,2.0,100.0,100.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,5.0);
    glutSolidTorus(0.1,2.0,100.0,100.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,1.25);
    glutSolidTorus(0.1,2.0,100.0,100.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,3.75);
    glutSolidTorus(0.1,2.0,100.0,100.0);
    glPopMatrix();
}
void baril_cigarette()
{
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0 ,0.0);
    baril();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.12,-2.0);
    glRotatef(15.0, 1.0, 0.0 ,0.0);
    glScalef(0.1,0.1,0.1);
    cigarette();
    glPopMatrix();
}
void cendrier()
{
    GLUquadric* params;
    params = gluNewQuadric();
    glPushMatrix();
    gluCylinder(params,2.0,2.0,0.5,20.0,1.0);
    gluCylinder(params,1.8,1.8,0.5,20.0,1.0);
    gluDisk(params,0.0,2.0,20.0,1.0);
    glTranslatef(0.0,0.0,0.5);
    gluDisk(params,1.8,2.0,20.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,0.5);
    glPushMatrix();
    glTranslatef(0.2,1.875,0.0);
    glutSolidSphere(0.1,20.0,20.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.2,1.875,0.0);
    glutSolidSphere(0.1,20.0,20.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.2,-1.875,0.0);
    glutSolidSphere(0.1,20.0,20.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.2,-1.875,0.0);
    glutSolidSphere(0.1,20.0,20.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.875,0.2,0.0);
    glutSolidSphere(0.1,20.0,20.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.875,-0.2,0.0);
    glutSolidSphere(0.1,20.0,20.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.875,-0.2,0.0);
    glutSolidSphere(0.1,20.0,20.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.875,0.2,0.0);
    glutSolidSphere(0.1,20.0,20.0);
    glPopMatrix();
    glPopMatrix();
}
void cendrier_cigar()
{
    glPushMatrix();
    glRotatef(90.0, -1.0, 0.0 ,0.0);
    cendrier();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.12,-0.05);
    glRotatef(15.0, -1.0, 0.0 ,0.0);
    glScalef(0.5,0.5,0.5);
    cigarette();
    glPopMatrix();
}*/
Object* sol()
{
	Texture* t = TextureMgr::getTextureMgr()->getTexture("../../src/img/sol.bmp");
	Mesh* m;
	m = new Mesh();
	m->setTexture(t);
	m->addVertex(new Vertex(-22.0F,-35.0F,0.0F,0,0,glm::vec3(0,0,1)));
	m->addVertex(new Vertex(26.0F,-35.0F,0.0F,1,0,glm::vec3(0,0,1)));
	m->addVertex(new Vertex(26.0F,18.0F,0.0F,1,1,glm::vec3(0,0,1)));
	m->addVertex(new Vertex(-22.0F,18.0F,0.0F,0,1,glm::vec3(0,0,1)));
	m->addFace(Face(0,1,2));
	m->addFace(Face(0,2,3));
	return m;
}
Object* mur()
{
	
	Texture* t = TextureMgr::getTextureMgr()->getTexture("../../src/img/interieur.bmp");
	Container* c = new Container();
	Mesh* m;

	m = CreateBox(1.0,53.0,25.0);
	m->setPosition(-22.5,-8.5,12.5);
	m->setTexture(t);
	c->addObject(m);

	m = CreateBox(1.0,53.0,25.0);
	m->setPosition(26.5,-8.5,12.5);
	m->setTexture(t);
	c->addObject(m);
	return c;
}
Object* plafond()
{
	Texture* t = TextureMgr::getTextureMgr()->getTexture("../../src/img/interieur.bmp");
	Container* c = new Container();
	Mesh* m;
	m = new Mesh();
	m->setTexture(t);
	m->addVertex(new Vertex(-22.0F,-35.0F,25.0F,0,0,glm::vec3(0,0,-1)));
	m->addVertex(new Vertex(26.0F,-35.0F,25.0F,0,1,glm::vec3(0,0,-1)));
	m->addVertex(new Vertex(26.0F,18.0F,25.0F,1,0,glm::vec3(0,0,-1)));
	m->addVertex(new Vertex(-22.0F,18.0F,25.0F,1,1,glm::vec3(0,0,-1)));
	m->addFace(Face(0,1,2));
	m->addFace(Face(0,2,3));
	c->addObject(m);


	c->addObject(lustre(glm::vec3(0.0,10.0,22.75)));
	c->addObject(lustre(glm::vec3(0.0,-25.0,22.75)));
	c->addObject(lustre(glm::vec3(0.0,-7.5,22.75)));
	return c;
}
Object* mur_porte()
{
	Texture* t = TextureMgr::getTextureMgr()->getTexture("../../src/img/interieur.bmp");
	Container* c = new Container(glm::vec3(5.0,18.5,12.5));
	Mesh* m;

	m = CreateBox(43,1.0,25.0);
	m->setPosition(0.5,0,0);
	m->setTexture(t);
	c->addObject(m);

	c->addObject(porte(glm::vec3(-24.5,0.0,-12.5)));
	return c;
}
Object* mur_fond()
{
	Container* c = new Container();
	Mesh* m;
	Texture* t = TextureMgr::getTextureMgr()->getTexture("../../src/img/interieur.bmp");

	m = CreateBox(50.0, 1.0, 25.0);
	m->setPosition(2.0,-35.5,12.5);
	m->setTexture(t);
	c->addObject(m);
	return c;
}
Object* porte(glm::vec3 pos)
{
	Container* c = new Container(pos);
	Mesh* m;
	Texture* t = TextureMgr::getTextureMgr()->getTexture("../../src/img/interieur.bmp");
	m = CreateBox(5.0, 0.8, 10.0);
	m->setPosition(0.0,0.0,5.0);
	
	c->addObject(m);

	m = CreateCylinder(0.1,0.1,1.2,20.0,1.0);
	m->rotate(-90,glm::vec3(1,0,0));
	m->setPosition(2.0,-0.6,5.0);
	c->addObject(m);

	//glScalef(1.0,1.0,0.5);
	m = CreateSphere(0.2,20.0,20.0);
	m->setPosition(2.0,0.6,5.0);
	c->addObject(m);

	//glScalef(1.0,1.0,0.5);
	m = CreateSphere(0.2,20.0,20.0);
	m->setPosition(2.0,-0.6,5.0);
	c->addObject(m);

	m = CreateBox(1.0, 1.0, 25.0);
	m->setPosition(-3.0,0.0,12.5);
	m->setTexture(t);
	c->addObject(m);

	m = CreateBox(1.0, 1.0, 25.0);
	m->setPosition(3.0,0.0,12.5);
	m->setTexture(t);
	c->addObject(m);

	m = CreateBox(6.0, 1.0, 15.0);
	m->setPosition(0.0,0.0,17.5);
	m->setTexture(t);
	c->addObject(m);

	return c;
}
/*
void chaise2()
{
    GLUquadric* params;
    params = gluNewQuadric();
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0 ,0.0);
    glPushMatrix();
    gluCylinder(params,0.2,2.0,1.0,20.0,1.0);
    glTranslatef(0.0,0.0,-5.0);
    gluCylinder(params,0.2,0.2,5.0,20.0,1.0);
    //gluDisk(params,0.0,2.0,20.0,1.0);
    //gluDisk(params,1.8,2.0,20.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,-5.75);
    gluCylinder(params,1.75,1.75,0.75,20.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,-5.0);
    gluDisk(params,0.0,1.75,20.0,1.0);
    glTranslatef(0.0,0.0,-0.75);
    gluDisk(params,0.0,1.75,20.0,1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.0,-5.95);
    gluCylinder(params,1.5,1.5,0.2,20.0,1.0);
    gluDisk(params,0.0,1.5,20.0,1.0);
    glPopMatrix();
    glPopMatrix();

}
void cube(float x,float y,float z)
{
    x/=2;
    y/=2;
    z/=2;
    glBegin(GL_POLYGON);
    glVertex3d(-x, y, z);
    glVertex3d(-x, -y, z);
    glVertex3d( x, -y, z);
    glVertex3d( x, y, z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3d( x, y, -z);
    glVertex3d( x, -y, -z);
    glVertex3d( -x, -y, -z);
    glVertex3d( -x, y, -z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3d( x, y, z);
    glVertex3d( x, -y, z);
    glVertex3d( x, -y, -z);
    glVertex3d( x, y, -z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3d( -x, y, z);
    glVertex3d( -x, y, -z);
    glVertex3d( -x, -y, -z);
    glVertex3d( -x, -y, z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3d( -x, -y, z);
    glVertex3d( -x, -y, -z);
    glVertex3d( x, -y, -z);
    glVertex3d( x, -y, z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3d( -x, y, z);
    glVertex3d( x, y, z);
    glVertex3d( x, y, -z);
    glVertex3d( -x, y, -z);
    glEnd();
}
void Sphere(float taille,int a,int b)
{
    float da = ( M_PI / a );
    float db = ( 2.0f * M_PI / b );
    glBegin(GL_QUADS);
//glColor3f(1.0,0.0,0.0);
    glNormal3f(0,0,1);
    for( int i = 0; i < a + 1 ; i++ )
    {
        float r0 = sin ( i * da );
        float y0 = cos ( i * da );
        float r1 = sin ( (i+1) * da );
        float y1 = cos ( (i+1) * da );
        y0*=taille;
        y1*=taille;
        for( int j = 0; j < b + 1 ; j++ )
        {
            float x0 = r0 * sin( j * db );
            float z0 = r0 * cos( j * db );
            float x1 = r0 * sin( (j+1) * db );
            float z1 = r0 * cos( (j+1) * db );

            float x2 = r1 * sin( j * db );
            float z2 = r1 * cos( j * db );
            float x3 = r1 * sin( (j+1) * db );
            float z3 = r1 * cos( (j+1) * db );
            x0*=taille;
            z0*=taille;
            x1*=taille;
            z1*=taille;
            x2*=taille;
            z2*=taille;
            x3*=taille;
            z3*=taille;
            //glColor3f((x0+x1+x2+x3)/4.0,(y0+y1)/2.0,(z0+z1+z2+z3)/4.0);

            glVertex3f(x0,y0,z0);
            glVertex3f(x1,y0,z1);
            glVertex3f(x3,y1,z3);
            glVertex3f(x2,y1,z2);
        }
    }
    glEnd();
}*/

void scene()
{
    Object* obj;

	obj = enstabcha(glm::vec3(8.0,0.0,0.0));
	ObjectAccessor::getObjMgr()->getScene()->add(obj);

	obj = enstabcha(glm::vec3(-8.0,0.0,0.0));
	ObjectAccessor::getObjMgr()->getScene()->add(obj);

	obj = enstabcha(glm::vec3(0.0,0.0,0.0));
	ObjectAccessor::getObjMgr()->getScene()->add(obj);

	obj = ensbanqtab(glm::vec3(4.0,12.0,0.0));
	ObjectAccessor::getObjMgr()->getScene()->add(obj);

	obj = ensbanqtab(glm::vec3(-8.0,12.0,0.0));
	ObjectAccessor::getObjMgr()->getScene()->add(obj);

	obj = bar(glm::vec3(2.0,-15.0,4.0));
	ObjectAccessor::getObjMgr()->getScene()->add(obj);

	for(int i=0; i<9; i++)
	{
		//obj = chaise2(glm::vec3(2.0+5.0*1.25*i,4.0,-15.0));
		//ObjectAccessor::getObjMgr()->getScene()->add(obj);
	}

	//obj = baril_cigarette(glm::vec3(20.0,15.0,5.1));
	//ObjectAccessor::getObjMgr()->getScene()->add(obj);

	//obj = tas_de_parpaing(glm::vec3(21.5,5.0,1.0));
	//ObjectAccessor::getObjMgr()->getScene()->add(obj);

	obj = sol();
	ObjectAccessor::getObjMgr()->getScene()->add(obj);
	obj = mur();
	ObjectAccessor::getObjMgr()->getScene()->add(obj);
	obj = plafond();
	ObjectAccessor::getObjMgr()->getScene()->add(obj);
	obj = mur_fond();
	ObjectAccessor::getObjMgr()->getScene()->add(obj);
	obj = mur_porte();
	ObjectAccessor::getObjMgr()->getScene()->add(obj);
}