

#ifndef ROBOT_H
#define ROBOT_H
#include "Object/Object.h"

class Robot
{
public:
	Robot();

	Object* doigtB();
	Object* doigt();
	Object* doigt_complete();
	Object* corps();
	Object* tete();
	Object* bras();
	Object* avant_bras();
	Object* bras_complete();
	Object* mains();
	Object* getBase() {return base; }
	Object* operator[] (int i);
private:
	Container* base;
	Container* _doigt[12];
	Container* _bras[2];

};



#endif