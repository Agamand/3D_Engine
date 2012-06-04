
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Shader.h"
#include <map>
#include <iostream>
#include <fstream>
 
using namespace std;

char* Shader::LoadSource(const char *filename)
{
    char *src = NULL;
	uint64 size;
	ifstream file(filename, ios::in);
    
	if(!file || file.fail())
    {
        fprintf(stderr, "impossible d'ouvrir le fichier '%s'\n", filename);
        return NULL;
    }
	file.seekg(0,ios_base::end);
	size= file.tellg();
    file.seekg(0,ios_base::beg);
    src = new char[size+1];//(char*)malloc(size+1);
    if(src == NULL)
    {
		file.close();
        fprintf(stderr, "erreur d'allocation de memoire!\n");
        return NULL;
    }
    
	//fread(src,size,1,fp);    
	/*String line;
	int index = 0;
	while(getline(file,line))
	{
		if(index >= size)
			break;

		memcpy(src+index,line.c_str(),line.length());
		
		index += line.length();
		src[index] = '\n';
		index++;
	}*/
	file.read(src,size);
    src[size] = '\0';
    
	file.close();
    
    return src;
}


GLuint Shader::LoadShader(GLenum type, const char *filename)
{
    GLuint shader = 0;
    GLsizei logsize = 0;
    GLint compile_status = GL_TRUE;
    char *log = NULL;
    char *src = NULL;
    
    /* creation d'un shader de sommet */
    shader = glCreateShader(type);
    if(shader == 0)
    {
        fprintf(stderr, "impossible de creer le shader\n");
        return 0;
    }
    
    /* chargement du code source */
    src = LoadSource(filename);
    if(src == NULL)
    {
        /* theoriquement, la fonction LoadSource a deja affiche un message
           d'erreur, nous nous contenterons de supprimer notre shader
           et de retourner 0 */
        
        glDeleteShader(shader);
        return 0;

    }
    
    /* assignation du code source */
    glShaderSource(shader, 1, (const GLchar**)&src, NULL);
    
    /* compilation du shader */
    glCompileShader(shader);
    
    /* liberation de la memoire du code source */
    delete src;//free(src);
    src = NULL;
    
    /* verification du succes de la compilation */
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE)
    {
        /* erreur a la compilation recuperation du log d'erreur */
        
        /* on recupere la taille du message d'erreur */
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
        
        /* on alloue un espace memoire dans lequel OpenGL ecrira le message */
        log = new char[logsize+1];//(char*)malloc(logsize + 1);
        if(log == NULL)
        {
            fprintf(stderr, "impossible d'allouer de la memoire !\n");
            return 0;
        }
        /* initialisation du contenu */
        memset(log, '\0', logsize + 1);
        
        glGetShaderInfoLog(shader, logsize, &logsize, log);
        fprintf(stderr, "impossible de compiler le shader '%s' :\n%s",
                filename, log);
       
        delete log;
        glDeleteShader(shader);
        
        return 0;
    }
    
    return shader;
}

Shader::Shader(String vertex, String frag, String geom)
{
	GLuint vertex_id = 0,frag_id = 0,geom_id = 0,program_id;
	GLint link = 0;
	GLint tailleErreur = 0;
	char *erreur = NULL;

	ready = false;

	if(vertex.empty() && frag.empty() && geom.empty())
		return;

	int beg = vertex.find_last_of("/") > 0 ? vertex.find_last_of("/") : 0;
	int end = vertex.find_last_of(".") > 0 ? vertex.find_last_of(".") : vertex.size()-1;
	programName = vertex.substr(beg+1,end);

	if(!vertex.empty())
		vertex_id = LoadShader(GL_VERTEX_SHADER,vertex.c_str());

	if(!geom.empty())
		geom_id = LoadShader(GL_GEOMETRY_SHADER_EXT,geom.c_str());

	if(!frag.empty())
		frag_id = LoadShader(GL_FRAGMENT_SHADER,frag.c_str());


	program_id = glCreateProgram();
	fragId = frag_id;
	geomId = geom_id;
	vertexId = vertex_id;
	programId = program_id;
	ready = false;

	if(vertex_id)
		glAttachShader(program_id, vertex_id);
	if(geom_id)
		glAttachShader(program_id, geom_id);
	if(frag_id)
		glAttachShader(program_id, frag_id);
	
	glLinkProgram(program_id);

	glGetProgramiv(program_id, GL_LINK_STATUS, &link);

	if(link != GL_TRUE)
	{

		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &tailleErreur);

		erreur = new char[tailleErreur + 1];

		glGetProgramInfoLog(program_id, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';

		printf("Erreur lors du link du program : %s",erreur);

		delete erreur;
		return;
	}
	ready = true;
	SetupUniform();
	SetupVertexAttribut();
}

void Shader::SetupUniform()
{
	int32 n = 0;
	glGetProgramiv( programId, GL_ACTIVE_UNIFORMS, &n );

	// read all active uniforms
	for( int i = 0 ; i < n ; i++ )
	{
		// read out info
		UniformVar _var;
		char name[30] = "\0";
		size_t length = 0;
		_var.size = 0;
		_var.type = 0;
		glGetActiveUniform( programId, i, sizeof(name), (GLsizei*)&length, (GLint*)&_var.size, &_var.type, name );
		_var.loc = glGetUniformLocation( programId, name );
		_var.name = String(name);
		unif_var[_var.name] = _var;
	}

}

void Shader::SetupVertexAttribut()
{
	int32 n = 0;
	glGetProgramiv( programId, GL_ACTIVE_ATTRIBUTES, &n );

	// read all active uniforms
	for( int i = 0 ; i < n ; i++ )
	{
		// read out info
		AttributVar _var;
		char name[30] = "\0";
		size_t length = 0;
		_var.size = 0;
		_var.type = 0;
		glGetActiveAttrib( programId, i, sizeof(name), (GLsizei*)&length, (GLint*)&_var.size, &_var.type, name );
		_var.loc = glGetAttribLocation( programId, name );
		_var.name = String(name);
		attribut_var[_var.name] = _var;
	}

}

UniformVar Shader::getUniform(String varname)
{
	return unif_var[varname];
}
AttributVar Shader::getAttribut(String varname)
{
	return attribut_var[varname];
}

Shader::~Shader()
{

	if(vertexId)
		glDeleteShader(vertexId);

	if(fragId)
		glDeleteShader(fragId);

	if(programId)
		glDeleteProgram(programId);
}

void initShader()
{
	glewInit();
}