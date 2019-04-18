#include "stdafx.h"
#include "GMonoPoly.h"

namespace Glory {

Shader GMonoPoly::monotoneShader;

GMonoPoly::GMonoPoly() : GDrawable(&monotoneShader) {
	indices.reserve(3);
	upToDate = false;

}

GMonoPoly::~GMonoPoly() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vertexVbo);
}

void GMonoPoly::Update(float deltaTime) {
	GDrawable::Update(deltaTime);
}

void GMonoPoly::AddVertices(std::initializer_list<glm::vec3> vertices) {
	this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
	upToDate = false;
}

void GMonoPoly::AddIndices(std::initializer_list<GLuint> indices) {
	this->indices.insert(this->indices.end(), indices.begin(), indices.end());
	upToDate = false;
}

void GMonoPoly::SetVao() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vertexVbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	upToDate = true;
}

void GMonoPoly::Render() {
	GDrawable::Render();
	shader->setVec4("color", color);

	if (!upToDate) {
		SetVao();
	}

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

}