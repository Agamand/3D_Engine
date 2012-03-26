#include "Loader/BMPloader.h"
#include "Loader/PNGloader.h"
#include "Texture.h"
#include <glut.h>

Texture::Texture()
{
	filename = "";
	isLoad = false;
	textureID = 0;
	use = 0;
	ttl = 0;
}
Texture::Texture(String filename)
{
	int i;


	this->filename = filename;
	isLoad = false;
	textureID = 0;
	for(i = filename.size()-1; i >= 0; i--)
	{
		if(filename.at(i) == '/')
		{
			name = filename.substr(i+1);
		}else if(!i)
		{
			name = filename;
		}
	}
	use = 0;
	ttl = 0;
	load();
}

// FUNCTION

void Texture::load()
{
	GLuint texture;
	String ext = "";
	int i;

	if(filename.empty())
		textureID = 0;

	for(i = filename.size()-1; i >= 0; i--)
	{
		if(filename.at(i) == '.')
		{
			ext = filename.substr(i+1);
			break;
		}
	}

	if(ext.empty())
		textureID = 0;

	if(!ext.compare("png"))
		textureID = 0; //loadPNGTexture
	else if (!ext.compare("bmp"))
		textureID = loadBMPTexture(filename.c_str());
	else if(!ext.compare("jpg"))
		textureID = 0; //loadJPGTexture

	if(textureID)
		isLoad = true;

}

void Texture::unLoad()
{
	glDeleteTextures(1,(GLuint*)&textureID);
}