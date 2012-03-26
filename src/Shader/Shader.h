


#ifndef SHADER_H
#define SHADER_H
//#include <gl\glew.h>
#include <glut.h>
typedef struct _shader
{
	GLuint program_id,vertex,frag;
}Shader;

char* LoadSource(const char *filename);
GLuint LoadShader(GLenum type, const char *filename);
Shader* LoadProgram(const char *vertex, const char *frag);
void DeleteProgram(Shader*);

#endif