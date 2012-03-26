

#ifndef CAMERA_H
#define CAMERA_H

#include "../Math/Vector.h"

class Camera
{
public:
	Camera();
	Camera(Vector3D pos);
	~Camera();

	void OnMouseMotion(int x, int y);
	void OnKeyboard(char key);

	void VectorsFromAngles();

	Vector3D getPosition() { return _position; }
	void setPosition(Vector3D pos) { _position = pos; } 
	void getPosition(double &x, double &y, double &z) { x = _position.getX(); y = _position.getY(); z = _position.getZ(); }
	void setPosition(double x, double y, double z) { _position = Vector3D(x,y,z); }

	void setTarget(Vector3D pos) { _target = pos; } 

	void look();

private:
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
};
#endif