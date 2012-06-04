#include "Bone.h"
#include "Object\Object.h"
#include "Scene\Animation.h"
#include "ObjectAccessor\ObjectAccessor.h"

Bone::Bone(float _length ,Bone* _parent)
{
	length = _length;
	parent = _parent;
	mainParent = parent ? parent->getMainParent() : NULL;
	if(parent)
	{
		parent->addChild(this);
		//posBase = parent->posEnd;
	}
	posBase = glm::vec3(0.0f);
	//posEnd = posBase + glm::vec3(0,0,length);
	//updateMatrix();
	anim = new AnimationBone(this);
	bone = CreateBone(length,this);
	bone->UseLight(false);
	updateBoneMatrix();

}


Bone::~Bone(void)
{
}

void Bone::show(glm::vec3 start)
{
	glPushMatrix();
	/*glBegin(GL_LINES);
	glColor3f(1.0f,0,0);
	if(parent)
		glColor3f(0.0f,1.0f,0);
	glm::vec4 _start(0,0,0,1);
	glm::vec4 _end(0,0,length,1);
	_start = boneMatrix*_start;
	_end = boneMatrix*_end;
	glVertex3d(_start.x,_start.y,_start.z);
	glVertex3d(_end.x,_end.y,_end.z);
	glEnd();
	GLdouble d[16];
	glGetDoublev(GL_MODELVIEW,d);*/
	bone->show();
	for(size_t i = 0; i < child.size(); i++)
		child[i]->show(glm::vec3());
	glPopMatrix();

}

void Bone::moveTo(glm::vec3 pos)
{
	posBase = pos;
	updateBoneMatrix();
	updateAnimationPos();
}
void Bone::setMatrix()
{

	if (parent)
	{
		parent->setMatrix();
		glTranslated(0.0, 0.0, parent->getLength());
	}

	glTranslatef(posBase.x, posBase.y, posBase.z);
//	glRotatef(TOROT(rotation.toRot()));
}

void Bone::updateMatrix()
{
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if(parent)
	{
		parent->setMatrix(); 
		glTranslated(0.0, 0.0, parent->getLength());
	}
	if(child.size())
	{
		for(size_t i = 0; i < child.size(); i++)
			child[i]->updateMatrix();
	}
//	glRotatef(TOROT(rotation.toRot()));
	//RemoveTranslate();
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();
}

void Bone::RemoveTranslate()
{
	if(parent)
	{
		glTranslated(0.0, 0.0, -parent->getLength());
		parent->RemoveTranslate();
	}
}

void Bone::RemoveTranslate(glm::mat4 &a)
{
	if(parent)
	{
		a = a*glm::translate(glm::mat4(1.0f),glm::vec3(0,0,parent->getLength()));
		//parent->RemoveTranslate(a);
	}
}
/*

      | a b c d |   | x |
pos = | e f g h | * | y |
      | i j k l |   | z |
      | m n o p |   | 1 |

	  _x = a*x + b*y + c*z + d
	  _y = e*x + f*y + g*z + h
	  _z = i*x + j*y + k*z + l

*/


void Bone::rotate(float angle, glm::vec3 vector)
{
	rotation = rotation * glm::quat_cast(glm::rotate(glm::mat4(1.0f),angle,vector));
	//updateMatrix();
	updateBoneMatrix();
	updateAnimationPos();
}

void Bone::linkVertex(Vertex * _vertex, float w, glm::mat4 bindMatrix,int boneindex)
{

	for(size_t i = 0; i < linkList.size(); i++)
	{
		if(linkList[i]->vert == _vertex)
			return;
	}

	BoneLinkInfo* info = new BoneLinkInfo(this,w,_vertex);
	//updateMatrix();
	
	info->bindMatrix = bindMatrix;
	linkList.push_back(info);
	_vertex->linkList.push_back(info);
	info->boneindex = boneindex;
}

void Bone::getEnd(glm::quat &q, glm::vec3 &v)
{

	if(parent)
		parent->getEnd(q,v);

	q = q* rotation;
	//v += q.rotatePoint(glm::vec3(0,0,length));
}

glm::mat4 Bone::getInverseMatrix()
{
	//updateMatrix();

	return glm::inverse(boneMatrix);
}

glm::mat4 Bone::getBoneMatrix()
{
	return boneMatrix;
}

void Bone::updateBoneMatrix()
{
	glm::mat4 parentMatrix = glm::mat4(1.0);
	if(parent)
	{
		parentMatrix = parent->getBoneMatrix();
		parentMatrix = parentMatrix * glm::translate(glm::mat4(1.0),glm::vec3(0,0,parent->getLength()));
	}


	boneMatrix = glm::translate(glm::mat4(1.0f),posBase)*glm::mat4_cast(rotation);
	boneMatrix = parentMatrix*boneMatrix;
	//RemoveTranslate(boneMatrix);
	bone->setObjectMatrix(boneMatrix);
	if(child.size())
	{
		for(size_t i = 0; i < child.size(); i++)
			child[i]->updateBoneMatrix();
	}
	
}


void Bone::updateAnimationPos(int time)
{
	if(time < 0)
		time = ObjectAccessor::getObjMgr()->getScene()->getTime();
	AnimationBone::MoveInfoBone mv(posBase,rotation,time);
	anim->addMoveInfoBone(mv);
}

void Bone::updateAnimation(int time)
{
	anim->update(time);
	if(child.size())
	{
		for(size_t i = 0; i < child.size(); i++)
			child[i]->updateAnimation(time);
	}
}