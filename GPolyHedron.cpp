#include "stdafx.h"
#include "GPolyhedron.h"

namespace Glory {

GPolyhedron::GPolyhedron() {
	indices.reserve(3);
	upToDate = false;

}

GPolyhedron::~GPolyhedron() {
//	glDeleteVertexArrays(1, &vao);
//	glDeleteBuffers(1, &colorVbo);
//	glDeleteBuffers(1, &vertexVbo);
}

void GPolyhedron::Update(float deltaTime) {
	GDrawable::Update(deltaTime);
}

void GPolyhedron::AddVertices(std::initializer_list<glm::vec3> vertices) {
	this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
	upToDate = false;
}

void GPolyhedron::AddIndices(std::initializer_list<GLuint> indices) {
	this->indices.insert(this->indices.end(), indices.begin(), indices.end());
	upToDate = false;
}

void GPolyhedron::AddColors(std::initializer_list<glm::vec4> colors) {
	this->colors.insert(this->colors.end(), colors.begin(), colors.end());
	upToDate = false;
}

void GPolyhedron::SetVao() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vertexVbo);
	glGenBuffers(1, &colorVbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec4), 0, GL_STATIC_DRAW);
	int sizeDiff = vertices.size() - colors.size();
	if (sizeDiff > 0) {
		glm::vec4 defaultColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 *defaultColors = new glm::vec4[sizeDiff];
		std::fill_n(defaultColors, sizeDiff, defaultColor);

		glBufferSubData(GL_ARRAY_BUFFER, 0, this->colors.size() * sizeof(glm::vec4), &colors.front());
		glBufferSubData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(glm::vec4), sizeDiff * sizeof(glm::vec4), defaultColors);
		delete[] defaultColors;
	} else {
		glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertices.size() * sizeof(glm::vec4), &colors.front());
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	upToDate = true;
}

void GPolyhedron::Render() {
	GDrawable::Render();

	if (!upToDate) {
		SetVao();
	}

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

}