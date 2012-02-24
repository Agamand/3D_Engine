#include "Vector.h"

#ifndef CAMERA_H
#define CAMERA_H

typedef struct _camera Camera;

struct _camera
{
    float _speed;
    float _sensivity;

    //int32 _timeBeforeStoppingVerticalMotion;
    int _verticalMotionActive;
    int _verticalMotionDirection;

    Vector3D _position;
    Vector3D _target;
    Vector3D _forward;
    Vector3D _left;
    float _theta;
    float _phi;

	void (*OnMouseMotion)(Camera* cam,int x, int y);
	int (*OnKeyboard)(Camera* cam,char key);

};


// CONSTRUCTOR / DECONSTRUCTOR

Camera * newCamera(Camera* cam, Vector3D pos);
void deleteCamera(Camera* cam);

// FUNCTION

void VectorsFromAngles(Camera*cam);
void OnMouseMotion(Camera* cam,int x, int y);
int OnKeyboard(Camera* cam,char key);
void setPosition(Camera* cam, Vector3D pos);
void setTarget(Camera* cam, float x, float y, float z);
void look(Camera*);

#endif