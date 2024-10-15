#include "stdafx.h"

#ifndef __GCANVAS_H__
#define	__GCANVAS_H__

#include "shader.h"

namespace Glory {

class GCanvas {
private:
	GLuint VAO, VBO;
	glm::mat4 projection;

public:
	GCanvas();

	void Draw(std::string path, int x, int y, int width, int height, Shader* shader = &defaultShader);
	void Draw(std::string path, std::initializer_list<glm::vec2> pos,
		std::initializer_list<glm::vec2> texCoords, Shader* shader = &defaultShader);

	static Shader defaultShader;
};

}

#endif