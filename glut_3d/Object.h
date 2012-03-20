
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
	OBJECT_TYPE_PARTICLE_GENERATOR,
};

class Animation;
class Mass;

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

	void setMass(Mass* m) { mass = m;}
	Mass* getMass() { return mass;}

	void updateMass(int diff);

protected:
	uint64 guid;
	ObjectType type;
	double size;
	int color;
	Texture* texture;
	Quat rotation;
	Vector3D position;
	Vector3D repere;
	Object* parent;
	Animation* animation;
	Mass* mass;
};

class Container : public Object
{
public:
	Container();
	Container(Vector3D _position);
	Container(Vector3D _position, Vector3D _repere);
	~Container();

	void show();
	void addObject(Object* obj) { obj->setParent(this); object_list.push_back(obj);}
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

class Light : public Object
{
public:
	Light();
	Light(Vector3D pos);
	~Light();

	void show();
private:
	int n_light;
	float spot;
	Vector3D dir;
};

class ParticleGenerator : public Object
{
public:
	ParticleGenerator();
	ParticleGenerator(Vector3D pos);
	~ParticleGenerator();

	void show();
private:
	Vector3D dir;
};

void showrepere();
//GLuint loadTexture(char *);
//void getEulerAngle(double*,double*);



#endif