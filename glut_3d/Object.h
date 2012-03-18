
#ifndef OBJECT_H
#define OBJECT_H

#include "Texture.h"
#include "MathPlus.h"
//#include "Animation.h"
#include <vector>
/*
typedef struct _cube Cube;
typedef struct _point Point;
typedef struct _object Object;
typedef struct _polygone Polygone;
typedef struct _sphere Sphere;
typedef struct _container Container;
typedef struct _3ds Object_3ds;
typedef struct _light Light;*/

#define TOCOLOR4(c) ((char*)&c)[0], ((char*)&c)[1], ((char*)&c)[2], ((char*)&c)[3]

enum FileType
{
	FILE_SCENE,
	FILE_ANIM,
	FILE_LISTCH,
	FILE_OBJECT,
};
enum ObjectType
{
	OBJECT_TYPE_NONE = -1,
	OBJECT_TYPE_POLYGONE,
	//OBJECT_TYPE_SPHERE, old
	OBJECT_TYPE_CONTAINER,
	//OBJECT_TYPE_3DS, 
	OBJECT_TYPE_LIGHT,
};

class Animation;

class Object
{
public:
	Object();
	Object(Vector3D _position);
	Object(Vector3D _position, Vector3D _repere);
	~Object();

	Vector3D getPosition() { return position; }
	void setPosition(Vector3D pos) { position = pos; } 
	void getPosition(double &x, double &y, double &z) { x = position.getX(); y = position.getY(); z = position.getZ(); }
	void setPosition(double x, double y, double z) { position = Vector3D(x,y,z); }
	void update(int time);
	void updatePosition(int time);
	virtual void updateChild(int time) {return;}
	virtual void updatePositionChild(int time) {return;}

	Vector3D getRepere() { return repere; }
	void setRepere(Vector3D pos) { repere = pos; } 
	void getRepere(double &x, double &y, double &z) { x = repere.getX(); y = repere.getY(); z = repere.getZ(); }
	void setRepere(double x, double y, double z) { repere = Vector3D(x,y,z); }

	ObjectType getType() { return type;}
	
	double getSize() { return size; }
	void setSize(double size) { this->size = size; }

	void rotate(double angle, Vector3D vect) { rotation *= Quat(angle,vect);}
	void setRotation(Quat q) { rotation = q;}
	Quat getRotation() { return rotation;}

	int getColor() { return color; }
	void setColor(int color) { this->color = color; }

	Texture* getTexture() { return texture; }
	void setTexture(Texture* texture) { this->texture = texture; }

	Object* getParent() { return parent; }
	void setParent(Object* par) { parent = par; }

	Animation* getAnimation() { return animation; }

	virtual void show() {return;}

protected:
	ObjectType type;
	double size;
	int color;
	Texture* texture;
	Quat rotation;
	Vector3D position;
	Vector3D repere;
	Object* parent;
	Animation* animation;
};

class Container : public Object
{
public:
	Container();
	Container(Vector3D _position);
	Container(Vector3D _position, Vector3D _repere);
	~Container();

	void show();
	void addObject(Object* obj) {object_list.push_back(obj);}
	void delObject(Object* obj);
	void updateChild(int time);
	void updatePositionChild(int time);

	void addSphere(double r,float stack, float slice,double angle = 2.0f *M_PI);
	void addCylinder(double r1,double r2, double length,float stack, float slice, double angle = 2.0f*M_PI);
	void addDisk(double r,float stack,double angle = 2.0f*M_PI);
	void addTorus(double r1, double r2, float side, float ring, double angle1 = 2.0f*M_PI, double angle2 = 2.0f*M_PI, double angle1_beg = 0.0f);
private:
	std::vector<Object*> object_list;
};

class Polygone : public Object
{
public:
	Polygone();
	Polygone(Vector3D _position);
	Polygone(Vector3D _position, Vector3D _repere);
	~Polygone();

	struct Vertex
	{
	public:
		Vertex(double _x, double _y, double _z, float _u = 0.0f, float _v = 0.0f)
		{
			x = _x;
			y = _y;
			z = _z;
			u = _u;
			v = _v;
		}

		Vertex(Vertex const &vert)
		{
			x = vert.x;
			y = vert.y;
			z = vert.z;
			u = vert.u;
			v = vert.v;
		}
		bool operator==(Vertex const &a) 
		{
			if(x != a.x || y != a.y || z != a.z)
				return false;
			return true;
		}
		
		double x,y,z;
		float u,v;
	};
	void addVertex(Vertex v) { vertex_list.push_back(new Vertex(v)); }
	void delVertex(Vertex v);
	void show();
private:
	std::vector<Vertex*> vertex_list;
};

void showrepere();
/*
struct _point
{
	float x,y,z;
};

struct _cube
{
	Point center;
	int l[3];
	char color[3];
};

struct _object
{
	int type;
	float size;
	char color[4];
	Texture* texture;
	Quat qtrot;
	int name;
};

struct _polygone
{
	Object obj;
	ListCh * lPoint;
};

struct _sphere
{
	Object obj;
	Point center;
	float r;
};

struct _container
{
	Object obj;
	Point center;
	Point repere;
	int showRep;
	ListCh * objectL;
};

struct _3ds
{
	Object obj;
	Point center;
	Point repere;
	float angle[3];
	ListCh * objectL;
};

struct  _light
{
	Object obj;
	float spot;
	Vector3D dir;
	Vector3D center;
	Vector3D rep;
	int n_light;
};

//struct _pointLinker

// CONSTRUCTOR / DECONSTRUCTOR

Point * newPoint(Point*, float x, float y, float z);
void deletePoint(Point*);
Point* cpyPoint(Point*);


Cube* newCube(Cube *, Point,int*);


Object* cpyObject(Point*);

Polygone * newPolygone(Polygone*, Point*, int);
void deletePolygone(Polygone*);


Sphere* newSphere(Sphere* sph,Point * center, float r, char * texture, int color);
void deleteSphere(Sphere* sph);

Container* newContainer(Container* ct,Point * center, Point * repere);
void deleteContainer(Container* ct);

Light* newLight(Light * l,Vector3D center,Vector3D rep, int color, int n_light);
void deleteLight(Light* l);

// FUNCTION

GLuint loadTexture(char *);
void getEulerAngle(double*,double*);
void showrepere();
void render_string(float x, float y, float z, const char* s);

void polyAddPoint(Polygone*,Point*);
void polyDelPoint(Polygone*,Point*);
void showPolygone(Polygone*, int*);

void showSphere(Sphere*, int*);

void contAddObject(Container*,Object*);
void contDelObject(Container*,Object*);
void showContainer(Container*,int*);

void showLight(Light*l);
void rot(Object*obj,double angle, double x, double y, double z);




void traceCube(Cube*);
*/

#endif