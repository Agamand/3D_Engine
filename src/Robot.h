

#ifndef ROBOT_H
#define ROBOT_H
#include "Object/Object.h"
#include "Bone.h"

class Robot
{
public:
	Robot();

	Object* doigtB();
	//Object* doigt();
	Object* doigt_complete();
	void corps();
	void bras(bool droit);
	void mains(bool droit);
	void doigt(bool droit, int index);
	void tete();
	void jambe();
	void pied();
	//Object* tete();
	//Object* eye();
	Object* old_bras();
	Object* avant_bras();
	Object* bras_complete();
	//Object* mains();
	Object* jambe_complete();
	Object* getBase() {return base; }
	void generateBone();
	void generateRobot();
	Bone* getBoneBase() {return bonebase;}
	Object* operator[] (int i);

private:
	Container* base;
	Bone* bonebase;
	Container* _doigt[12];
	Container* _bras[2];

};



#endif