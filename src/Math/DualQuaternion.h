
#ifndef DUALQUATERNION_H
#define DUALQUATERNION_H

#include "glm::quaternion.h"


class Dualglm::quat
{
	Dualglm::quat(glm::quat q, glm::vec3 v)
	{
		ord = q;
		glm::vec3 quatvect = q.getVector();
		dual.setA(quatvect.scaleProduct(v)*-0.5f);
		glm::vec3 dualvector = glm::vec3(0.5f * (v.x * q.getA() + v.y * quatvect.z - v.z * quatvect.y),
									   0.5f * (-v.x * quatvect.z + v.y * q.getA() + v.z * quatvect.x),
									   0.5f * (v.x * quatvect.y - v.y * quatvect.y + v.z * q.getA()));
	
	}
private:
	glm::quat ord;
	glm::quat dual;
};

#endif