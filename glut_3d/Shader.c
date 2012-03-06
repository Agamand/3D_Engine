#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Shader.h"


char* LoadSource(const char *filename)
{
    char *src = NULL;
    FILE *fp = NULL;
    long size;
    
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        fprintf(stderr, "impossible d'ouvrir le fichier '%s'\n", filename);
        return NULL;
    }
    
    fseek(fp, 0, SEEK_END);
    size = ftell(fp); 
    rewind(fp);
    
    src = (char*)malloc(size+1);
    if(src == NULL)
    {
        fclose(fp);
        fprintf(stderr, "erreur d'allocation de memoire!\n");
        return NULL;
    }
    
	fread(src,size,1,fp);    
    src[size] = '\0';
    
    fclose(fp);
    
    return src;
}


GLuint LoadShader(GLenum type, const char *filename)
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
    free(src);
    src = NULL;
    
    /* verification du succes de la compilation */
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE)
    {
        /* erreur a la compilation recuperation du log d'erreur */
        
        /* on recupere la taille du message d'erreur */
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
        
        /* on alloue un espace memoire dans lequel OpenGL ecrira le message */
        log = malloc(logsize + 1);
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
       
        free(log);
        glDeleteShader(shader);
        
        return 0;
    }
    
    return shader;
}

Shader* LoadProgram(const char *vertex, const char *frag)
{
	GLuint vertex_id,frag_id,program_id;
	GLint link = 0;
	GLint tailleErreur = 0;
	char *erreur = NULL;
	Shader* sh = NULL;

	vertex_id = LoadShader(GL_VERTEX_SHADER,vertex);
	frag_id = LoadShader(GL_FRAGMENT_SHADER,frag);


	program_id = glCreateProgram();
	sh = (Shader*)malloc(sizeof(Shader));
	sh->frag = frag_id;
	sh->vertex = vertex_id;
	sh->program_id = program_id;
	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, frag_id);

	glLinkProgram(program_id);

	glGetProgramiv(program_id, GL_LINK_STATUS, &link);

	if(link != GL_TRUE)
	{

		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &tailleErreur);

		erreur = (char*)malloc(sizeof(char)*(tailleErreur + 1));

		glGetProgramInfoLog(program_id, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';

		printf("Erreur lors du link du program : %s",erreur);

		free(erreur);
		DeleteProgram(sh);

		return NULL;
	}


	return sh;
}

void DeleteProgram(Shader*sh)
{

	if(!sh)
		return;
	if(sh->vertex)
		glDeleteShader(sh->vertex);

	if(sh->frag)
		glDeleteShader(sh->frag);

	if(sh->program_id)
		glDeleteProgram(sh->program_id);

	free(sh);
}