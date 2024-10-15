#include "stdafx.h"
#include "GDrawable.h"

#ifndef	__GTEXTUREDMESH_H__
#define __GTEXTUREDMESH_H__

namespace Glory {

class GTexturedMesh : public GDrawable {
private:
	unsigned int vao;
	unsigned int vertexVbo;
	unsigned int normalVbo;
	unsigned int texCoordVbo;
	unsigned int ebo;
	bool upToDate;

protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<GLuint> indices;

public:
	std::string path;

	GTexturedMesh();
	~GTexturedMesh();

	void AddVertices(std::initializer_list<glm::vec3> vertices, 
		std::initializer_list<glm::vec3> normals, std::initializer_list<glm::vec2> texCoords);
	void AddIndices(std::initializer_list<GLuint> indices);

	void SetVao();

	void Update(float deltaTime);
	void Render();
};

}

#endif