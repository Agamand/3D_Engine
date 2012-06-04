#ifndef BONE_H
#define BONE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "Util/List.h"
#include <vector>
class Mesh;
class BoneMesh;
struct Vertex;
struct BoneLinkInfo;

class AnimationBone;

class Bone
{
public:
	Bone(float _length, Bone* parent = NULL);
	~Bone();
	void show(glm::vec3 v = glm::vec3());
	void moveTo(glm::vec3 pos);
	void rotate(float angle, glm::vec3);

	float getLength() { return length;}
	void linkVertex(Vertex * vertex, float w, glm::mat4 bindMatrix, int boneindex);
	void addChild(Bone* _child) {child.push_back(_child);}
	void getEnd(glm::quat &q, glm::vec3 &v);
	void RemoveTranslate();
	void setBoneMatrix(glm::mat4 m)
	{
		boneMatrix = m;
	}
	glm::mat4 getInverseMatrix();
	glm::mat4 getBoneMatrix();
	void updateBoneMatrix();
	void updateVertex();
	glm::vec3 posBase;
	glm::vec3 posEnd;
	glm::quat rotation;
	void RemoveTranslate(glm::mat4 &);
	Bone* getMainParent() { if(!mainParent) return this; return mainParent;}
	std::vector<glm::mat4> getAllMatrixIndiced();
	std::vector<int> getAllIndice();
	Bone* operator[] (int i)
	{
		return child[i];
	}
	//OLD - unused
	void updateMatrix();
	float* getMatrix() { return matrix;}
	void setMatrix();
	void updateAnimationPos(int time = -1);
	void updateAnimation(int time);
	//
private:
	List<Bone*> child;
	Bone* parent;
	Bone* mainParent;
	List<Vertex*> linked_vertex;
	float length;
	float radius;
	glm::mat4 boneMatrix;
	List<BoneLinkInfo*> linkList;
	BoneMesh* bone;
	AnimationBone* anim;
	//OLD
	float matrix[16];
	//
};

#endif

