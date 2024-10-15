#include "stdafx.h"
#include "GTextureManager.h"

namespace Glory {

GTextureManager::GTextureManager() : Textures() {

}

GTextureManager* GTextureManager::Instance() {
	static GTextureManager instance;
	return &instance;
}

GLuint GTextureManager::Load(std::string path, GLint wrapParam) {
	if (Textures.find(path) == Textures.end()) {
		Textures[path] = LoadTexture(path, wrapParam);
	}
	return Textures[path];
}

void GTextureManager::Unload(std::string path) {
	auto iter = Textures.find(path);
	if (iter != Textures.end()) {
		glDeleteTextures(1, &(iter->second));
		Textures.erase(iter);
	}
}

void GTextureManager::UnloadAll() {
	for (auto iter : Textures) {
		glDeleteTextures(1, &(iter.second));
	}
	Textures.clear();
}

GLuint GTextureManager::LoadTexture(std::string path, GLint wrapParam) {
	static GLuint id = 0;

	// Create texture ids.
	glGenTextures(1, &id);

	// All upcomming GL_TEXTURE_2D operations now on "texture" object
	glBindTexture(GL_TEXTURE_2D, id);

	// Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParam);

	// Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *image = stbi_load(path.data(), &width, &height, &nrChannels, 0);
	if (!image) {
		printf("texture %s loading error ... \n", path.data());
	} else printf("texture %s loaded\n", path.data());

	GLenum format;
	if (nrChannels == 1) format = GL_RED;
	else if (nrChannels == 3) format = GL_RGB;
	else if (nrChannels == 4) format = GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	return id++;
}

}