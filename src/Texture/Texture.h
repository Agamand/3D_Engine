



#ifndef TEXTURE_H
#define TEXTURE_H

#include <time.h>
#include "../Util/util.h"
#include <vector>
#include <assert.h>
class Texture
{
public:
	Texture();
	Texture(String filename);


	int getTextureID() { return textureID; }
	String getName() { return filename;}
	void load();
	void unLoad();

private:
	int textureID;
	String filename;
	String name;
	time_t ttl;
	int use;
	bool isLoad;
};

class TextureMgr
{
public:
	TextureMgr();

	Texture* getTexture(String filepath);
	
	void load(Texture*);
	void loadAll();

	void unload(Texture*);
	void unloadAll();

	static TextureMgr* getTextureMgr()
	{
		if(!textmgr)
			textmgr = new TextureMgr();
		
		assert(textmgr != NULL);
		return textmgr;
	}
private:
	static TextureMgr* textmgr; //Singleton
	std::vector<Texture*> texture_list;
};

#endif TEXTURE_H