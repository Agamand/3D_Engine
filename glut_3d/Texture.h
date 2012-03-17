



#ifndef TEXTURE_H
#define TEXTURE_H

#include <time.h>


typedef struct _texture Texture;

struct _texture
{
	int textureID;
	char* filename;
	char * textureName;
	time_t timeToUnload;
	int use;
	char isLoad;
};

// CONSTRUCTOR / DECONSTRUCTOR
Texture * newTexture(Texture* t, const char * filename);
void deleteTexture(Texture* t);


// FUNCTION

void load(Texture * t);
void unLoad(Texture * t);



#endif TEXTURE_H