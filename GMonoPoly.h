#include "stdafx.h"

#ifndef __GMONOPOLY_H__
#define	__GMONOPOLY_H__

#include "GDrawable.h"

namespace Glory {

class GMonoPoly : public GDrawable {
private:
	unsigned int vao;
	unsigned int vertexVbo;
	unsigned int ebo;
	bool upToDate;

protected:
	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;

public:
	glm::vec4 color;

	GMonoPoly();
	~GMonoPoly();

	void AddVertices(std::initializer_list<glm::vec3> vertices);
	void AddIndices(std::initializer_list<GLuint> colors);

	void SetVao();

	void Update(float deltaTime);
	void Render();

	static Shader monotoneShader;
};

}

#endif