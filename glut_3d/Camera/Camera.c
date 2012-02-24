#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <glut.h>
#include "Camera.h"


// CONSTRUCTOR / DECONSTRUCTOR

Camera * newCamera(Camera* cam, Vector3D pos)
{
	if(!cam)
		cam = (Camera*)malloc(sizeof(Camera));

	cam->_position = pos;
    cam->_phi = 0;
    cam->_theta = 0;
    VectorsFromAngles(cam);

    cam->_speed = 1.0f;
    cam->_sensivity = 0.2;
    cam->_verticalMotionActive = 0;


	cam->OnKeyboard = OnKeyboard;
	cam->OnMouseMotion = OnMouseMotion;
	return cam;
}
void deleteCamera(Camera* cam)
{
	free(cam);
}

// FUNCTION

void VectorsFromAngles(Camera*cam)
{
	static const Vector3D up = {0,0,1,1};
	double r_temp = cos(cam->_phi*M_PI/180);
    if (cam->_phi > 89)
        cam->_phi = 89;
    else if (cam->_phi < -89)
        cam->_phi = -89;
    
    cam->_forward.z = sin(cam->_phi*M_PI/180);
    cam->_forward.x = r_temp*cos(cam->_theta*M_PI/180);
    cam->_forward.y = r_temp*sin(cam->_theta*M_PI/180);
    cam->_left = vectorCrossProduct(up,cam->_forward);
	normalize(&cam->_left);

    cam->_target = vectorAdd(cam->_position,cam->_forward);
}
void OnMouseMotion(Camera* cam,int x, int y)
{
    cam->_theta -= x*cam->_sensivity;
    cam->_phi += y*cam->_sensivity;
    VectorsFromAngles(cam);
}

int OnKeyboard(Camera* cam,char key)
{
	Vector3D up;
	newVector3D(&up,0.0f,0.0f,1.0f);
	switch(key)
	{
	case 'z':
		cam->_position = vectorAdd(cam->_position,vectorMutl(cam->_forward,cam->_speed));
		break;
	case 's':
		cam->_position = vectorSous(cam->_position,vectorMutl(cam->_forward,cam->_speed));
		break;
	case 'q':
		cam->_position = vectorAdd(cam->_position,vectorMutl(cam->_left,cam->_speed));
		break;
	case 'd':
		cam->_position = vectorSous(cam->_position,vectorMutl(cam->_left,cam->_speed));
		break;
	case 'e':
		cam->_position = vectorAdd(cam->_position,vectorMutl(up,cam->_speed));
		break;
	case 'a':
		cam->_position = vectorSous(cam->_position,vectorMutl(up,cam->_speed));
		break;

	case '8':
		cam->_phi++;
		break;
	case '2':
		cam->_phi--;
		break;
	case '4':
		cam->_theta++;
		break;
	case '6':
		cam->_theta--;
		break;
	}

	VectorsFromAngles(cam);

	cam->_target = vectorAdd(cam->_position,cam->_forward);
}

void setPosition(Camera* cam, Vector3D pos)
{
    cam->_position = pos;
    cam->_target = vectorAdd(cam->_position, cam->_forward);
}

void look(Camera* cam)
{
	gluLookAt(cam->_position.x, cam->_position.y, cam->_position.z, cam->_target.x, cam->_target.y, cam->_target.z, 0, 0, 1);
}


void setTarget(Camera* cam,float x, float y, float z)
{
	cam->_target.x = x;
	cam->_target.y = y;
	cam->_target.z = z;
}