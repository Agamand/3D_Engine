

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 pos);
	~Camera();

	void OnMouseMotion(int x, int y);
	void OnKeyboard(char key);

	void VectorsFromAngles();

	glm::vec3 getPosition() { return _position; }
	void setPosition(glm::vec3 pos) { _position = pos; } 
	void getPosition(float &x, float &y, float &z) { x = _position.x; y = _position.y; z = _position.z; }
	void setPosition(float x, float y, float z) { _position = glm::vec3(x,y,z); }

	void setTarget(glm::vec3 pos) { _target = pos; } 
	glm::vec3 getTarget() {return _target;}

	void look();

private:
    float _speed;
    float _sensivity;

    //int32 _timeBeforeStoppingVerticalMotion;
    int _verticalMotionActive;
    int _verticalMotionDirection;

	glm::vec3 _position;
    glm::vec3 _target;
    glm::vec3 _forward;
    glm::vec3 _left;
    float _theta;
    float _phi;
};
#endif