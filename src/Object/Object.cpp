
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../opengl.h"
#include "Object.h"

#include "../ObjectAccessor/ObjectAccessor.h"
#include "../Physics/Physics.h"
#include "../Math/Matrix.h"

#include <glut.h>


#define R(dr,r0,i) (dr*i + r0)
#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))
#define OFFSET(a) ((char*)NULL + (a))
#define TOROT(x) acos(x.w)*2,x.x,x.y,x.z
/*	GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
	GLfloat mat_diffuse[] = {0.1, 0.5, 0.8, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat no_shininess[] = {0.0};
	GLfloat low_shininess[] = {8.0};
	GLfloat high_shininess[] = {100.0};
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};*/

Object::Object(glm::vec3 _position, glm::vec3 _repere) : parent(NULL), texture(NULL), shader(NULL)
{
	color = 0xffffffff;
	position = glm::vec3();
	repere = position;
	size = 1.0f;
	animation =  new Animation(this);
	mass = NULL;
	guid = ObjectAccessor::getObjMgr()->nextGUID();
	ObjectAccessor::getObjMgr()->addObject(this);
	heritage = false;
	bind = false,
	showrep = false;
	useLight = true;
	mainBone = NULL;
	type = OBJECT_TYPE_NONE;
	symetrie = glm::vec3(1.0f,1.0f,1.0f);
	position = _position;
	repere = _repere;
	transmatrix = glm::mat4(1);
	rotmatrix = glm::mat4(1);
	updateObjectMatrix();
}

Object::~Object()
{
	if(parent)
		static_cast<Container*>(parent)->delObject(this);
	else ObjectAccessor::getObjMgr()->getScene()->del(this);

	ObjectAccessor::getObjMgr()->delObject(this);

	//if(texture)
		//delete texture;
}

void Object::update(int diff)
{
	updateMass(diff);
}

void Object::updateAnim(int time)
{
	if(mainBone)
		mainBone->updateAnimation(time);
	else
		animation->update(time);
	updateChild(time);
}

void Object::updatePosition(int time)
{
	Animation::MoveInfo mv(position,rotation,time);
	animation->addMoveInfo(mv);
	updatePositionChild(time);
}

void Object::updateMass(int diff)
{
	if(!mass)
		return;

	mass->simulate(diff);
}

void Object::file_export(ofstream file)
{
	file << type;
	file << size;
	file << heritage;
	file << color;
	//file << texture
}

void Object::file_import(ifstream file)
{

}

Container::Container() : Object()
{
	type = OBJECT_TYPE_CONTAINER;
}

Container::Container(glm::vec3 _position) : Object(_position)
{
	type = OBJECT_TYPE_CONTAINER;
}

Container::Container(glm::vec3 _position, glm::vec3 _repere) : Object(_position, _repere)
{
	type = OBJECT_TYPE_CONTAINER;
}

void Container::delObject(Object* obj)
{
	if(object_list.empty())
		return;

	std::size_t max = object_list.size();
	for(std::size_t i = 0; i < max;)
	{
		if(obj == (object_list[i]))
		{
			object_list[i]->setParent(NULL);
			object_list.erase(object_list.begin()+i);
			return;
		}
		else i++;
	}
}

void Container::clearList(bool _delete)
{
	if(object_list.empty())
		return;

	if(_delete)
	{
		std::size_t max = object_list.size();
		for(std::size_t i = 0; i < max; i++)
		{

			object_list[i]->setParent(NULL);
			delete object_list[i];
		}
	}

	object_list.clear();
}

void Container::updateChild(int time)
{
	std::size_t max = object_list.size();
	for(std::size_t i = 0; i < max; i++)
		object_list[i]->updateAnim(time);
}

void Container::updatePositionChild(int time)
{
	std::size_t max = object_list.size();
	for(std::size_t i = 0; i < max; i++)
	{
		object_list[i]->updatePosition(time);
	}
}

void Container::show()
{
	ObjectAccessor::getObjMgr()->getScene()->applyOption();
	if(!(bind && getParent()))
	{
		glLoadName(guid);
		glPushName(0);
	}
	glPushMatrix();
	glTranslatef(position.x,position.y,position.z);
	glTranslatef(repere.x,repere.y,repere.z);
	glRotatef(TODEG*acos(rotation.w)*2,rotation.x,rotation.y,rotation.z);
	if(showrep)
		showrepere();
	glScaled(size*symetrie.x,size*symetrie.y,size*symetrie.z);
	glTranslatef(-repere.x,-repere.y,-repere.z);
	std::size_t max = object_list.size();
	if(shader)
		shader->use();
	for(std::size_t i = 0; i < max; i++)
	{
		object_list[i]->show();
	}
	if(shader)
		shader->use(false);
	glPopMatrix();
	if(!(bind && getParent()))
		glPopName();
}

void Container::addSphere(float r,float stack, float slice,float angle)
{
	bind = true;
	float cosa = 1.0f;
	float sina = 0.0f;
	float cosa1 = cos(angle/stack);
	float sina1 = sin(angle/stack);
	Mesh* s = new Mesh();
	s->heritageMode(true);
	s->setColor(0xffffffff);
	for(int i = 0; i <= stack; i++)
	{
		for(int j = 0; j <= slice; j++)
		{
			glm::vec3 normal;
			Vertex vertex[4];
			normal = glm::vec3(cosa*sin(j*M_PI/slice),sina*sin(j*M_PI/slice), cos(j*M_PI/slice));
			glm::normalize(normal);
			vertex[0] = Vertex(r*cosa*sin(j*M_PI/slice),r*sina*sin(j*M_PI/slice), r*cos(j*M_PI/slice),i/stack,1.0f-j/slice,normal);

			normal = glm::vec3(cosa*sin((j+1)*M_PI/slice),sina*sin((j+1)*M_PI/slice), cos((j+1)*M_PI/slice));
			glm::normalize(normal);
			vertex[1] = Vertex(r*cosa*sin((j+1)*M_PI/slice),r*sina*sin((j+1)*M_PI/slice), r*cos((j+1)*M_PI/slice),i/stack,1.0f-(j+1)/slice,normal);

			normal = glm::vec3(cosa1*sin((j+1)*M_PI/slice),sina1*sin((j+1)*M_PI/slice), cos((j+1)*M_PI/slice));
			glm::normalize(normal);
			vertex[2] = Vertex(r*cosa1*sin((j+1)*M_PI/slice),r*sina1*sin((j+1)*M_PI/slice), r*cos((j+1)*M_PI/slice),(i+1)/stack,1.0f-(j+1)/slice,normal);

			normal = glm::vec3(cosa1*sin(j*M_PI/slice),sina1*sin(j*M_PI/slice), cos(j*M_PI/slice));
			glm::normalize(normal);
			vertex[3] = Vertex(r*cosa1*sin(j*M_PI/slice),r*sina1*sin(j*M_PI/slice), r*cos(j*M_PI/slice),(i+1)/stack,1.0f-j/slice,normal);

			//s->addFace(Face(vertex[0],vertex[1],vertex[2]));
			//s->addFace(Face(vertex[0],vertex[2],vertex[3]));

			/*
			glm::vec3 normal;
			Polygone* poly = new Polygone();
			poly->heritageMode(true);
			poly->setColor(0xffffffff);
			normal = glm::vec3(cosa*sin(j*M_PI/slice),sina*sin(j*M_PI/slice), cos(j*M_PI/slice));
			normal.normalise();
			poly->addVertex(Vertex(r*cosa*sin(j*M_PI/slice),r*sina*sin(j*M_PI/slice), r*cos(j*M_PI/slice),i/stack,1.0f-j/slice,normal));

			normal = glm::vec3(cosa*sin((j+1)*M_PI/slice),sina*sin((j+1)*M_PI/slice), cos((j+1)*M_PI/slice));
			normal.normalise();
			poly->addVertex(Vertex(r*cosa*sin((j+1)*M_PI/slice),r*sina*sin((j+1)*M_PI/slice), r*cos((j+1)*M_PI/slice),i/stack,1.0f-(j+1)/slice,normal));

			normal = glm::vec3(cosa1*sin((j+1)*M_PI/slice),sina1*sin((j+1)*M_PI/slice), cos((j+1)*M_PI/slice));
			normal.normalise();
			poly->addVertex(Vertex(r*cosa1*sin((j+1)*M_PI/slice),r*sina1*sin((j+1)*M_PI/slice), r*cos((j+1)*M_PI/slice),(i+1)/stack,1.0f-(j+1)/slice,normal));

			normal = glm::vec3(cosa1*sin(j*M_PI/slice),sina1*sin(j*M_PI/slice), cos(j*M_PI/slice));
			normal.normalise();
			poly->addVertex(Vertex(r*cosa1*sin(j*M_PI/slice),r*sina1*sin(j*M_PI/slice), r*cos(j*M_PI/slice),(i+1)/stack,1.0f-j/slice,normal));

			addObject(poly);
			*/
		}

	cosa = cosa1;
	sina = sina1;
	cosa1 = cos((i+2)*angle/stack);
	sina1 = sin((i+2)*angle/stack);
	}
	addObject(s);

}

void Container::addCylinder(float r1,float r2, float length,float stack, float slice, float angle)
{
	bind = true;
	float dr = (r2-r1)/slice;
	float _angle = length == 0.0f ? M_PI_2 : -atan((r2-r1)/length);
	Mesh* m = new Mesh();
	m->heritageMode(true);
	m->setColor(0xffffffff);


	for(int i = 0; i < stack;i++)
	{
		for(int j = 0; j <= slice; j++)
		{
			glm::vec3 normal;
			normal = glm::vec3(cos(i*angle/stack)*cos(_angle),sin(i*angle/stack)*cos(_angle),sin(_angle));
			glm::normalize(normal);
			m->addVertex(new Vertex((dr*j + r1)*cos(i*angle/stack),(dr*j + r1)*sin(i*angle/stack), length/slice*j,i/stack,1.0f-j/slice,normal));
			/*Vertex* vertex[4] = {NULL};

			normal = glm::vec3(cos(i*angle/stack)*cos(_angle),sin(i*angle/stack)*cos(_angle),sin(_angle));
			normal.normalise();
			vertex[0] = new Vertex((dr*j + r1)*cos(i*angle/stack),(dr*j + r1)*sin(i*angle/stack), length/slice*j,i/stack,1.0f-j/slice,normal);

			normal = glm::vec3(cos(i*angle/stack)*cos(_angle),sin(i*angle/stack)*cos(_angle),sin(_angle));
			normal.normalise();
			vertex[1] = Vertex((dr*(j+1) + r1)*cos(i*angle/stack),(dr*(j+1) + r1)*sin(i*angle/stack), length/slice*(j+1),i/stack,1.0f-(j+1)/slice,normal);

			normal = glm::vec3(cos((i+1)*angle/stack)*cos(_angle),sin((i+1)*angle/stack)*cos(_angle),sin(_angle));
			normal.normalise();
			vertex[2] = Vertex((dr*(j+1) + r1)*cos((i+1)*angle/stack),(dr*(j+1) + r1)*sin((i+1)*angle/stack), length/slice*(j+1),(i+1)/stack,1.0f-(j+1)/slice,normal);

			normal = glm::vec3(cos((i+1)*angle/stack)*cos(_angle),sin((i+1)*angle/stack)*cos(_angle),sin(_angle));
			normal.normalise();
			vertex[3] = Vertex((dr*j + r1)*cos((i+1)*angle/stack),(dr*j + r1)*sin((i+1)*angle/stack), length/slice*j,(i+1)/stack,1.0f-j/slice,normal);


			m->addFace(Face(vertex[0],vertex[1],vertex[2]));
			m->addFace(Face(vertex[0],vertex[2],vertex[3]));*/
		}
	}

	for(int i = 0; i < stack;i++)
	{
		for(int j = 0; j < slice; j++)
		{
			/*(i,j+1) _ _ (i+1,j+1)
			         |  /|
			         | / |
			    (i,j)|/  |(i+1,j)
			*/
			int _i = SELECT(i+1,stack), _j = SELECT(j+1,(slice+1));
			m->addFace(Face(i*(slice+1)+j,_i*(slice+1)+j,i*(slice+1)+_j));
			m->addFace(Face(_i*(slice+1)+j,_i*(slice+1)+_j,i*(slice+1)+_j));
		}
	}
	addObject(m);
}

void Container::addDisk(float r,float stack,float angle)
{
	bind = true;
		for(int i = 0; i < stack; i++)
		{
			Polygone* poly = new Polygone();
			poly->setColor(0xffffffff);
			poly->heritageMode(true);
			poly->addVertex(Vertex(r*cos(i*angle/stack),r*sin(i*angle/stack), 0.0f,(i)/stack,1.0f,glm::vec3(0,0,1.0f)));
			poly->addVertex(Vertex(0.0f,0.0f, 0.0f,(i)/stack,0.0f,glm::vec3(0,0,1.0f)));
			poly->addVertex(Vertex(r*cos((i+1)*angle/stack),r*sin((i+1)*angle/stack), 0.0f,(i+1)/stack,1.0f,glm::vec3(0,0,1.0f)));
			addObject(poly);
		}
}

void Container::addTorus(float r1, float r2, float side, float ring, float angle1, float angle2, float angle1_beg)
{
	bind = true;
	r2 += r1*2;
	for(int i = 0; i <	1; i++)
	{
	/*	Matrix m1 = Matrix::getRotateMatrix2(i*angle/ring);
		Matrix m2 = Matrix::getRotateMatrix2((i+1)*angle/ring);
		*/


		for(int j = 0; j < side; j++)
		{

			Polygone* poly = new Polygone();
			poly->setColor(0xff00ff00);
			/*poly->addVertex(Vertex(r2*cos(i*angle2/ring)*r1*cos(j*angle1/side),r2*sin(i*angle2/ring)*r1*cos(j*angle1/side), r1*sin(j*angle1/side)));
			poly->addVertex(Vertex(r2*cos(i*angle2/ring)*r1*cos((j+1)*angle1/side),r2*sin(i*angle2/ring)*r1*cos((j+1)*angle1/side), r1*sin((j+1)*angle1/side)));
			poly->addVertex(Vertex(r2*cos((i+1)*angle2/ring)*r1*cos((j+1)*angle1/side),r2*sin((i+1)*angle2/ring)*r1*cos((j+1)*angle1/side), r1*sin((j+1)*angle1/side)));
			poly->addVertex(Vertex(r2*cos((i+1)*angle2/ring)*r1*cos(j*angle1/side),r2*sin((i+1)*angle2/ring)*r1*cos(j*angle1/side),r1*sin(j*angle1/side)));*/
			addObject(poly);
		}
	}
}
Polygone::Polygone() : Object()
{

}

Polygone::Polygone(glm::vec3 _position) : Object(_position)
{

}

Polygone::Polygone(glm::vec3 _position, glm::vec3 _repere) : Object(_position, _repere)
{

}

Polygone::~Polygone()
{
	if(vertex_list.size())
		return;
	std::size_t max = vertex_list.size();
	for(std::size_t i = 0; i < max; i++)
		delete vertex_list[i];
}

void Polygone::show()
{
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	//glScaled(size*symetrie.x,size*symetrie.y,size*symetrie.z);
	if(Texture* t = getTexture())
	{
		glBindTexture(GL_TEXTURE_2D,t->getTextureID());
	} else glBindTexture(GL_TEXTURE_2D,0);
	std::size_t max = vertex_list.size();
	//glm::vec3 normal;
	//if(max >= 3) //calcul de la normal
	//{
		//glm::vec3 v1(vertex_list[1]->x-vertex_list[0]->x,vertex_list[1]->y-vertex_list[0]->y,vertex_list[1]->z-vertex_list[0]->z);
		//glm::vec3 v2(vertex_list[2]->x-vertex_list[0]->x,vertex_list[2]->y-vertex_list[0]->y,vertex_list[2]->z-vertex_list[0]->z);
		//normal = v2.crossProduct(v1);
		//normal.normalise();
	//}
	glBegin(GL_POLYGON);
	for(std::size_t i = 0; i < max; i++)
	{

		glColor4ub(TOCOLOR4(color));
		
		glNormal3d(vertex_list[i]->normal.x,vertex_list[i]->normal.y,vertex_list[i]->normal.z);
		glTexCoord2f(vertex_list[i]->u,vertex_list[i]->v);
		glVertex3d(vertex_list[i]->x,vertex_list[i]->y,vertex_list[i]->z);
		

	}
	glEnd();
	

	// show normal
	/*for(std::size_t i = 0; i < max; i++)
	{
		if(vertex_list[i]->normal.isNull())
			showVecteur(glm::vec3(vertex_list[i]->x,vertex_list[i]->y,vertex_list[i]->z),normal);
		else showVecteur(glm::vec3(vertex_list[i]->x,vertex_list[i]->y,vertex_list[i]->z),vertex_list[i]->normal);
	}*/
	
}

void Polygone::delVertex(Vertex v)
{
	if(vertex_list.empty())
		return;

	std::size_t max = vertex_list.size();
	for(std::size_t i = 0; i < max; i++)
	{
		if(v == (*vertex_list[i]))
		{
			vertex_list.erase(vertex_list.begin()+i);
			delete vertex_list[i];
		}
	}
}

void Mesh::calculateNormal()
{
	glm::vec3 * m_NormalArray = new glm::vec3[vertex_list.size()];

	// Assigne le vecteur (0,0,0)
	for(size_t i = 0; i < vertex_list.size(); i++)
	{
		m_NormalArray[i] = glm::vec3();
	}
	//Calc normal
	for(size_t i = 0; i < face_list.size(); i++)
	{
		int index1 = face_list[i]->vertex[0];
		int index2 = face_list[i]->vertex[1];
		int index3 = face_list[i]->vertex[2];
		glm::vec3 a(vertex_list[index3]->x - vertex_list[index2]->x,vertex_list[index3]->y - vertex_list[index2]->y,vertex_list[index3]->z - vertex_list[index2]->z);
		glm::vec3 b(vertex_list[index1]->x - vertex_list[index2]->x,vertex_list[index1]->y - vertex_list[index2]->y,vertex_list[index1]->z - vertex_list[index2]->z);
		glm::vec3 normal = glm::cross(b,a);
		m_NormalArray[index1] += normal;
		m_NormalArray[index2] += normal;
		m_NormalArray[index3] += normal;
	}

	// Normalise le vecteur
	for(size_t i = 0; i < vertex_list.size(); i++)
	{
		glm::normalize(m_NormalArray[i]);
		vertex_list[i]->normal = m_NormalArray[i];
	}
	delete m_NormalArray;
}

void Mesh::UpdateBuffer(bool fullupdate)
{
	int* m_ColorArray = new int[vertex_list.size()];
	glm::vec3* m_PositionArray = new glm::vec3[vertex_list.size()];
	glm::vec3* m_NormalArray = new glm::vec3[vertex_list.size()];
	glm::vec2* m_TexCoordArray = new glm::vec2[vertex_list.size()];

	glm::vec4* m_WeightArray = new glm::vec4[vertex_list.size()];
	glm::vec4* m_BoneIndiceArray = new glm::vec4[vertex_list.size()];

	//Création des buffers
	if(!m_ColorBuffer)
	{
		glGenBuffers(1,&m_ColorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_list.size()*sizeof(int), NULL, GL_STREAM_DRAW);
	}

	if(!m_PositionBuffer)
	{
		glGenBuffers(1,&m_PositionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_PositionBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_list.size()*sizeof(glm::vec3), NULL, GL_STREAM_DRAW);
	}

	if(!m_NormalBuffer)
	{
		glGenBuffers(1,&m_NormalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_list.size()*sizeof(glm::vec3), NULL, GL_STREAM_DRAW);
	}

	if(!m_TexCoordBuffer)
	{
		glGenBuffers(1,&m_TexCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_list.size()*sizeof(glm::vec2), NULL, GL_STREAM_DRAW);
	}

	if(!m_IndiceBuffer)
	{
		glGenBuffers(1,&m_IndiceBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IndiceBuffer);
		int* _indices = new int[face_list.size()*3];
		for(size_t i = 0; i < face_list.size(); i++)
			memcpy(&_indices[i*3],face_list[i]->vertex,sizeof(int)*3);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_list.size()*sizeof(int)*3, _indices, GL_STATIC_DRAW);
		delete _indices;
	}

	//

	if(!m_WeightBoneBuffer)
	{
		glGenBuffers(1,&m_WeightBoneBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_WeightBoneBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_list.size()*sizeof(glm::vec4), NULL, GL_STREAM_DRAW);
	}

	if(!m_IndiceBoneBuffer)
	{
		glGenBuffers(1,&m_IndiceBoneBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_IndiceBoneBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_list.size()*sizeof(glm::vec4), NULL, GL_STREAM_DRAW);
	}


	//

	for(size_t i = 0; i < vertex_list.size(); i++)
	{
		m_ColorArray[i] = color;
		m_PositionArray[i].x = vertex_list[i]->x;
		m_PositionArray[i].y = vertex_list[i]->y;
		m_PositionArray[i].z = vertex_list[i]->z;
		m_TexCoordArray[i].x = vertex_list[i]->u;
		m_TexCoordArray[i].y = vertex_list[i]->v;
		m_NormalArray[i] = vertex_list[i]->normal;
		for(size_t j = 0; j < 4; j++)
		{
			m_WeightArray[i][j] = j >= vertex_list[i]->linkList.size() ? -1.0f : vertex_list[i]->linkList[j]->weight;
			m_BoneIndiceArray[i][j] = j >= vertex_list[i]->linkList.size() ? -1.0f : (float)vertex_list[i]->linkList[j]->boneindex;
		}
	}
	//calc normal;
	/*for(size_t i = 0; i < face_list.size(); i++)
	{
		int index1 = face_list[i]->vertex[0];
		int index2 = face_list[i]->vertex[1];
		int index3 = face_list[i]->vertex[2];
		glm::vec3 a(m_PositionArray[index3] - m_PositionArray[index2]);
		glm::vec3 b(m_PositionArray[index1] - m_PositionArray[index2]);
		glm::vec3 normal = glm::cross(a,b);
		m_NormalArray[index1] += normal;
		m_NormalArray[index2] += normal;
		m_NormalArray[index3] += normal;
	}*/

	for(size_t i = 0; i < vertex_list.size(); i++)
	{
		glm::normalize(m_NormalArray[i]);
	}
	// liage au buffer

	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
	void* pos_vbo = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if(pos_vbo != NULL)
	{
		memcpy(pos_vbo,m_ColorArray,vertex_list.size()*sizeof(int));
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	delete m_ColorArray;

	glBindBuffer(GL_ARRAY_BUFFER, m_PositionBuffer);
	pos_vbo = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if(pos_vbo != NULL)
	{
		memcpy(pos_vbo,m_PositionArray,vertex_list.size()*sizeof(glm::vec3));
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	delete m_PositionArray;

	glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
	pos_vbo = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if(pos_vbo != NULL)
	{
		memcpy(pos_vbo,m_NormalArray,vertex_list.size()*sizeof(glm::vec3));
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	delete m_NormalArray;

	glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordBuffer);
	pos_vbo = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if(pos_vbo != NULL)
	{
		memcpy(pos_vbo,m_TexCoordArray,vertex_list.size()*sizeof(glm::vec2));
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	delete m_TexCoordArray;

	glBindBuffer(GL_ARRAY_BUFFER, m_IndiceBoneBuffer);
	pos_vbo = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if(pos_vbo != NULL)
	{
		memcpy(pos_vbo,m_BoneIndiceArray,vertex_list.size()*sizeof(glm::vec4));
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	delete m_BoneIndiceArray;

	glBindBuffer(GL_ARRAY_BUFFER, m_WeightBoneBuffer);
	pos_vbo = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if(pos_vbo != NULL)
	{
		memcpy(pos_vbo,m_WeightArray,vertex_list.size()*sizeof(glm::vec4));
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	delete m_WeightArray;
}

void Mesh::SetupUniform(bool disable)
{

	Shader* sh = ObjectAccessor::getObjMgr()->getScene()->GetActiveShader();
	UniformVar enable = sh->getUniform("boneSkinning");
	UniformVar transformloc = sh->getUniform("transform");
	UniformVar lightloc = sh->getUniform("uselight");
	UniformVar enabletexture = sh->getUniform("usetexture");
	if(disable)
	{
		glUniform1i(enable.loc,0);
		glUniform1i(enabletexture.loc,0);
		glUniformMatrix4fv(transformloc.loc,1,GL_FALSE,glm::value_ptr(glm::mat4(1.0f)));
		return;
	}
	glUniform1i(enable.loc,bone_list.size() > 0);

	if(lightloc.loc != -1 && useLight)
	{
		glUniform1i(lightloc.loc,1);
	}else glUniform1i(lightloc.loc,0);
	
	UniformVar tex = sh->getUniform("texture");
	Texture* _texture = getTexture();
	if(_texture)
	{
		glUniform1i(enabletexture.loc,1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,_texture->getTextureID());
		glUniform1i(tex.loc,0);	
	}else 
	{
		//TextureMgr::getTextureMgr()->getTexture("../../"
		glUniform1i(enabletexture.loc,0);
	}

	if(transformloc.loc != -1)
		glUniformMatrix4fv(transformloc.loc,1,GL_FALSE,glm::value_ptr(objectMatrix));

	//if(lightloc.loc != -1)
		//glUniform1i(lightloc.loc,(int)useLight);

	UniformVar boneloc = sh->getUniform("bone");
	UniformVar inverseboneloc = sh->getUniform("inverse_bone");

	if(boneloc.loc == -1 || inverseboneloc.loc == -1)
		return;
	for(size_t i = 0; i < 10; i++)
	{
		if(i < bone_list.size())
		{
			glUniformMatrix4fv(boneloc.loc+i,1,0,glm::value_ptr(bone_list[i]->getBoneMatrix()));
			glUniformMatrix4fv(inverseboneloc.loc+i,1,0,glm::value_ptr(inversebone_list[i]));
		}
		else // si le bone n'existe pas, on envoit juste 2 matrix identité.
		{
			glUniformMatrix4fv(boneloc.loc+i,1,0,glm::value_ptr(glm::mat4(1.0f)));
			glUniformMatrix4fv(inverseboneloc.loc+i,1,0,glm::value_ptr(glm::mat4(1.0f)));
		}
	}
}

void Mesh::SetupAttribut(bool disable)
{
	Shader* sh = ObjectAccessor::getObjMgr()->getScene()->GetActiveShader();
	AttributVar weight = sh->getAttribut("weight");
	AttributVar indice = sh->getAttribut("bone_indices");
	if(weight.loc == -1 || indice.loc == -1)
		return;

	if(disable)
	{
		glDisableVertexAttribArray(weight.loc);
		glDisableVertexAttribArray(indice.loc);
		return;
	}

	glEnableVertexAttribArray(weight.loc);
	glBindBuffer(GL_ARRAY_BUFFER,m_WeightBoneBuffer);
	glVertexAttribPointer(weight.loc,4,GL_FLOAT,GL_FALSE,sizeof(glm::vec4),OFFSET(0));

	glEnableVertexAttribArray(indice.loc);
	glBindBuffer(GL_ARRAY_BUFFER,m_IndiceBoneBuffer);
	glVertexAttribPointer(indice.loc,4,GL_FLOAT,GL_FALSE,sizeof(glm::vec4),OFFSET(0));
}

void Mesh::show()
{
	if(!m_PositionBuffer)
		UpdateBuffer();

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
	glColorPointer(4,GL_UNSIGNED_BYTE,sizeof(int),OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, m_PositionBuffer);
	glVertexPointer(3,GL_FLOAT,sizeof(glm::vec3),OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
	glNormalPointer(GL_FLOAT,sizeof(glm::vec3),OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordBuffer);
	glTexCoordPointer(2,GL_FLOAT,sizeof(glm::vec2),OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndiceBuffer);

	//Shader part
	SetupUniform();
	// Attribut
	SetupAttribut();
	//end Shader part
	glLoadName(guid);
	glPushName(0);
	glDrawElements(GL_TRIANGLES, face_list.size()*3, GL_UNSIGNED_INT, OFFSET(0));
	glPopName();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	SetupUniform(true);
	SetupAttribut(true);
}

void Mesh::linkVertex(int vertex,int bone, float w, glm::mat4 mat)
{
	Vertex* vert = vertex_list[vertex];
	Bone* _bone = bone_list[bone];
	_bone->linkVertex(vert,w,mat,bone);
}

Light::Light(glm::vec3 pos) : Object(pos)
{
	n_light = ObjectAccessor::getObjMgr()->getScene()->getUnusableLight();
	ObjectAccessor::getObjMgr()->getScene()->enableLight(n_light);
	setDir(glm::vec3(1.0f,0.0f,0.0f));
	setSpot(180);
	setColor(color);
	setPosition(pos);
}

void Light::setDir(glm::vec3 dir)
{
	if(n_light < 0 || n_light >= MAX_LIGHT)
		return;
	this->dir = dir;
	glm::mat4 mat(glm::mat4_cast(rotation));
	glm::vec3 _vdir = glm::vec3(mat * glm::vec4(dir,1.0f));
	float _dir[3];
	_dir[0] = _vdir.x;
	_dir[1] = _vdir.y;
	_dir[2] = _vdir.z;
	glLightfv(GL_LIGHT0+n_light, GL_SPOT_DIRECTION, _dir);
}

void Light::setPosition(glm::vec3 pos)
{ 
	Object::setPosition(pos);
	if(n_light < 0 || n_light >= MAX_LIGHT)
		return;

	float _pos[4];
	_pos[0] = position.x;
	_pos[1] = position.y;
	_pos[2] = position.z;
	_pos[3] = 1.0f;
	glLightfv(GL_LIGHT0+n_light, GL_POSITION, _pos);
}

void Light::setColor(int color)
{
	Object::setColor(color);
	if(n_light < 0 || n_light >= MAX_LIGHT)
		return;

	float _color[4];
	for(int i = 0; i < 4; i++)
		_color[i] = ((unsigned char*)&color)[i]/255.0f;

	glLightfv(GL_LIGHT0+n_light, GL_DIFFUSE, _color);
}

//void Light::setExponent

void Light::show()
{
	if(n_light < 0 || n_light >= MAX_LIGHT)
		return;

	glEnable(GL_LIGHT0+n_light);
	float value = 10;
	if(spot !=180.0f)
		glLightfv(GL_LIGHT0+n_light, GL_SPOT_EXPONENT, &value);
	setPosition(position);
	setDir(dir);
	glLoadName(guid);
	glPushName(0);
	glPushMatrix();
	glTranslated(position.x,position.y,position.z);
	//glRotatef(TOROT(rotation.toRot()));
	if(showrep)
		showrepere();
	glColor4ub(TOCOLOR4(color));
	glDisable(GL_LIGHTING);
	/*glBegin(GL_LINES);
	glVertex3d(0.0f,0.0f,0.0f);
	glVertex3d(dir.x,dir.y,dir.z);
	glEnd();
	glutSolidSphere(0.1f,20,20);*/
	ObjectAccessor::getObjMgr()->getScene()->applyOption();
	glPopMatrix();
	glPopName();
}
float randomValue(float min, float max)
{  return (float) (min + (max - min)*((float) rand() / (RAND_MAX + 1.0)));
}

ParticleGenerator::ParticleGenerator(glm::vec3 _pos, int _life_particle, int _maxParticle, glm::vec3 _dir) : Object(_pos)
{
	speed = _dir;
	life_particle = _life_particle;
	maxParticle = _maxParticle;
	part = new Particle*[maxParticle];
	memset(part,0,maxParticle*sizeof(Particle*));
	angle = M_PI/12;
	acc = glm::vec3();
	t = 0;
	particle_shader = new Shader("../../src/Shader/ParticleSimple.vert","../../src/Shader/ParticleSimple.frag");
	generateParticle();


}
ParticleGenerator::~ParticleGenerator()
{
	for(int i = 0; i < maxParticle; i++)
	{
		if(part[i])
			delete part[i];
	}
}
void ParticleGenerator::generateParticle()
{
	for(int i = 0; i < maxParticle; i++)
	{
		float _t = t/1000.0f;
		float ttl = life_particle/1000.0f;
		float _angle = randomValue(0,M_PI*2);
		float _angle2 = randomValue(0,angle);
		glm::vec3 _speed(speed.z*cos(_angle)*sin(_angle2),speed.z*sin(_angle)*sin(_angle2),speed.z*cos(_angle2));
		part[i] = new Particle(_speed,acc,_t+randomValue(0.0f,ttl),ttl,particle_shader->getProgramId());
	}
}

void ParticleGenerator::update(int diff)
{
	t += diff;
}

void ParticleGenerator::show()
{
	float _t = t/1000.0f;
	float ttl = life_particle/1000.0f;
	for(int i = 0; i < maxParticle; i++ )
	{		
		if(!part[i]->show(_t))
		{
			float _angle = randomValue(0,M_PI*2);
			float _angle2 = randomValue(0,angle);
			glm::vec3 _speed(speed.z*cos(_angle)*sin(_angle2),speed.z*sin(_angle)*sin(_angle2),speed.z*cos(_angle2));
			part[i]->generate(_speed,acc,_t+randomValue(0.0f,ttl),ttl);
		}
	}
}
Sphere::Sphere() : Container()
{
	radius = 1.0f;
	angle = M_PI*2;
	stacks = 20;
	slices = 20;
	buildSphere();
}

Sphere::Sphere(glm::vec3 pos, float r) : Container(pos)
{
	radius = r;
	angle = M_PI*2;
	stacks = 20;
	slices = 20;
	buildSphere();
}

void Sphere::buildSphere()
{
	clearList(true);
	float cosa = 1.0f;
	float sina = 0.0f;
	float cosa1 = cos(angle/stacks);
	float sina1 = sin(angle/stacks);
	for(float i = 0; i < stacks; i++)
	{
		for(float j = 0; j < slices; j++)
		{
			glm::vec3 normal;
			Polygone* poly = new Polygone();
			poly->heritageMode(true);
			poly->setColor(0xffffffff);
			normal = glm::vec3(cosa*sin(j*M_PI/slices),sina*sin(j*M_PI/slices), cos(j*M_PI/slices));
			glm::normalize(normal);
			
			poly->addVertex(Vertex(radius*cosa*sin(j*M_PI/slices),radius*sina*sin(j*M_PI/slices), radius*cos(j*M_PI/slices),i/stacks,1.0f-j/slices,normal));

			normal = glm::vec3(cosa*sin((j+1)*M_PI/slices),sina*sin((j+1)*M_PI/slices), cos((j+1)*M_PI/slices));
			glm::normalize(normal);
			poly->addVertex(Vertex(radius*cosa*sin((j+1)*M_PI/slices),radius*sina*sin((j+1)*M_PI/slices), radius*cos((j+1)*M_PI/slices),i/stacks,1.0f-(j+1)/slices,normal));

			normal = glm::vec3(cosa1*sin((j+1)*M_PI/slices),sina1*sin((j+1)*M_PI/slices), cos((j+1)*M_PI/slices));
			glm::normalize(normal);
			poly->addVertex(Vertex(radius*cosa1*sin((j+1)*M_PI/slices),radius*sina1*sin((j+1)*M_PI/slices), radius*cos((j+1)*M_PI/slices),(i+1)/stacks,1.0f-(j+1)/slices,normal));

			normal = glm::vec3(cosa1*sin(j*M_PI/slices),sina1*sin(j*M_PI/slices), cos(j*M_PI/slices));
			glm::normalize(normal);
			poly->addVertex(Vertex(radius*cosa1*sin(j*M_PI/slices),radius*sina1*sin(j*M_PI/slices), radius*cos(j*M_PI/slices),(i+1)/stacks,1.0f-j/slices,normal));

			addObject(poly);
		}

	cosa = cosa1;
	sina = sina1;
	cosa1 = cos((i+2)*angle/stacks);
	sina1 = sin((i+2)*angle/stacks);
	}
}



Box::Box() : Container()
{
	length = glm::vec3(1.0f,1.0f,1.0f);
	buildBox();
	bind = true;
}
Box::Box(glm::vec3 pos, glm::vec3 side_length) : Container(pos)
{
	length = side_length;
	buildBox();
	bind = true;
}

#define SIGNE(x) x >= 0 ? 1.0f : -1.0f
void Box::buildBox()
{
	clearList(true);
	
	Polygone* poly;
	glm::vec3 normal;
	float _x,_y,_z;
	_x = SIGNE(length.x);
	_y = SIGNE(length.y);
	_z = SIGNE(length.z);

	glm::vec3 _normal[6] = 
	{
		glm::vec3(1.0f*_x,0,0),
		glm::vec3(-1.0f*_x,0,0),
		glm::vec3(0,1.0f*_y,0),
		glm::vec3(0,-1.0f*_y,0),
		glm::vec3(0,0,1.0f*_z),
		glm::vec3(0,0,-1.0f*_z)
	};
	// FACE 1
	normal = _normal[5];
	poly  = new Polygone();
	//normal = _normal[1]+_normal[3]+_normal[5];
	poly->addVertex(Vertex(0,0,0,0,0,normal));
	//normal = _normal[0]+_normal[3]+_normal[5];
	poly->addVertex(Vertex(length.x,0,0,1,0,normal));
	//normal = _normal[0]+_normal[2]+_normal[5];
	poly->addVertex(Vertex(length.x,length.y,0,1,1,normal));
	//normal = _normal[1]+_normal[2]+_normal[5];
	poly->addVertex(Vertex(0,length.y,0,0,1,normal));
	addObject(poly);

	// FACE 2
	normal = _normal[4];
	poly  = new Polygone();
	//normal = _normal[1]+_normal[3]+_normal[4];
	poly->addVertex(Vertex(0,0,length.z,0,0,normal));
	//normal = _normal[0]+_normal[3]+_normal[4];
	poly->addVertex(Vertex(length.x,0,length.z,1,0,normal));
	//normal = _normal[0]+_normal[2]+_normal[4];
	poly->addVertex(Vertex(length.x,length.y,length.z,1,1,normal));
	//normal = _normal[1]+_normal[2]+_normal[4];
	poly->addVertex(Vertex(0,length.y,length.z,0,1,normal));
	addObject(poly);

	// FACE 3
	normal = _normal[3];
	poly  = new Polygone();
	//normal = _normal[1]+_normal[3]+_normal[5];
	poly->addVertex(Vertex(0,0,0,0,0,normal));
	//normal = _normal[0]+_normal[3]+_normal[5];
	poly->addVertex(Vertex(length.x,0,0,1,0,normal));
	//normal = _normal[0]+_normal[3]+_normal[4];
	poly->addVertex(Vertex(length.x,0,length.z,1,1,normal));
	//normal = _normal[1]+_normal[3]+_normal[4];
	poly->addVertex(Vertex(0,0,length.z,0,1,normal));
	addObject(poly);

	// FACE 4
	normal = _normal[2];
	poly  = new Polygone();
	//normal = _normal[1]+_normal[2]+_normal[5];
	poly->addVertex(Vertex(0,length.y,0,0,0,normal));
	//normal = _normal[0]+_normal[2]+_normal[5];
	poly->addVertex(Vertex(length.x,length.y,0,1,0,normal));
	//normal = _normal[0]+_normal[2]+_normal[4];
	poly->addVertex(Vertex(length.x,length.y,length.z,1,1,normal));
	//normal = _normal[1]+_normal[2]+_normal[4];
	poly->addVertex(Vertex(0,length.y,length.z,0,1,normal));
	addObject(poly);


	// FACE 5
	normal = _normal[1];
	poly  = new Polygone();
	//normal = _normal[1]+_normal[3]+_normal[5];
	poly->addVertex(Vertex(0,0,0,0,0,normal));
	//normal = _normal[1]+_normal[2]+_normal[5];
	poly->addVertex(Vertex(0,length.y,0,1,0,normal));
	//normal = _normal[1]+_normal[2]+_normal[4];
	poly->addVertex(Vertex(0,length.y,length.z,1,1,normal));
	//normal = _normal[1]+_normal[3]+_normal[4];
	poly->addVertex(Vertex(0,0,length.z,0,1,normal));
	addObject(poly);

	// FACE 6
	normal = _normal[0];
	poly  = new Polygone();
	//normal = _normal[0]+_normal[3]+_normal[5];
	poly->addVertex(Vertex(length.x,0,0,0,0,normal));
	//normal = _normal[0]+_normal[2]+_normal[5];
	poly->addVertex(Vertex(length.x,length.y,0,1,0,normal));
	//normal = _normal[0]+_normal[2]+_normal[4];
	poly->addVertex(Vertex(length.x,length.y,length.z,1,1,normal));
	//normal = _normal[0]+_normal[3]+_normal[4];
	poly->addVertex(Vertex(length.x,0,length.z,0,1,normal));
	addObject(poly);

}


void render_string(float x, float y, float z, const char* s)
{
    glDisable(GL_TEXTURE_2D);
	glColor3f(0,255,0);
	glRasterPos3f(x,y,z);


    while(*s)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *s);
        s++;
    }

	ObjectAccessor::getObjMgr()->getScene()->applyOption();
}


void showrepere()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3ub(255,0,0);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(1.0f,0.0f,0.0f);
	glEnd();
	render_string(1, 0, 0, "x");

	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3ub(0,255,0);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glEnd();
	render_string(0, 1, 0, "y");

	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3ub(0,0,255);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,1.0f);
	glEnd();
	render_string(0, 0, 1, "z");
	ObjectAccessor::getObjMgr()->getScene()->applyOption();
}

void showVecteur(glm::vec3 p,glm::vec3 vect)
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	//glColor3ub(255,0,0);
	glVertex3f(p.x,p.y,p.z);
	glVertex3f(p.x+vect.x,p.y+vect.y,p.z+vect.z);
	glEnd();

	ObjectAccessor::getObjMgr()->getScene()->applyOption();
}


/*
	C*E				-C*F			-D		0
	-B*D*E + A*F	B*D*F+ A*E		-B*C	0
	A*D*E + B*F		-A*D*F + B*E	A*C		0
	0				0				0		1

A       = cos(angle_x);
B       = sin(angle_x);
C       = cos(angle_y);
D       = sin(angle_y);
E       = cos(angle_z);
F       = sin(angle_z);


if C = 0 (angle_y = 0);

	0				0			-D		0
	-B*D*E + A*F	B*D*F+ A*E		-B*C	0
	A*D*E + B*F		-A*D*F + B*E	A*C		0
	0				0				0		1

*//*
void getEulerAngle(float angles[3], GLfloat * tab)
{
	float A,B,C,D,E,F;
	Matrice * mat = ToMatrice(tab);
	D = -mat->mat[0][2];
	(angles)[1] = asin(D);
	C = cos(angles[1]);

	if(fabs(C) > 0.0f)
	{
		A = mat->mat[1][2]/C;
		B = -mat->mat[2][2]/C;
		E = mat->mat[0][0]/C;
		F = -mat->mat[0][1]/C;

		(angles)[0] = atan2(B,A);
		(angles)[2] = atan2(F,E);
	}else
	{
		(angles)[0] = 0.0f;
		E = mat->mat[1][1];
		F = mat->mat[1][0];

		(angles)[2]  = atan2(F, E);
	}
}*/

void Vertex::getLinkInfo(_linkinfo *tab)
{
	if(linkList.size())
	{
		size_t _max = (linkList.size() > 10 ? 10 : linkList.size());
		for(size_t i = 0; i < _max; i++)
		{
			float* m1 = linkList[i]->bone->getMatrix();
			for(int j = 0;  j < 16; j++)
				tab[i].matrix[j] = (float)m1[j];

			tab[i].weight = linkList[i]->weight;
		}
	}
}
void Vertex::getPosition(float &_x, float &_y, float &_z)
{
	_x = 0; _y = 0; _z = 0;
	if(linkList.size())
	{
		size_t _size = linkList.size();
		float weightTot = 0;
		glm::vec3 init_pos(x,y,z);
		glm::vec3 end_pos;
		for(size_t i = 0; i < _size; i++)
		{
			weightTot += linkList[i]->weight;
			//linkList[i]->getPos(x,y,z,_x,_y,_z);
			glm::mat4 mat = (linkList[i]->bone->getBoneMatrix());
			glm::mat4 transfo = mat * linkList[i]->bindMatrix;
			end_pos += glm::vec3(transfo*glm::vec4(init_pos,1.0f)*linkList[i]->weight);
			/*_x += (mat[0]*x + mat[4]*y + mat[8]*z + mat[12])*linkList[i]->weight;
			_y += (mat[1]*x + mat[5]*y + mat[9]*z + mat[13])*linkList[i]->weight;;
			_z += (mat[2]*x + mat[6]*y + mat[10]*z + mat[14])*linkList[i]->weight;
			*/
		}
		_x=end_pos.x;
		_y=end_pos.y;
		_z=end_pos.z;
		_x/=weightTot;
		_y/=weightTot;
		_z/=weightTot;
	}else
	{

	
		_x = x;
		_y = y;
		_z = z;
	}
}

void Vertex::updatePos()
{
	if(linkList.size())
	{
		size_t _size = linkList.size();
		float weightTot = 0;
		glm::vec3 init_pos(x,y,z);
		glm::vec3 end_pos;
		for(size_t i = 0; i < _size; i++)
		{
			weightTot += linkList[i]->weight;
			//linkList[i]->getPos(x,y,z,_x,_y,_z);
			glm::mat4 mat = (linkList[i]->bone->getBoneMatrix());
			glm::mat4 transfo = mat* linkList[i]->bindMatrix;
//			end_pos += transfo*init_pos*linkList[i]->weight;
			/*_x += (mat[0]*x + mat[4]*y + mat[8]*z + mat[12])*linkList[i]->weight;
			_y += (mat[1]*x + mat[5]*y + mat[9]*z + mat[13])*linkList[i]->weight;;
			_z += (mat[2]*x + mat[6]*y + mat[10]*z + mat[14])*linkList[i]->weight;
			*/
		}
		x=end_pos.x;
		y=end_pos.y;
		z=end_pos.z;
		x/=weightTot;
		y/=weightTot;
		z/=weightTot;
	}
}


// MESH BUILDER

Mesh* CreateSphere(float r,float stack, float slice,float angle)
{

	float cosa = 1.0f;
	float sina = 0.0f;
	float cosa1 = cos(angle/stack);
	float sina1 = sin(angle/stack);
	Mesh* m = new Mesh();
	m->setColor(0xffffffff);

	for(int i = 0; i <= stack; i++)
	{
		for(int j = 0; j <= slice; j++)
		{
			glm::vec3 normal;
			normal = glm::vec3(cos(i*angle/stack)*sin(j*M_PI/slice),sin(i*angle/stack)*sin(j*M_PI/slice), cos(j*M_PI/slice));
			glm::normalize(normal);
			m->addVertex(new Vertex(r*cos(i*angle/stack)*sin(j*M_PI/slice),r*sin(i*angle/stack)*sin(j*M_PI/slice), r*cos(j*M_PI/slice),i/stack,1.0f-j/slice,normal));
		}
	}

	for(int i = 0; i < stack;i++)
	{
		for(int j = 0; j < slice; j++)
		{
			/*(i,j+1) _ _ (i+1,j+1)
			         |  /|
			         | / |
			    (i,j)|/  |(i+1,j)
			*/
			int _i = SELECT(i+1,stack+1), _j = SELECT(j+1,(slice+1));
			m->addFace(Face(_i*(slice+1)+j,i*(slice+1)+j,i*(slice+1)+_j));
			m->addFace(Face(_i*(slice+1)+_j,_i*(slice+1)+j,i*(slice+1)+_j));
		}
	}
	return m;
}

Mesh* CreateCylinder(float r1,float r2, float length,float stack, float slice, float angle)
{
	float dr = (r2-r1)/slice;
	float _angle = length == 0.0f ? M_PI_2 : -atan((r2-r1)/length);
	Mesh* m = new Mesh();
	m->setColor(0xffffffff);


	for(int i = 0; i <= stack;i++)
	{
		for(int j = 0; j <= slice; j++)
		{
			glm::vec3 normal;
			normal = glm::vec3(cos(i*angle/stack)*cos(_angle),sin(i*angle/stack)*cos(_angle),sin(_angle));
			glm::normalize(normal);
			m->addVertex(new Vertex((dr*j + r1)*cos(i*angle/stack),(dr*j + r1)*sin(i*angle/stack), length/slice*j,i/stack,1.0f-j/slice,normal));
		}
	}

	for(int i = 0; i < stack;i++)
	{
		for(int j = 0; j < slice; j++)
		{
			/*(i,j+1) _ _ (i+1,j+1)
			         |  /|
			         | / |
			    (i,j)|/  |(i+1,j)
			*/
			int _i = SELECT(i+1,stack+1), _j = SELECT(j+1,(slice+1));
			m->addFace(Face(i*(slice+1)+j,_i*(slice+1)+j,i*(slice+1)+_j));
			m->addFace(Face(_i*(slice+1)+j,_i*(slice+1)+_j,i*(slice+1)+_j));
		}
	}
	return m;
}

Mesh* CreateDisk(float r,float stack,float angle)
{
	Mesh* m = new Mesh();
	//stack++;
	

	for(int i = 0; i < stack; i++)
		m->addVertex( new Vertex(r*cos(i*angle/stack),r*sin(i*angle/stack), 0.0f,(i)/stack,1.0f,glm::vec3(0,0,1.0f)));
	m->addVertex( new Vertex(0,0, 0.0f,(0)/stack,1.0f,glm::vec3(0,0,1.0f)));
	for(int i = 0; i < stack;i++)
	{
			/*          (0,0)
			            /|
			           / |
	  (cos(i),sin(i)) /__|(cos(i+1),sin(i+1))
			*/
			int _i = SELECT(i+1,stack);
			m->addFace(Face(i,_i,stack));
	}
	return m;
}


/*Mesh* CreateTorus(float r1, float r2, float side, float ring, float angle1, float angle2, float angle1_beg)
{
	return NULL;
}*/

BoneMesh* CreateBone(float size, Bone* b)
{
	BoneMesh* m = new BoneMesh(b);

	m->addVertex(new Vertex(0,0,0));
	m->addVertex(new Vertex(0.01,0.01,size*0.3));
	m->addVertex(new Vertex(0.01,-0.01,size*0.3));
	m->addVertex(new Vertex(-0.01,-0.01,size*0.3));
	m->addVertex(new Vertex(-0.01,0.01,size*0.3));
	m->addVertex(new Vertex(0,0,size));


	m->addFace(Face(0,1,2));
	m->addFace(Face(0,2,3));
	m->addFace(Face(0,3,4));
	m->addFace(Face(0,4,1));

	m->addFace(Face(5,1,2));
	m->addFace(Face(5,2,3));
	m->addFace(Face(5,3,4));
	m->addFace(Face(5,4,1));

	return m;
}

Mesh* CreateBox(float x, float y, float z)
{
	x /=2;y /=2;z /=2;
	Mesh * m = new Mesh();


	m->addVertex(new Vertex(-x,-y,-z,0,0,glm::vec3(0,0,-1)));
	m->addVertex(new Vertex(x,-y,-z,1,0,glm::vec3(0,0,-1)));
	m->addVertex(new Vertex(x,y,-z,1,1,glm::vec3(0,0,-1)));
	m->addVertex(new Vertex(-x,y,-z,0,1,glm::vec3(0,0,-1)));

	m->addVertex(new Vertex(-x,-y,z,0,0,glm::vec3(0,0,1)));
	m->addVertex(new Vertex(x,-y,z,1,0,glm::vec3(0,0,1)));
	m->addVertex(new Vertex(x,y,z,1,1,glm::vec3(0,0,1)));
	m->addVertex(new Vertex(-x,y,z,0,1,glm::vec3(0,0,1)));

	m->addVertex(new Vertex(-x,-y,-z,0,0,glm::vec3(0,-1,0)));
	m->addVertex(new Vertex(x,-y,-z,1,0,glm::vec3(0,-1,0)));
	m->addVertex(new Vertex(x,-y,z,1,1,glm::vec3(0,-1,0)));
	m->addVertex(new Vertex(-x,-y,z,0,1,glm::vec3(0,-1,0)));

	m->addVertex(new Vertex(-x,y,-z,0,0,glm::vec3(0,1,0)));
	m->addVertex(new Vertex(x,y,-z,1,0,glm::vec3(0,1,0)));
	m->addVertex(new Vertex(x,y,z,1,1,glm::vec3(0,1,0)));
	m->addVertex(new Vertex(-x,y,z,0,1,glm::vec3(0,1,0)));

	m->addVertex(new Vertex(-x,-y,-z,0,0,glm::vec3(-1,0,0)));
	m->addVertex(new Vertex(-x,y,-z,1,0,glm::vec3(-1,0,0)));
	m->addVertex(new Vertex(-x,y,z,1,1,glm::vec3(-1,0,0)));
	m->addVertex(new Vertex(-x,-y,z,0,1,glm::vec3(-1,0,0)));

	m->addVertex(new Vertex(x,-y,-z,0,0,glm::vec3(1,0,0)));
	m->addVertex(new Vertex(x,y,-z,1,0,glm::vec3(1,0,0)));
	m->addVertex(new Vertex(x,y,z,1,1,glm::vec3(1,0,0)));
	m->addVertex(new Vertex(x,-y,z,0,1,glm::vec3(1,0,0)));


	// FACE Z+
	m->addFace(Face(0,1,2));
	m->addFace(Face(0,2,3));

	// FACE Z-
	m->addFace(Face(4,5,6));
	m->addFace(Face(4,6,7));

	// FACE X+
	m->addFace(Face(8,9,10));
	m->addFace(Face(8,10,11));

	// FACE X-
	m->addFace(Face(12,13,14));
	m->addFace(Face(12,14,15));

	// FACE Y+
	m->addFace(Face(16,17,18));
	m->addFace(Face(16,18,19));

	// FACE Y-
	m->addFace(Face(20,21,22));
	m->addFace(Face(20,22,23));

	return m;
}