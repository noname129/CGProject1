#include "stdafx.h"
#include "GDrawable.h"

#ifndef	__GPOLYHEDRON_H__
#define __GPOLYHEDRON_H__

namespace Glory {

class GPolyhedron : public GDrawable {
private:
	unsigned int vao;
	unsigned int vertexVbo;
	unsigned int colorVbo;
	unsigned int ebo;
	bool upToDate;

protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec4> colors;
	std::vector<GLuint> indices;

public:
	GPolyhedron();
	~GPolyhedron();

	void AddVertices(std::initializer_list<glm::vec3> vertices);
	void AddIndices(std::initializer_list<GLuint> colors);
	void AddColors(std::initializer_list<glm::vec4> colors);

	void SetVao();

	void Update(float deltaTime);
	void Render();
};

}

#endif