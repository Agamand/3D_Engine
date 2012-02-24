#include "Object.h"

#ifndef OTHER_H
#define OTHER_H
typedef struct _corps Corps;
typedef struct _bras Bras;
typedef struct _mains Mains;
typedef struct _doigt Doigt;


struct _doigt
{
	Container* doigt[3];
};
struct _mains
{
	Container* main;
	Doigt doigt[5];
};

struct _bras
{
	Container* bras[2];
	Mains main;
};

struct _corps
{
	Container* Corps;
	//Tete t;
	Bras bras[2];
	//Jambe jambe[2];
};






Object * box(Point * center,Point* repere,float x_length, float y_length, float z_length);




Object * pied();
Object * jambe();
Object * jambe_complete();

Object * doigt(float length);
Object * doigt_complet(Doigt*);
Object * pouce(Doigt*);
Object * mains();
Object * main_complete(Mains*);


Object * bras();
Object * bras_complet(Bras * b);

Object * corps(Corps * c);

#endif
