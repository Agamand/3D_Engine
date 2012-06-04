
#include <time.h>
#include <math.h>
#include <cstdlib>
#include "opengl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Camera/Camera.h"
#include "Math/Vector.h"
#include "Shader/Shader.h"
#include "Scene/Animation.h"
#include "Physics/Physics.h"
#include "ObjectAccessor\ObjectAccessor.h"
#include "Scene_demo.h"
#include "test.h"
#include "Robot.h"
#include "Object/Particle.h"
#include "Math\Geom.h"
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

enum CreatePhase
{
	NO_CREATE = -1,
	PHASE_1,
	PHASE_2,
	PHASE_3,
};

// Local variable
int click_pressed = NO_CLICK;
int mode = 0;
Object* selected_obj = NULL;
Camera* cam = NULL;
clock_t last_time = 0;
int timer = 10;
Robot * rob;
float FOV = 45.0f;
Object* light;
float t = 0.0f;



// Creation d'objet
Object* objectCreated = NULL;
int creatingPhase = NO_CREATE;


// BEGIN TEST VAR
Bone * bone;
Bone* _bone, *_bone2;
int boneselect = 0;
int bras_timer = 1000;
int bras_inverse = -1;

// END TEST

#define BUFSIZE 512
GLuint selectBuf[BUFSIZE];

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
bool getIntersect(int cursorX, int cursorY,glm::vec3 &v,Plan p = Plan(glm::vec3(),glm::vec3(0,0,1)));



void initOP(void) 
{
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(FOV,(float)X_2/((float)Y_2),0.1,1000);
	glClearColor(0*192/255.0f, 0*192/255.0f, 0*192/255.0f, 0.0);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glEnable( GL_ALPHA_TEST );
}

int main(int argc, char ** argv)
{

	glm::vec3 v,v1,v2;
	GLenum err;
    glutInit(&argc, argv);


    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(X_2*2+1, Y_2*2+1);
	glutInitWindowPosition (100+800, 100);
    glutCreateWindow("Projet info/math");
	err = glewInit();
	new ObjectAccessor(new Scene(OPTION_ENABLE_LIGHT));
	initOP();
    glutDisplayFunc(display);
	glutKeyboardFunc(onkey);
	glutSpecialFunc(keyboardSpec);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemotion);
	glutPassiveMotionFunc(passivemotion);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	cam = new Camera(glm::vec3(0.0f,0.0f,4.0f));
	Light* l;
	//l = new Light(glm::vec3(0.0,0.0,10.0));
	//l->setColor(255/2 + (255/2<< 8) + (255/2<< 16));
	//ObjectAccessor::getObjMgr()->getScene()->add(l);

	l = new Light(glm::vec3(0.0,10.0,22.75));
	l->setSpot(35.0f);
	l->setDir(glm::vec3(0.0f,0.0f,-1.0f));
	ObjectAccessor::getObjMgr()->getScene()->add(l);

	l = new Light(glm::vec3(0.0,-25.0f,22.75));
	l->setSpot(30.0f);
	l->setDir(glm::vec3(0.0f,0.0f,-1.0f));
	ObjectAccessor::getObjMgr()->getScene()->add(l);

	l = new Light(glm::vec3(0.0,-7.5,22.75));
	l->setSpot(40.0f);
	l->setDir(glm::vec3(0.0f,0.0f,-1.0f));
	ObjectAccessor::getObjMgr()->getScene()->add(l);
	//light = l;

	rob = new Robot();
	ObjectAccessor::getObjMgr()->getScene()->add(rob->getBase());
	bone = rob->getBoneBase();
	scene();


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

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();	
	if(cam)
		cam->look();

	ObjectAccessor::getObjMgr()->getScene()->show();
	bone->show();

	glutSwapBuffers();
	glutPostRedisplay();
}
void keyboardSpec(int key,int x, int y)
{
	switch(key)
	{
	case 104:
		boneselect++;
		break;
	case 105:
		boneselect--;
		break;
	}

}

void mousemotion(int x,int y)
{
	int x_diff, y_diff;
	glm::quat qt;
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
			angleAdd *= x_diff;
			selected_obj->rotate(angleAdd,glm::vec3(mode == SELECT_ROT_1 ? 1.0f : 0.0f, mode == SELECT_ROT_2 ? 1.0f : 0.0f, mode == SELECT_ROT_3 ? 1.0f : 0.0f));
			break;
		case SELECT_SIZE:
			selected_obj->setSize(selected_obj->getSize()+x_diff*0.1f);
			break;
		}
		
		
		
	}
	/*angleAdd *= x_diff*10;
	if(click_pressed == CLICK_LEFT)
	{
		switch(boneselect)
		{
		case 0:
			bone->rotate(angleAdd,glm::vec3(0,1,0));
			break;
		case 1:
			_bone->rotate(angleAdd,glm::vec3(0,1,0));
			break;
		case 2:
			_bone2->rotate(angleAdd,glm::vec3(0,1,0));
			break;
		}

	}*/

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
}


void passivemotion(int x, int y)
{
	float x_0,y_0;
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	x_0 = x - viewport[2]/2;
	y_0 = -y + viewport[3]/2;

}
void onkey(unsigned char key,int x, int y)
{
	char buffer[128];
	glm::vec3 v;
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
	case 'r':
		ObjectAccessor::getObjMgr()->getScene()->reset();
		break;
	case 't':
		ObjectAccessor::getObjMgr()->getScene()->start();
		break;
	case 'm':
		cam->setPosition(0,0,4.0f);
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

		//saveScene(Objmgr->scene,buffer);
		break;
	case 'x':
		printf("\n !LOAD! file : ");
		fgets(buffer,128-1,stdin);
		buffer[strlen(buffer)-1] = 0;

		//sctest = loadScene(buffer);

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
	case 'p':
		ObjectAccessor::getObjMgr()->getScene()->switchShader();
	}
	//glutPostRedisplay();
}

void idle()
{
	glm::vec3 v0;
	float _angle = M_PI/60;
	glm::quat qt,qt2;
	clock_t diff;
	clock_t time = clock();
	diff = time - last_time;
	if(diff == 0)
		return;

	last_time = time;
	
	if(bras_timer <= diff)
	{
		bras_inverse = -bras_inverse;
		bras_timer = 1000;
	}else bras_timer -= diff;
	if(timer <= diff)
	{
		ObjectAccessor::getObjMgr()->getScene()->update(TIMER+diff-timer);
		
		
		//_bone->rotate(bras_inverse*0.5,glm::vec3(1,0,0));

			//t = 0.0f;
		//double x,y,z;
		//light->getPosition(x,y,z);

		//light->setPosition(x,2.0f*sin(t),2.0f*cos(t));
		//glutPostRedisplay();
		timer = TIMER;
	}
	else timer -= diff;
	//printf("\n update time : %d",diff);
}

void showGrid()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	int i;

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
	bone->show();
	//ObjectAccessor::getObjMgr()->getScene()->show();
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

bool getIntersect(int cursorX, int cursorY,glm::vec3 &p,Plan pl)
{
    GLdouble Bx,By,Bz;
    GLint viewport[4];
    GLdouble mvmatrix[16], projmatrix[16];
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
    glGetIntegerv(GL_VIEWPORT,viewport);
    gluUnProject( cursorX,viewport[3]-cursorY,0,mvmatrix,projmatrix,viewport,&Bx,&By,&Bz);
	glm::vec3 B(Bx,By,Bz);
	glm::vec3 AB= B - cam->getPosition();
	Droite d_AB = Droite(cam->getPosition(),AB); 
	return pl.intersect(d_AB,p);
}