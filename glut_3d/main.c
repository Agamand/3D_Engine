#include <gl\glew.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <glut.h>

#include "Camera\Camera.h"
#include "Camera\Vector.h"
#include "Shader.h"

#include "ObjectAccessor\ObjectAccessor.h"
#include "Other.h"
#include "3DSLoader.h"
#define X_2 400
#define Y_2 300
#define BLANC 0xffffff


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
Camera* cam = NULL;

//TEST
clock_t last_time = 0;
int timer = 10;
float angle = 0.0f;
float angle_1 = 0.0f;
float angle_2 = 0.0f;
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
void reshape(int w, int h);
void idle();

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
	//glutSpecialFunc(keyboardSpec);
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
	selected_obj = corps(&c);
	Objmgr->scene->object_list->Append(Objmgr->scene->object_list,selected_obj);


	rot(c.bras[0].bras[0],45.0f,0,1.0,0.0);
	rot(c.bras[1].bras[0],45.0f,0,1.0,0.0);


	selected_obj = c.bras[0].bras[0];

	
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



	Objmgr->scene->showAllObject(Objmgr->scene);

	
	showGrid();

	//glEnable(GL_LIGHTING);
	//glUseProgram(program);
	//showObject(selected_obj);

	//

	glFlush();
	glutSwapBuffers();
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
void onkey(unsigned char key,int x, int y)
{
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
	last_time = time;
	
	if(timer <= diff)
	{



		//if(!selected_obj)
			//return;

		angle +=3.14/60;

		//((Container*)selected_obj)->angle[1] = _angle;
	/*setRot(c.bras[0].main.doigt[0].doigt[0],0,_angle,0.0,1.0,0.0);
	setRot(c.bras[0].main.doigt[0].doigt[1],0,_angle,0.0,1.0,0.0);
	setRot(c.bras[0].main.doigt[0].doigt[2],0,_angle/2,0.0,1.0,0.0);

	setRot(c.bras[0].main.doigt[1].doigt[0],0,_angle,0.0,1.0,0.0);
	setRot(c.bras[0].main.doigt[1].doigt[1],0,_angle,0.0,1.0,0.0);
	setRot(c.bras[0].main.doigt[1].doigt[2],0,_angle/2,0.0,1.0,0.0);

	setRot(c.bras[0].main.doigt[2].doigt[0],0,_angle,0.0,1.0,0.0);
	setRot(c.bras[0].main.doigt[2].doigt[1],0,_angle,0.0,1.0,0.0);
	setRot(c.bras[0].main.doigt[2].doigt[2],0,_angle/2,0.0,1.0,0.0);

	setRot(c.bras[0].main.doigt[3].doigt[0],0,_angle,0.0,1.0,0.0);
	setRot(c.bras[0].main.doigt[3].doigt[1],0,_angle,0.0,1.0,0.0);
	setRot(c.bras[0].main.doigt[3].doigt[2],0,_angle/2,0.0,1.0,0.0);*/



		//((Container*)selected_obj)->center.x = 20*cos(angle);
		//((Container*)selected_obj)->center.y = 20*sin(angle);
		/*cam->_position.x = ((Sphere*)selected_obj)->center.x;
		cam->_position.y = ((Sphere*)selected_obj)->center.y;
		cam->_position.z = ((Sphere*)selected_obj)->r+0.5;


		/*angle_1 += 4.0f/30;
		angle_2 -= 30.0f/30;*/
		timer = 1000/60;
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

/*void test_3ds(obj_type object)
{

	int l_index;
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture 

    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
	glColor3ub(255,255,255);
    for (l_index=0;l_index<object.polygons_qty;l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertexdds
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u,
                      object.mapcoord[ object.polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
                    object.vertex[ object.polygon[l_index].a ].y,
                    object.vertex[ object.polygon[l_index].a ].z); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,
                      object.mapcoord[ object.polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
                    object.vertex[ object.polygon[l_index].b ].y,
                    object.vertex[ object.polygon[l_index].b ].z);
        
        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,
                      object.mapcoord[ object.polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
                    object.vertex[ object.polygon[l_index].c ].y,
                    object.vertex[ object.polygon[l_index].c ].z);
    }
    glEnd();
}*/

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