


#ifndef SHADER_H
#define SHADER_H
#include "../opengl.h"
#include "../Util/util.h"
#include <vector>
#include <map>

/*
typedef struct _shader
{
	GLuint program_id,vertex,frag;
}Shader;*/

struct UniformVar
{	
	UniformVar()
	{
		loc = -1;
	}
	String name;
	uint32 type;
	int32 loc;
	uint32 size;
};

struct AttributVar
{
	AttributVar()
	{
		loc = -1;
	}
	String name;
	uint32 type;
	int32 loc;
	uint32 size;
};

class Shader
{
public:
	Shader(String vertex, String frag, String geom = String(""));
	~Shader();
	GLuint getProgramId() { return programId;}
	bool isReady() {return ready;}
	void SetupUniform();
	void SetupVertexAttribut();
	UniformVar getUniform(String varname);
	AttributVar getAttribut(String varname);
	void use(bool use = true) 
	{ 
		if(use) 
			glUseProgram(programId);
		else
			glUseProgram(0);
	}

private:
	char* LoadSource(const char *filename);
	GLuint LoadShader(GLenum type, const char *filename);
	GLuint programId;
	GLuint vertexId;
	GLuint geomId;
	GLuint fragId;

	bool ready;
	String programName;

	std::map<String,UniformVar> unif_var;
	std::map<String,AttributVar> attribut_var;
//	std::vector<UniformVar> unif_var;
//	std::vector<AttributVar> attrib_var;
};

#endif