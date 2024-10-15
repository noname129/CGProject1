#include "stdafx.h"

#ifndef __GTEXTUREMANAGER_H__
#define	__GTEXTUREMANAGER_H__

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Glory {

class GTextureManager {
private:
	std::map<std::string, GLuint> Textures;

	GLuint LoadTexture(std::string path, GLint wrapParam = GL_CLAMP);

	GTextureManager();
public:
	static GTextureManager* Instance();

	GLuint Load(std::string path, GLint wrapParam = GL_CLAMP);

	void Unload(std::string path);
	void UnloadAll();
};

}

#endif