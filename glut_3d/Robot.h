

#ifndef ROBOT_H
#define ROBOT_H
#include "Object.h"

class Robot
{
public:
	Robot();

	Object* doigtB();
	Object* doigt();
	Object* doigt_complete();
	Object* getBase() {return base; }
	Object* operator[] (int i);
private:
	Container* base;
	Container* _doigt[3];

};



#endif