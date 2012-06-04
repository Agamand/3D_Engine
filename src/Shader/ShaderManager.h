#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H


//#include "Shader.h"
#include <cstdio>
#include <assert.h>

class ShaderMgr
{
public:




	static ShaderMgr* getOrCreateShaderMgr()
	{
		if(!instance)
			instance = new ShaderMgr();

		assert(instance != NULL);
		return instance;
	}
private:
	ShaderMgr(void);
	~ShaderMgr(void);
	static ShaderMgr* instance; // Singleton 
};

#endif
