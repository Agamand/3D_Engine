
#ifndef OBJECT_H
#define OBJECT_H
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Texture/Texture.h"
#include "Particle.h"
#include "../Shader/Shader.h"
#include "../Util/List.h"
#include "../Bone.h"
//#include "../Scene/Animation.h"

#include <iostream>
#include <fstream>
#include <vector>

#define TODEG (180/M_PI)


#define TOCOLOR4(c) ((char*)&c)[0], ((char*)&c)[1], ((char*)&c)[2], ((char*)&c)[3]

enum FileType
{
	FILE_SCENE,
	FILE_ANIM,
	FILE_OBJECT,
};
enum ObjectType
{
	// Virtual type
	OBJECT_TYPE_NONE = -1,

	// Normals type
	OBJECT_TYPE_POLYGONE,
	OBJECT_TYPE_CONTAINER,
	OBJECT_TYPE_MESH,
	
	// Specials type
	OBJECT_TYPE_LIGHT,
	OBJECT_TYPE_PARTICLE_GENERATOR,

	//Specifics types
	OBJECT_TYPE_SPHERE,
	OBJECT_TYPE_BOX,
	OBJECT_TYPE_TORUS,
	OBJECT_TYPE_CYLINDER,
};

//using namespace std;
class Animation;
class Mass;
struct Face;
struct _linkinfo;
struct BoneLinkInfo;


struct Vertex
{
public:
	Vertex() : x(0), y(0), z(0), u(0), v(0),normal() {}
	Vertex(float _x, float _y, float _z, float _u = 0.0f, float _v = 0.0f, glm::vec3 n = glm::vec3())
	{
		x = _x;
		y = _y;
		z = _z;
		u = _u;
		v = _v;
		normal = n;
		glm::normalize(normal);
	}

	Vertex(Vertex const &vert)
	{
		x = vert.x;
		y = vert.y;
		z = vert.z;
		u = vert.u;
		v = vert.v;
		normal = vert.normal;
		glm::normalize(normal);
	}
	bool operator==(Vertex const &a) 
	{
		if(x != a.x || y != a.y || z != a.z)
			return false;
		return true;
	}

	void getPosition(float &_x, float &_y, float &_z);
	void getLinkInfo(_linkinfo* tab);
	void updatePos();

	
	
	// position
	float x,y,z;
	// normal
	glm::vec3 normal;
	// texture coord
	float u,v;

	List<BoneLinkInfo*> linkList;
	List<Face*> linked_faces;
};

struct Face
{
public:
	Face(int v1, int v2, int v3)
	{
		vertex[0] = v1;
		vertex[1] = v2;
		vertex[2] = v3;
		//generateNormal();
	}
	/*void generateNormal()
	{
		glm::vec3 _v1 = glm::vec3(vertex[0]->x-vertex[2]->x, vertex[0]->y-vertex[2]->y, vertex[0]->z-vertex[2]->z);
		glm::vec3 _v2 = glm::vec3(vertex[0]->x-vertex[1]->x, vertex[0]->y-vertex[1]->y, vertex[0]->z-vertex[1]->z);
		normal = _v1.crossProduct(_v2);
		normal.normalise();
	}*/
	int vertex[3];
	//glm::vec3 normal;
};



struct _linkinfo
{
	float matrix[16];
	float weight;
};

struct _linkinfocomplete
{
	int n_link;
	_linkinfo link[10];
};

struct BoneLinkInfo
{
	public:
		BoneLinkInfo( Bone* _bone, float _weight, Vertex* _vert)
		{
			bone = _bone;
			weight = _weight;
			vert = _vert;
		}

		/*void getPos(float x, float y, float z,float &_x, float &_y, float &_z)
		{
			float * mat = bone->getMatrix();
			_x = (inv_mat_origin[0][0]*x + inv_mat_origin[0][1]*y + inv_mat_origin[0][2]*z + inv_mat_origin[0][3]);
			_y = (inv_mat_origin[1][0]*x + inv_mat_origin[1][1]*y + inv_mat_origin[1][2]*z + inv_mat_origin[1][3]);
			_z = (inv_mat_origin[2][0]*x + inv_mat_origin[2][1]*y + inv_mat_origin[2][2]*z + inv_mat_origin[2][3]);
			x += (mat[0]*_x + mat[4]*_y + mat[8]*_z + mat[12])*weight;
			y += (mat[1]*_x + mat[5]*_y + mat[9]*_z + mat[13])*weight;;
			z += (mat[2]*_x + mat[6]*_y + mat[10]*_z + mat[14])*weight;
		}*/

		Bone* bone;
		int boneindex;
		float weight;
		Vertex*	vert;
		glm::mat4 bindMatrix;

};


class Object
{
public:
	Object(glm::vec3 _position = glm::vec3(0), glm::vec3 _repere = glm::vec3(0));
	~Object();

	glm::vec3 getPosition() { return position; }
	void setPosition(glm::vec3 pos) 
	{
		glm::vec3 diffpos = pos - position;
		position = pos; 
		transmatrix = glm::translate(glm::mat4(1),position); 
		updateObjectMatrix(); 
		atPositionChange(diffpos,0,glm::vec3());
	} 
	void getPosition(float &x, float &y, float &z) { x = position.x; y =  position.y; z = position.z; }
	void setPosition(float x, float y, float z) { setPosition(glm::vec3(x,y,z)); }
	void updatePosition(int time);

	virtual void update(int time);
	void updateAnim(int time);
	virtual void updateChild(int time) {return;}
	virtual void updatePositionChild(int time) {return;}
	virtual void atPositionChange(glm::vec3 pos,float angle, glm::vec3 v) {return;}


	glm::vec3 getRepere() { return repere; }
	void setRepere(glm::vec3 pos) { repere = pos; } 
	void getRepere(float &x, float &y, float &z) { x = repere.x; y = repere.y; z = repere.z; }
	void setRepere(float x, float y, float z) { repere = glm::vec3(x,y,z); }

	glm::vec3 getSymetrie() { return symetrie; }
	void setSymetrie(glm::vec3 s) { symetrie = s; } 
	void getSymetrie(float &x, float &y, float &z) { x = symetrie.x; y = symetrie.y; z = symetrie.z; }
	void setSymetrie(float x, float y, float z) { symetrie = glm::vec3(x,y,z); }

	ObjectType getType() { return type;}
	
	float getSize() { return size; }
	void setSize(float size) { this->size = size; }

	void rotate(float angle, glm::vec3 vect)
	{ 
		rotation = rotation * glm::quat_cast(glm::rotate(glm::mat4(1.0f),angle,vect));
		rotmatrix = glm::mat4_cast(rotation); 
		updateObjectMatrix();
		atPositionChange(glm::vec3(),angle,vect);
	}
	void setRotation(glm::quat q) { rotation = q;}
	glm::quat getRotation() { return rotation;}

	int getColor() { return color; }
	void setColor(int color) { this->color = color; }

	Texture* getTexture()
	{ 
		if(heritage && parent)
			return parent->getTexture();
		return texture;
	}
	void setTexture(Texture* texture) { this->texture = texture; }

	Object* getParent() { return parent; }
	void setParent(Object* par) { parent = par; }

	Animation* getAnimation() { return animation; }

	virtual void show() {return;}

	uint64 getGUID() { return guid;}

	void setMass(Mass* m) { mass = m;}
	Mass* getMass() { return mass;}

	void updateMass(int diff);

	void heritageMode(bool h) { heritage = h;}
	
	void setBind(bool b) {bind = b;}
	bool isBind() { return bind; }

	void UseLight(bool use = true) { useLight = use;}

	void showRepere(bool show) { showrep = show;}
	
	void setMainBone(Bone* b) { mainBone = b;}

	void file_export(std::ofstream file);
	void file_import(std::ifstream file);
	void useShader(Shader* sh) { shader = sh;}
	void updateObjectMatrix() {objectMatrix = transmatrix*rotmatrix;}
	void setObjectMatrix(glm::mat4 mat) { objectMatrix = mat;}
protected:
	uint64 guid;
	ObjectType type;
	float size;
	bool heritage;
	bool bind;
	bool showrep;
	bool useLight;
	int color;
	glm::quat rotation;
	glm::vec3 position;
	glm::vec3 repere;
	glm::vec3 symetrie;
	Object* parent;
	Animation* animation;
	Bone* mainBone;
	Mass* mass;
	Shader *shader;
	glm::mat4 rotmatrix;
	glm::mat4 transmatrix;
	glm::mat4 objectMatrix;
private:
	Texture* texture;
};

class Container : public Object
{
public:
	Container();
	Container(glm::vec3 _position);
	Container(glm::vec3 _position, glm::vec3 _repere);

	virtual void update(int diff)
	{
		Object::update(diff);
		for(size_t i = 0; i < object_list.size(); i++)
			object_list[i]->update(diff);
	}
	void show();
	void addObject(Object* obj) { obj->setParent(this); object_list.push_back(obj);}
	void delObject(Object* obj);
	void updateChild(int time);
	List<Object*> getObjectList() { return object_list;}
	void updatePositionChild(int time);

	void clearList(bool _delete = false);

	void addSphere(float r,float stack, float slice,float angle = 2.0f *M_PI);
	void addCylinder(float r1,float r2, float length,float stack, float slice, float angle = 2.0f*M_PI);
	void addDisk(float r,float stack,float angle = 2.0f*M_PI);
	void addTorus(float r1, float r2, float side, float ring, float angle1 = 2.0f*M_PI, float angle2 = 2.0f*M_PI, float angle1_beg = 0.0f);
protected:
	List<Object*> object_list;
};

class Polygone : public Object
{
public:
	Polygone();
	Polygone(glm::vec3 _position);
	Polygone(glm::vec3 _position, glm::vec3 _repere);
	~Polygone();


	void addVertex(Vertex v) { vertex_list.push_back(new Vertex(v)); }
	void delVertex(Vertex v);
	void show();
private:
	List<Vertex*> vertex_list;
};

class Mesh : public Object
{
public:
	Mesh(glm::vec3 _position = glm::vec3(), glm::vec3 _repere = glm::vec3()) : Object(_position, _repere), m_ColorBuffer(0), m_PositionBuffer(0), m_NormalBuffer(0), m_TexCoordBuffer(0), m_IndiceBuffer(0), m_IndiceBoneBuffer(0), m_WeightBoneBuffer(0) {}
	~Mesh() {}

	void addFace(Face f) { face_list.push_back(new Face(f));}
	void addVertex(Vertex* v) { vertex_list.push_back(v);}
	void show();
	std::vector<Face*> getFaces() { return face_list;}
	std::vector<Vertex*> getVertex() {return vertex_list;}
	void UpdateBuffer(bool fullupdate = false);
	void UpdateBoneBuffer(bool fullupdate = false);
	void addBone(Bone*b, glm::mat4 mat) { bone_list.push_back(b); inversebone_list.push_back(mat);}
	void linkVertex(int vertex,int bone, float w, glm::mat4 mat);
	void SetupUniform(bool disable = false);
	void SetupAttribut(bool disable = false);
	void calculateNormal();

private:
	std::vector<Face*> face_list;
	std::vector<Vertex*> vertex_list;
	std::vector<Bone*> bone_list;
	std::vector<glm::mat4> inversebone_list;

	//VBO(Vertex Buffer Object)
	uint32 m_ColorBuffer;
	uint32 m_PositionBuffer;
	uint32 m_NormalBuffer;
	uint32 m_TexCoordBuffer;
	uint32 m_IndiceBuffer;

	// VBO for Skinning
	uint32 m_WeightBoneBuffer;
	uint32 m_IndiceBoneBuffer;
};

class Light : public Object
{
public:
	Light(glm::vec3 pos = glm::vec3());
	~Light();

	void show();
	void setDir(glm::vec3 _dir);
	void setPosition(glm::vec3 pos);
	void setColor(int color);
	glm::vec3 getDir() { return dir;}
	void setSpot(float _spot) { spot = _spot; glLightfv(GL_LIGHT0+n_light, GL_SPOT_CUTOFF, &spot);}

private:
	int n_light;
	float spot;
	glm::vec3 dir;
};

class ParticleGenerator : public Object
{
public:
	ParticleGenerator(glm::vec3 pos, int life_particle, int _maxParticle, glm::vec3 _dir = glm::vec3(0.0f,0.0f,0.0f));

	~ParticleGenerator();
	void update(int time);
	void show();

	void setAcc(glm::vec3 a) {acc = a;}
private:
	void generateParticle();

	glm::vec3 dir;
	glm::vec3 speed;
	glm::vec3 acc;
	int life_particle; // in ms;
	int maxParticle;
	Particle** part;
	int t;
	float angle;
	Shader* particle_shader;
};


class Sphere : public Container
{
public:
	Sphere();
	Sphere(glm::vec3 pos, float r = 1.0f);

	void buildSphere();

	void setStacks(int stacks) { this->stacks = stacks; buildSphere();}
	int getStacks() { return stacks;}
	void setSlices(int slices) { this->slices = slices; buildSphere();}
	int getSlices() { return slices;}

	void setStacksAndSlices(int stacks, int slices) {this->stacks = stacks; this->slices = slices; buildSphere();}

	void setRadius(float r) { radius = r; buildSphere();}
	float getRadius() { return radius;}

private:
	float radius;
	float angle;
	int stacks;
	int slices;
};

class Cylinder : public Container
{
	Cylinder();
	Cylinder(glm::vec3 pos, float r1 = 1.0f, float r2 = 1.0f, float length = 2.0f);

	void buildCylinder();

	void setStacks(int stacks) { this->stacks = stacks; buildCylinder();}
	int getStacks() { return stacks;}
	void setSlices(int slices) { this->slices = slices; buildCylinder();}
	int getSlices() { return slices;}

	void setStacksAndSlices(int stacks, int slices) {this->stacks = stacks; this->slices = slices; buildCylinder();}

	void setRadius1(float r) { radius_1 = r; buildCylinder();}
	float getRadius1() { return radius_1;}

	void setRadius2(float r) { radius_2 = r; buildCylinder();}
	float getRadius2() { return radius_2;}

	void setLength(float l) {length = l; buildCylinder();}
	float getLength() {return length;}

private:
	float radius_1;
	float radius_2;
	float length;
	int stacks;
	int slices;
};

class Torus : public Container
{
	Torus();
	Torus(glm::vec3 pos, float r1 = 1.0f, float r2 = 2.0f);

	void buildTorus();

	void setSides(int sides) { this->sides = sides;}
	int getSides() { return sides;}
	void setRings(int rings) { this->rings = rings;}
	int getRings() { return rings;}

	void setSidesAndRings(int sides, int rings) {this->sides = sides; this->rings = rings;}

	void setInnerRadius(float r) { innerRadius = r;}
	float getInnerRadius() { return innerRadius;}

	void setOuterRadius(float r) { outerRadius = r;}
	float getOuterRadius() { return outerRadius;}

private:
	float innerRadius;
	float outerRadius;
	int sides;
	int rings;
};

class Box : public Container
{
public:
	Box();
	Box(glm::vec3 pos, glm::vec3 side_length = glm::vec3(1.0f,1.0f,1.0f));

	void buildBox();

	void setStacks(int stacks) { this->stacks = stacks; buildBox();}
	int getStacks() { return stacks;}
	void setSlices(int slices) { this->slices = slices; buildBox();}
	int getSlices() { return slices;}

	void setStacksAndSlices(int stacks, int slices) {this->stacks = stacks; this->slices = slices; buildBox();}

	glm::vec3 getLength() { return length; }
	void setLength(glm::vec3 l) { length = l; buildBox();} 
	void getLength(float &x, float &y, float &z) { x = length.x; y = length.y; z = length.z; }
	void setLength(float x, float y, float z) { length = glm::vec3(x,y,z); buildBox();}

private:
	glm::vec3 length;

	int stacks;
	int slices;
};


class BoneMesh : public Mesh
{
public:
	BoneMesh(Bone* b) : Mesh() {_bone = b;}
	void atPositionChange(glm::vec3 diffpos,float angle, glm::vec3 v)
	{

		_bone->posBase += diffpos;
		_bone->rotate(angle,v);
		_bone->updateAnimationPos();
	}
private:
	Bone* _bone;
};
void showrepere();
void showVecteur(glm::vec3 p,glm::vec3 vect);
//GLuint loadTexture(char *);
//void getEulerAngle(float*,float*);

//MESH BUILDER

Mesh* CreateSphere(float r,float stack, float slice,float angle = 2.0f *M_PI);
Mesh* CreateCylinder(float r1,float r2, float length,float stack, float slice, float angle = 2.0f*M_PI);
Mesh* CreateDisk(float r,float stack,float angle = 2.0f*M_PI);
Mesh* CreateTorus(float r1, float r2, float side, float ring, float angle1 = 2.0f*M_PI, float angle2 = 2.0f*M_PI, float angle1_beg = 0.0f);
Mesh* CreateBox(float x, float y, float z);
BoneMesh* CreateBone(float size, Bone* b);

#endif