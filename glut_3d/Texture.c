#include "BMPloader.h"
#include "PNGloader.h"
#include "Texture.h"





// CONSTRUCTOR / DECONSTRUCTOR
Texture * newTexture(Texture* t,char * filename)
{
	int i;
	if(!t)
		t = (Texture*)malloc(sizeof(Texture));

	t->filename = filename;
	t->isLoad = 0;
	t->textureID = 0;
	for(i = strlen(filename); i >= 0; i--)
	{
		if(filename[i] == '/')
		{
			t->textureName = (char*)malloc(sizeof(char)*(strlen(filename+i+1)+1));
			strcpy(t->textureName,filename+i+1);
		}else if(!i)
		{
			t->textureName = (char*)malloc(sizeof(char)*(strlen(filename+i)+1));
			strcpy(t->textureName,filename+i);
		}
	}
	t->use = 0;
	t->timeToUnload = 0;
	return t;
}

void deleteTexture(Texture* t)
{
	if(t->textureName)
		free(t->textureName);
	free(t);
}


// FUNCTION

void load(Texture * t)
{
	GLuint texture;
	char *ext = NULL;
	int i;

	if(!t->filename)
		t->textureID = 0;

	for(i = strlen(t->filename)-1; i >= 0; i--)
	{
		if(t->filename[i] == '.')
		{
			ext = t->filename+i+1;
			break;
		}
	}

	if(!ext)
		t->textureID = 0;

	if(!(strcmp(ext,"png")))
		t->textureID = 0; //loadPNGTexture
	else if (!(strcmp(ext,"bmp")))
		t->textureID = loadBMPTexture(t->filename);
	else if(!(strcmp(ext,"jpg")))
		t->textureID = 0; //loadJPGTexture

	if(t->textureID)
		t->isLoad = 1;

}


void unLoad(Texture * t)
{
	glDeleteTextures(1,&t->textureID);
}