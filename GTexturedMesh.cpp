#include "stdafx.h"
#include "GTexturedMesh.h"
#include "GTextureManager.h"

namespace Glory {

GTexturedMesh::GTexturedMesh() {
	indices.reserve(3);
	upToDate = false;

}

GTexturedMesh::~GTexturedMesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &texCoordVbo);
	glDeleteBuffers(1, &normalVbo);
	glDeleteBuffers(1, &vertexVbo);
}

void GTexturedMesh::Update(float deltaTime) {
	GDrawable::Update(deltaTime);
}

void GTexturedMesh::AddVertices(std::initializer_list<glm::vec3> vertices,
	std::initializer_list<glm::vec3> normals, std::initializer_list<glm::vec2> texCoords) {
	if (vertices.size() != normals.size() || normals.size() != texCoords.size()) {
		printf("GTexturedMesh::AddVertices - Size are not matched\n");
		return;
	}

	this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
	this->normals.insert(this->normals.end(), normals.begin(), normals.end());
	this->texCoords.insert(this->texCoords.end(), texCoords.begin(), texCoords.end());
	upToDate = false;
}

void GTexturedMesh::AddIndices(std::initializer_list<GLuint> indices) {
	this->indices.insert(this->indices.end(), indices.begin(), indices.end());
	upToDate = false;
}

void GTexturedMesh::SetVao() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vertexVbo);
	glGenBuffers(1, &normalVbo);
	glGenBuffers(1, &texCoordVbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
	glBufferData(GL_ARRAY_BUFFER, this->texCoords.size() * sizeof(glm::vec2), &texCoords.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	upToDate = true;
}

void GTexturedMesh::Render() {
	GDrawable::Render();

	if (!upToDate) {
		SetVao();
	}

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(vao);
	auto texMgr = GTextureManager::Instance();

	glBindTexture(GL_TEXTURE_2D, texMgr->Load(path));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

}