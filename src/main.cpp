#include <gl\glew.h>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <glut.h>

#include "Camera/Camera.h"
#include "Math/Vector.h"
#include "Shader/Shader.h"
#include "Scene/Animation.h"
#include "Physics/Physics.h"
#include "ObjectAccessor\ObjectAccessor.h"
//#include "Other.h"
#include "Robot.h"
#include "Object/Particle.h"

#include <random>
#define X_2 400
#define Y_2 300
#define BLANC 0xffffff
#define ROUGE 0x0000ff
#define BLEU 0xff0000
#define TIMER 1000/60




enum click
{
	NO_CLICK = 0x0,
	CLICK_LEFT = 0x1,
	CLICK_MIDDLE = 0x2,
	CLICK_RIGHT = 0x4,
};

enum Mode
{
	CREATE_POLYGONE,
	NAVIGATION,
	SELECT_ROT_1,
	SELECT_ROT_2,
	SELECT_ROT_3,
	SELECT_SIZE,
};

// Local variable
int click_pressed = NO_CLICK;
int mode = 0;
Object* selected_obj = NULL;
//Animation *anim = NULL;
Camera* cam = NULL;
double time_scene = 0.0f; //in sec
clock_t last_time = 0;
int timer = 10;
Robot * rob;
float FOV = 1.0f;


//TEST
float t = 1.0f;
GLuint cubeMapId;
//Animation* testanim = NULL;
Object* list_object[22];
int index = 0;
Shader * shadtest;
Scene* sctest;
int light[] = {0,0,0,1};
GLuint shader[] = {0,0};
Shader* sh;
lpart lparticle;
GLuint program;
GLuint texture;



	GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};    // Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {0.0f, -6.0f, 1.0f, 1.0f};

	
	GLfloat lightSpot0 = 20;    
	GLfloat lightDir0[] = {0.0f, 0.0f, 0.0f};

		GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat lightDir1[] = {0.0f, 1.0f, 0.0f};



#define BUFSIZE 512
GLuint selectBuf[BUFSIZE];
//obj_type obj;

//OLD POSITION
int ox = 0, oy = 0;

void display();
void mouse(int button, int state, int x, int y);
void mousemotion(int x, int y);
void passivemotion(int x, int y);
void onkey(unsigned char key,int x, int y);
void keyboardSpec( int key,int x, int y);
void reshape(int w, int h);
void idle();
void mainUpdate(int value);
void selection(int x, int y);
void setSelection(Object* obj);
void showGrid();

void picking(int cursorX, int cursorY);
void letter3D(char l, float x, float y, float z);
void esgi3D();

void initOP(void) 
{
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(FOV,(float)X_2/((float)Y_2),0.1,1000);
	glClearColor(0*192/255.0f, 0*192/255.0f, 0*192/255.0f, 0.0);
	glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glEnable( GL_ALPHA_TEST );
}

void initTexture()
{
	Texture * t;

	/*t = newTexture(NULL,"earthmap1k_24.bmp");
	Objmgr->addTexture(t);
	t = newTexture(NULL,"Water.bmp");
	Objmgr->addTexture(t);
	load(t);
	t = newTexture(NULL,"spaceshiptexture.bmp");
	Objmgr->addTexture(t);
	load(t);
	texture = t->textureID; */
}

int main(int argc, char ** argv)
{

	int i;

	Vector3D v,v1,v2;
	GLenum err;
	Quat qt1,qt2,qt3;
    glutInit(&argc, argv);

	new ObjectAccessor(new Scene(OPTION_ENABLE_TEXTURE));
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(X_2*2+1, Y_2*2+1);
	glutInitWindowPosition (100+800, 100);
    glutCreateWindow("Projet info/math");
	err = glewInit();
	initOP();
	initTexture();

    glutDisplayFunc(display);
	glutKeyboardFunc(onkey);
	glutSpecialFunc(keyboardSpec);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemotion);
	glutPassiveMotionFunc(passivemotion);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	cam = new Camera(Vector3D(-2.0f,0.0f,0.0f));

	Polygone* p = new Polygone();
	p->addVertex(Polygone::Vertex(0.0,0.0,0.0,0.25,0.25));
	p->addVertex(Polygone::Vertex(0.0,0.0,1.0,0.25,0.75));
	p->addVertex(Polygone::Vertex(1.0,0.0,1.0,0.75,0.25));
	p->addVertex(Polygone::Vertex(1.0,0.0,0.0,0.75,0.75));
	p->setTexture(new Texture("earthmap1k_24.bmp"));
	p->getTexture()->load();


	//Light* l = new Light(Vector3D(0.0,0.0,0.0));
	//l->setDir(Vector3D(1.0f,0.0f,0.0f));
	//ObjectAccessor::getObjMgr()->getScene()->add(p);

	Container* _t = new Container();
	_t->addSphere(0.5,20,20);
	_t->setTexture(new Texture("earthmap1k_24.bmp"));
	//ObjectAccessor::getObjMgr()->getScene()->add(_t);
	//selected_obj = _t;

	rob = new Robot();
	ObjectAccessor::getObjMgr()->getScene()->add(rob->getBase());

	shadtest = LoadProgram("Shader/test.vert","Shader/test.frag");
	sh = LoadProgram("Shader/ParticleSimple.vert","Shader/ParticleSimple.frag");
    glutMainLoop();
    return 0;

}


void reshape(int w, int h)
{
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective ((GLfloat)FOV, (GLfloat)w/(GLfloat)h, 0.1, 1000.0);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glutPostRedisplay ();
}
float onde(float i,float t)
{
	float length = 0.2;
	float h = 0.2;
	float coef = 0.0f;
	return 0.0f;
	//if(i >= t-length && i <= t+length*2)
		return h*sin((t+length-i)/length*M_PI);
	//else return -0.0f;
}
void test_1(float slice)
{
	float start = 0.0f;
	float c;
	int i;
	for(i = 1; i <= slice; i++)
	{
		//if(i%2 != 0)
			//continue;

		c = 1.0f - i/slice;
		glPushMatrix();
		glTranslatef(0.0f,3.0f,0.0f);
		glBegin(GL_POLYGON);
		glColor3f(0.0f,0.0f,c);
		glVertex3f((i-1)/slice,1.0f,0.0f);
		glVertex3f((i-1)/slice,-1.0f,0.0f);
		glVertex3f(i/slice,-1.0f,0.0f);
		glVertex3f(i/slice,1.0f,0.0f);
		start += i/60.0f;
		glEnd();
		glPopMatrix();
	}
}

void surface(float l1, float l2, float slice)
{
	float start = 0.0f;
	float c;
	int i,j;
	for(i = 1; i <= slice; i++)
	{
		//if(i%2 != 0)
		//	continue;
		for(j = 1; j <= slice; j++)
		{
			glPushMatrix();
			//glTranslatef(0.0f,3.0f,0.0f);
			glBegin(GL_POLYGON);
			glColor4f(1.0f,0.0f,0.0f,0.1f);
			glVertex3f(l1*(i-1)/slice-l1/2,l2*(j-1)/slice-l2/2,0.0f);
			glVertex3f(l1*(i-1)/slice-l1/2,l2*(j)/slice-l2/2,0.0f);
			glVertex3f(l1*i/slice-l1/2,l2*(j)/slice-l2/2,0.0f);
			glVertex3f(l1*i/slice-l1/2,l2*(j-1)/slice-l2/2,0.0f);
			glEnd();
			glPopMatrix();
		}
	}
}

void test_2(float slice,float stack,float r)
{
	float start = 0.0f;
	int i,j;
	float c1,c2;
	
	for(j = 1; j <= stack/4; j++)
	{
		
		for(i = 1; i <= slice; i++)
		{
			
			if(i%2 == 0 && j%2 == 0 || i%2 != 0 && j%2 != 0)
			{
				c1 = 0;
				c2 = 1.0;
			}else 
			{
				c1 = 1.0;
				c2 = 0;
			}


			/*c1 = 1.0f - i/slice;
			c2 = j > slice/2 ? 1.0f-j/slice : j/slice;
			//c1 /=2;
			//c1 +=1.0/2;
			c2 /=2;
			c2 +=1.0/2;*/			
			glBegin(GL_POLYGON);
			glColor3f(c1,0.0,c2);
			glVertex3f(r*(i-1)/slice*cos((j-1)*2*M_PI/stack),r*(i-1)/slice*sin((j-1)*2*M_PI/stack),onde((i-1)/slice,t));
			glVertex3f(r*(i-1)/slice*cos((j)*2*M_PI/stack),r*(i-1)/slice*sin((j)*2*M_PI/stack),onde((i-1)/slice,t));
			glVertex3f(r*(i)/slice*cos((j)*2*M_PI/stack),r*(i)/slice*sin((j)*2*M_PI/stack),onde((i)/slice,t));
			glVertex3f(r*(i)/slice*cos((j-1)*2*M_PI/stack),r*(i)/slice*sin((j-1)*2*M_PI/stack),onde((i)/slice,t));
			glEnd();
		}
	}
}

double randVal(double min, double max)
{
	return (double) (min + (max - min)*((float) rand() / (RAND_MAX + 1.0)));
}


void genParticle()
{
	float nPart = 300.0f,i;
	int uniID[4];
	double vec[3];
	
	uniID[0] = glGetUniformLocation(sh->program_id, "time");
	uniID[1] = glGetUniformLocation(sh->program_id, "repeat");
	uniID[2] = glGetUniformLocation(sh->program_id, "v0");
	

	for(i = 0; i < nPart; i++)
	{
		vec[0] = 2*cos(i/nPart*2*M_PI);
		vec[1] = 2*sin(i/nPart*2*M_PI);
		vec[2] = 5.0f;
		glUseProgram(sh->program_id);
		glUniform1f(uniID[0],t);
		glUniform1f(uniID[1],4.0f);
		glUniform3f(uniID[2],vec[0],vec[1],vec[2]);
	    glBegin(GL_POLYGON);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.01f,0.0f,0.01f);
		glVertex3f(0.01f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.01);
		glEnd();
		glPopMatrix();
		glUseProgram(0);
	}

}





void display()
{
	char txt[200];
	int i;
	int uniformId = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_TEXTURE);
    glLoadIdentity ();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();	

	if(cam)
		cam->look();

	//test_2(200,200,2.0);
	ObjectAccessor::getObjMgr()->getScene()->show();
	//glColor3f(1.0,1.0,0.0);
	//glutSolidSphere(1.0,40,40);
	//showAllParticle(lparticle,t);
	//surface(2.0f,2.0f,100.0f);



    /*uniformId = glGetUniformLocation(shadtest->program_id, "time");
	glUseProgram(shadtest->program_id);
	glUniform1f(uniformId,t);
	surface( 2.0f,2.0f,100.0f);
	glUseProgram(0);*/
	//showObject(selected_obj);


	showGrid();
	glFlush();
	glutSwapBuffers();
}
void keyboardSpec(int key,int x, int y)
{
	switch(key)
	{
	case 'h':
		index++;
		//if(index >= 21)
			//index = 0;
		//((Container*)selected_obj)->showRep = 0;
		selected_obj = (*rob)[index];
		//if(!selected_obj)
			//selected_obj = list_object[0];

		//((Container*)selected_obj)->showRep = 1;
		break;
	case 'i':
		index--;

		if(index < 0)
			index = 0;
		selected_obj = (*rob)[index];
		//((Container*)selected_obj)->showRep = 0;
		/*selected_obj = list_object[index];
		if(!selected_obj)
			selected_obj = list_object[0];
		//((Container*)selected_obj)->showRep = 1;*/
		break;
	}

}

void mousemotion(int x,int y)
{
	int x_diff, y_diff;
	Quat qt;
	float angleAdd = 1.0f;
	x_diff = x - ox;
	y_diff = y - oy;
	ox = x;
	oy = y;

	if(cam && click_pressed == CLICK_RIGHT)
		cam->OnMouseMotion(x_diff,y_diff);

	if(selected_obj && click_pressed == CLICK_LEFT)
	{
		switch(mode)
		{
		case SELECT_ROT_1:
		case SELECT_ROT_2:
		case SELECT_ROT_3:
			angleAdd *= x_diff*TORAD;
			selected_obj->rotate(angleAdd,Vector3D(mode == SELECT_ROT_1 ? 1.0f : 0.0f, mode == SELECT_ROT_2 ? 1.0f : 0.0f, mode == SELECT_ROT_3 ? 1.0f : 0.0f));
			break;
		case SELECT_SIZE:
			selected_obj->setSize(selected_obj->getSize()+x_diff*0.1f);
			break;
		}
	}
	//glutPostRedisplay();	
}

void mouse(int button, int state, int x, int y)
{
	float x_0,y_0;

	ox = x;
	oy = y;

	x_0 = x - X_2;
	y_0 = -y + Y_2;

	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN)
			click_pressed |= CLICK_LEFT;
		else click_pressed &= ~CLICK_LEFT;
		break;
	case GLUT_MIDDLE_BUTTON:
		if(state == GLUT_DOWN)
			click_pressed |= CLICK_MIDDLE;
		else click_pressed &= ~CLICK_MIDDLE;
		break;
	case GLUT_RIGHT_BUTTON:
		if(state == GLUT_DOWN)
			click_pressed |= CLICK_RIGHT;
		else click_pressed &= ~CLICK_RIGHT;
		break;
	}

	if(click_pressed != CLICK_LEFT)
		return;

	selection(x,y);
	//picking(x,y);
	/*startPicking(x, y);
	stopPicking();

	/*switch(mode)
	{
	case CREATE_POLYGONE:
		if(!selected_obj)
		{
			pt = newPoint(NULL,x_0,y_0,0);
			selected_obj = (Object*)newPolygone(NULL, pt,255);
		}
		else if(selected_obj->type == OBJECT_TYPE_POLYGONE)
		{
			pt = newPoint(NULL,x_0,y_0,0);
			polyAddPoint((Polygone*)selected_obj,pt);
		}
		glutPostRedisplay();
	}*/
}


void passivemotion(int x, int y)
{
	float x_0,y_0;
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	x_0 = x - viewport[2]/2;
	y_0 = -y + viewport[3]/2;

	printf("\n 1 x : %i, y : %i",x,y);
	printf("\n 2 x : %i, y : %i",x-viewport[2]/2,-y+viewport[3]);
	printf("\n 3 x : %i, y : %i",x,-y+viewport[3]);
}
void setTime(double time)
{

	//updatePosition(Objmgr->scene->anim,time_scene*1000);
	time_scene = time;
	if(time_scene < 0.0f)
		time_scene = 0.0f;
	
	ObjectAccessor::getObjMgr()->getScene()->reset();
	ObjectAccessor::getObjMgr()->getScene()->update(time_scene*1000,true);
	printf("Temps scene : %f \n",time_scene);
}
void onkey(unsigned char key,int x, int y)
{
	char buffer[128];
	Vector3D v;
	if(cam)
		cam->OnKeyboard(key);

	switch(key)
	{
	case '1':
		mode = SELECT_ROT_1;
		break;
	case '2':
		mode = SELECT_ROT_2;
		break;
	case '3':
		mode = SELECT_ROT_3;
		break;
	case '4':
		mode = SELECT_SIZE;
		break;
	case '8':
		selected_obj->getMass()->setVelocity(Vector3D(0.0f,0.0f,3.0f));
		break;
	case '7':
		selected_obj->setMass(new Mass(selected_obj,1.0f));
		selected_obj->getMass()->setVelocity(Vector3D(0.0f,2.0f,10.0f));
		/*if(anim && selected_obj)
		{
			if(anim->obj != selected_obj)
				anim = getAnimFromObj(Objmgr->scene->anim,selected_obj);
		}

		if(!anim && selected_obj)
		{
			anim = getAnimFromObj(Objmgr->scene->anim,selected_obj);
			if(!anim)
			{
				anim = newAnim(NULL,selected_obj);
				addAnim(Objmgr->scene->anim,anim);
			}
		}else if(!anim && !selected_obj)
			break;

		addMoveInfo(anim,anim->obj->qtrot,time_scene*1000);

		*/
		break;
	case '5':
		selected_obj->getMass()->applyVelocity(Vector3D(0.0f,2.0f,0.0f));
		break;
	case '6':
		selected_obj->getMass()->applyVelocity(Vector3D(0.0f,-2.0f,0.0f));
		break;
	case '9':
//		anim = NULL;
		break;
	case 'r':
		ObjectAccessor::getObjMgr()->getScene()->reset();
		break;
	case 't':
		ObjectAccessor::getObjMgr()->getScene()->start();
		break;
	case 'i':
		printf("\n !SET! time : ");
		fgets(buffer,128-1,stdin);
		buffer[strlen(buffer)-1] = 0;
		ObjectAccessor::getObjMgr()->getScene()->setTime((int)(atof(buffer)*1000));
		break;
	case 'w':
		printf("\n !SAVE! file : ");
		fgets(buffer,128-1,stdin);
		buffer[strlen(buffer)-1] = 0;
		setTime(0.0f);
		//saveScene(Objmgr->scene,buffer);
		break;
	case 'x':
		printf("\n !LOAD! file : ");
		fgets(buffer,128-1,stdin);
		buffer[strlen(buffer)-1] = 0;
		setTime(0.0f);
		//sctest = loadScene(buffer);
		if(!sctest)
		{
			printf("\n %s loading error.",buffer);
			break;
		}
		//Objmgr->scene = sctest;
		printf("\n %s loading success.",buffer);
		break;
	case '+':
		ObjectAccessor::getObjMgr()->getScene()->incTime();
		break;
	case '-':
		ObjectAccessor::getObjMgr()->getScene()->incTime(-100);
		break;
	case '&':
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		break;
	case 233:
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		break;
	case '"':
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
		break;
	case ')':
		FOV -=1.0f;
		if(FOV < 1.0f)
			FOV = 0.0f;
		break;
	case '=':
		FOV +=1.0f;
		if(FOV > 180.0f)
			FOV = 180.0f;
		break;
	}
	//glutPostRedisplay();
}

void idle()
{
	Vector3D v0;
	Particle* p;
	double _rand,_rand2;
	float _angle = M_PI/60;
	Quat qt,qt2;
	clock_t diff;
	int i;
	clock_t time = clock();
	diff = time - last_time;
	if(diff == 0)
		return;
	last_time = time;
	
	if(timer <= diff)
	{
		for(i = 0; i < 1;i++)
		{
		Vector3D v(randVal(-2.0f,2.0f),randVal(-2.0f,2.0f),4.0f);
		p = new Particle(v,t,3.0f,sh->program_id);
		lparticle.push_back(p);
		}
		ObjectAccessor::getObjMgr()->getScene()->update(TIMER+diff-timer);

		timer = TIMER;
		t += 0.005;
		//if(t > 1.0f)
			//t = 0.0f;
		glutPostRedisplay();
	}
	else timer -= diff;
}

void showGrid()
{
	glDisable(GL_TEXTURE_2D);
	int i, j;

	for(i = 0; i < 9; i++)
	{
		glBegin(GL_LINES);
		glColor3ub(255,255,255);
		glVertex3f(-4.0f+i,-4.0f,0.0f);
		glVertex3f(-4.0f+i,4.0f,0.0f);
		glEnd();

		glBegin(GL_LINES);
		glColor3ub(255,255,255);
		glVertex3f(-4.0f,-4.0f+i,0.0f);
		glVertex3f(4.0f,-4.0f+i,0.0f);
		glEnd();
	}
}

void selection(int x, int y)
{
	GLuint	buffer[512];
	GLint	hits;
	GLint	viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(512, buffer);
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3]-y), 1.0f, 1.0f, viewport);
	gluPerspective(FOV, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	ObjectAccessor::getObjMgr()->getScene()->show();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	hits=glRenderMode(GL_RENDER);

	if (hits > 0)
	{
		int	choose = buffer[buffer[0]+1];
		int depth = buffer[1];
		int lastindex = buffer[0]+2+1;
		for (int i = 1; i < hits; i++)
		{
			int size = buffer[lastindex]+1;
			if (buffer[lastindex+1] < GLuint(depth))
			{
				choose = buffer[lastindex+size];
				depth = buffer[lastindex+1];
			}
			lastindex += (size+2);
		}
		setSelection(ObjectAccessor::getObjMgr()->getObject(choose));
    }else setSelection(NULL);

	
}

void setSelection(Object* obj)
{
	if(selected_obj)
		selected_obj->showRepere(false);
	
	
	selected_obj = obj;

	if(selected_obj)
		selected_obj->showRepere(true);
}