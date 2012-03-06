#include <gl\glew.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <glut.h>

#include "Camera\Camera.h"
#include "Camera\Vector.h"
#include "Shader.h"
#include "Animation.h"

#include "ObjectAccessor\ObjectAccessor.h"
#include "Other.h"
#include "3DSLoader.h"
#define X_2 400
#define Y_2 300
#define BLANC 0xffffff
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
};

// Local variable
int click_pressed = NO_CLICK;
int mode = 0;
Object* selected_obj = NULL;
Animation *anim = NULL;
Camera* cam = NULL;
double time_scene = 0.0f; //in sec
clock_t last_time = 0;
int timer = 10;

//TEST
Animation* testanim = NULL;
Object* list_object[20];
int index = 0;
Shader * shadtest;
Scene* sctest;
int light[] = {0,0,0,1};
GLuint shader[] = {0,0};
GLuint program;
GLuint texture;

	GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
	GLfloat mat_diffuse[] = {0.1, 0.5, 0.8, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat no_shininess[] = {0.0};
	GLfloat low_shininess[] = {5.0};
	GLfloat high_shininess[] = {100.0};
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

	GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};    // Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {0.0f, 6.0f, 6.0f, 1.0f};

	
	GLfloat lightSpot0 = 20;    
	GLfloat lightDir0[] = {-1.0f, 0.0f, 0.0f};

		GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat lightDir1[] = {1.0f, 0.0f, 0.0f};

Corps c;

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
void keyboardSpec(unsigned char key,int x, int y);
void reshape(int w, int h);
void idle();
void mainUpdate(int value);

void showGrid();

void startPicking(int cursorX, int cursorY);
void stopPicking();
//void test_3ds(obj_type object);
void letter3D(char l, float x, float y, float z);
void esgi3D();

void initOP(void) 
{
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(70,(float)X_2/((float)Y_2),0.1,1000);
	glClearColor(0*192/255.0f, 0*192/255.0f, 0*192/255.0f, 0.0);
	glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void initTexture()
{
	Texture * t;

	t = newTexture(NULL,"earthmap1k_24.bmp");
	addTexture(t);
	t = newTexture(NULL,"Water.bmp");
	addTexture(t);
	load(t);
	t = newTexture(NULL,"spaceshiptexture.bmp");
	addTexture(t);
	load(t);
	texture = t->textureID; 
}

int main(int argc, char ** argv)
{
	Pointer* itr;
	int i;
	Point p;
	Vector3D v;
	GLenum err;
	Quat qt1,qt2,qt3;
    glutInit(&argc, argv);

	initObjectAccessor();
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
	newPoint(&p,-5.0f,6,6);
	newVector3D(&v,-2.0f, 0.0f, 0.0f);
	cam = newCamera(NULL,v);
	cam->_speed = 0.5f;

	Objmgr->scene =  newScene(NULL);
	//selected_obj = newSphere(NULL,&p,2.0f,"earthmap1k_24.bmp",255 +(255 << 8) + (255 << 16));
	//Objmgr->scene->object_list->Append(Objmgr->scene->object_list,selected_obj);
	selected_obj = bras_complet(&c.bras[0]);
	Objmgr->scene->object_list->Append(Objmgr->scene->object_list,selected_obj);


	//rot(c.bras[0].bras[0],45.0f,0,1.0,0.0);
	//rot(c.bras[1].bras[0],45.0f,0,1.0,0.0);

	
	selected_obj = c.bras[0].bras[0];
	for(i = 0;  i < 20; i++)
		list_object[i] = NULL;

	list_object[0] = c.bras[0].bras[0];
	list_object[1] = c.bras[0].bras[1];
	list_object[2] = c.bras[0].main.main;
	list_object[3] = c.bras[0].main.doigt[0].doigt[0];
	list_object[4] = c.bras[0].main.doigt[0].doigt[1];
	list_object[5] = c.bras[0].main.doigt[0].doigt[2];
	list_object[6] = c.bras[0].main.doigt[1].doigt[0];
	list_object[7] = c.bras[0].main.doigt[1].doigt[1];
	list_object[8] = c.bras[0].main.doigt[1].doigt[2];
	list_object[9] = c.bras[0].main.doigt[2].doigt[0];
	list_object[10] = c.bras[0].main.doigt[2].doigt[1];
	list_object[11] = c.bras[0].main.doigt[2].doigt[2];
	list_object[12] = c.bras[0].main.doigt[3].doigt[0];
	list_object[13] = c.bras[0].main.doigt[3].doigt[1];
	list_object[14] = c.bras[0].main.doigt[3].doigt[2];
	list_object[15] = c.bras[0].main.doigt[4].doigt[0];
	list_object[16] = c.bras[0].main.doigt[4].doigt[1];
	list_object[17] = c.bras[0].main.doigt[4].doigt[2];
	shadtest = LoadProgram("Shader/HeatHaze.vert","Shader/HeatHaze.frag");
	testanim = newAnim(NULL,selected_obj);

    glutMainLoop();
    return 0;
}


void reshape(int w, int h)
{
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (70.0, (GLfloat)w/(GLfloat)h, 0.1, 1000.0);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glutPostRedisplay ();
}

void display()
{
	char txt[200];
	GLUquadric* params;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();	

	if(cam)
		look(cam);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);   
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0); 
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir0);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &lightSpot0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);   
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos0); 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir1);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, &lightSpot0);

	glUseProgram(shadtest->program_id);
	glBegin(GL_POLYGON);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glEnd();
	glUseProgram(0);
	Objmgr->scene->showAllObject(Objmgr->scene,NULL);

	
	showGrid();

	//glEnable(GL_LIGHTING);
	//glUseProgram(program);
	//showObject(selected_obj);

	//

	glFlush();
	glutSwapBuffers();
}
void keyboardSpec(unsigned char key,int x, int y)
{
	switch(key)
	{
	case 'h':
		index++;
		if(index >= 20)
			index = 0;
		selected_obj = list_object[index];
		if(!selected_obj)
			selected_obj = list_object[0];
		break;
	case 'i':
		index--;
		if(index < 0)
			index = 0;
		selected_obj = list_object[index];
		if(!selected_obj)
			selected_obj = list_object[0];
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
		cam->OnMouseMotion(cam,x_diff,y_diff);

	if(selected_obj && click_pressed == CLICK_LEFT && mode >= SELECT_ROT_1)
	{
		angleAdd *= x_diff*TORAD;
		newQuat(&qt,angleAdd, mode == SELECT_ROT_1 ? 1.0f : 0.0f, mode == SELECT_ROT_2 ? 1.0f : 0.0f, mode == SELECT_ROT_3 ? 1.0f : 0.0f);
		selected_obj->qtrot = quatProd(selected_obj->qtrot,qt);
	}
	glutPostRedisplay();	
}

void mouse(int button, int state, int x, int y)
{
	float x_0,y_0;
	Point* pt;

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

	x_0 = x - X_2;
	y_0 = -y + Y_2;

}
void setTime(double time)
{

	updatePosition(Objmgr->scene->anim,time_scene*1000);
	time_scene = time;
	if(time_scene < 0.0f)
		time_scene = 0.0f;

	Objmgr->scene->anim->reset(Objmgr->scene->anim);
	Objmgr->scene->anim->update(Objmgr->scene->anim,time_scene*1000,1);
	printf("Temps scene : %f \n",time_scene);
}
void onkey(unsigned char key,int x, int y)
{
	char buffer[128];
	Vector3D v;
	if(cam)
		cam->OnKeyboard(cam,key);

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
	case '7':
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
	case '9':
		anim = NULL;
		break;
	case 'r':
		setTime(0.0f);
		Objmgr->scene->anim->reset(Objmgr->scene->anim);
		break;
	case 't':
		setTime(0.0f);
		Objmgr->scene->anim->reset(Objmgr->scene->anim);
		Objmgr->scene->anim->start = 1;
		break;
	case 'i':
		printf("\n !SET! time : ");
		fgets(buffer,128-1,stdin);
		buffer[strlen(buffer)-1] = 0;
		setTime(atof(buffer));
		break;
	case 'w':
		printf("\n !SAVE! file : ");
		fgets(buffer,128-1,stdin);
		buffer[strlen(buffer)-1] = 0;
		setTime(0.0f);
		saveScene(Objmgr->scene,buffer);
		break;
	case 'x':
		printf("\n !LOAD! file : ");
		fgets(buffer,128-1,stdin);
		buffer[strlen(buffer)-1] = 0;
		setTime(0.0f);
		sctest = loadScene(buffer);
		if(!sctest)
		{
			printf("\n %s loading error.",buffer);
			break;
		}
		Objmgr->scene = sctest;
		printf("\n %s loading success.",buffer);
		break;
	case '+':
		setTime(time_scene + 1.0f);
		break;
	case '-':
		setTime(time_scene - 1.0f);
		break;
	}
	glutPostRedisplay();
}

void idle()
{
	float _angle = M_PI/60;
	Quat qt,qt2;
	Matrice* m1,*m2,*m3;
	clock_t diff;
	int i;
	clock_t time = clock();
	diff = time - last_time;
	if(diff == 0)
		return;
	last_time = time;
	
	if(timer <= diff)
	{

		Objmgr->scene->anim->update(Objmgr->scene->anim,TIMER+diff-timer,0);

		timer = TIMER;
		glutPostRedisplay();
	}
	else timer -= diff;
}

void showGrid()
{
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


void startPicking(int cursorX, int cursorY) {

	GLint viewport[4];

	glSelectBuffer(BUFSIZE,selectBuf);
	glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT,viewport);
	gluPickMatrix(cursorX,viewport[3]-cursorY,
			5,5,viewport);
	gluPerspective(45,(float)X_2/((float)Y_2),0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glInitNames();
}

void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

   printf ("hits = %d\n", hits);
   ptr = (GLuint *) buffer;
   minZ = 0xffffffff;
   for (i = 0; i < hits; i++) {	
      names = *ptr;
	  ptr++;
	  if (*ptr < minZ) {
		  numberOfNames = names;
		  minZ = *ptr;
		  ptrNames = ptr+2;
	  }
	  
	  ptr += names+2;
	}
  printf ("The closest hit names are ");
  ptr = ptrNames;
  for (j = 0; j < numberOfNames; j++,ptr++) {
     printf ("%d ", *ptr);
  }
  printf ("\n");
   
}

void stopPicking() {

	int hits;
	
	// restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	
	// returning to normal rendering mode
	hits = glRenderMode(GL_RENDER);
	
	// if there are hits process them
	if (hits != 0)
		processHits(hits,selectBuf);
}