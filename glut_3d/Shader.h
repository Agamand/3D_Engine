#include <gl\glew.h>
#include <glut.h>


#ifndef SHADER_H
#define SHADER_H

char* LoadSource(const char *filename);
GLuint LoadShader(GLenum type, const char *filename);

#endif