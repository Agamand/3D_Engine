//#include "Object.h"

#ifndef OTHER_H
#define OTHER_H
/*typedef struct _corps Corps;
typedef struct _bras Bras;
typedef struct _mains Mains;
typedef struct _doigt Doigt;
typedef struct _pied Pied;
typedef struct _jambe Jambe;

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


struct _pied
{
	Container * pied;
};

struct _jambe
{
	Container* jambe[2];
	Pied pied;
};
struct _corps
{
	Container* Corps;
	//Tete t;
	Bras bras[2];
	Jambe jambe[2];
};


Object * box(Point * center,Point* repere,float x_length, float y_length, float z_length);



/*
Object * pied();
Object * jambe();
Object * jambe_complete();
*//*
Object * doigt(float length);
Object * doigt_complet(Doigt*);
Object * pouce(Doigt*);
Object * mains();
Object * main_complete(Mains*);


Object * bras();
Object * bras_complet(Bras * b);

Object * corps(Corps * c);


Object * pied(Pied* p);
Object * jambe();
Object * jambe_complet(Jambe*j);

Object * water();

Object* makeSphere(double angle_1, double angle_1to, double angle_2, double angle_2to, double stack, double slice);
*/
#endif
