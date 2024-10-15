#include "stdafx.h"
#include "GCanvas.h"
#include "GApp.h"
#include "GTextureManager.h"
#include <glm/gtc/quaternion.hpp>

namespace Glory {

Shader GCanvas::defaultShader;

GCanvas::GCanvas() {
	auto app = GApp::Instance();
	
	projection = glm::ortho(0.0f, static_cast<GLfloat>(app->GetWindowWidth()), 0.0f,
		static_cast<GLfloat>(app->GetWindowHeight()));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GCanvas::Draw(std::string path, int x, int y, int width, int height, Shader* shader) {
	
	shader->use();
	shader->setMat4("projection", projection);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	GLfloat xpos = static_cast<float>(x);
	GLfloat ypos = static_cast<float>(y);

	GLfloat w = static_cast<float>(width);
	GLfloat h = static_cast<float>(height);
	// Update VBO
	GLfloat vertices[6][4] = {
		{ xpos,     ypos + h,   0.0f, 0.0f },
		{ xpos,     ypos,       0.0f, 1.0f },
		{ xpos + w, ypos,       1.0f, 1.0f },

		{ xpos,     ypos + h,   0.0f, 0.0f },
		{ xpos + w, ypos,       1.0f, 1.0f },
		{ xpos + w, ypos + h,   1.0f, 0.0f }
	};
	// Render glyph texture over quad
	glBindTexture(GL_TEXTURE_2D, GTextureManager::Instance()->Load(path));
	// Update content of VBO memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Render quad
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GCanvas::Draw(std::string path, std::initializer_list<glm::vec2> pos,
	std::initializer_list<glm::vec2> texCoords,	Shader* shader) {

	shader->use();
	shader->setMat4("projection", projection);

	auto posIter = pos.begin();
	auto tcIter = texCoords.begin();

	for (int i = 0, tCount = pos.size() / 3; i < tCount; ++i) {
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, GTextureManager::Instance()->Load(path));

		GLfloat vertices[3][4];

		for (int j = 0; j < 3; ++j) {
			vertices[j][0] = posIter->x;
			vertices[j][1] = posIter->y;
			vertices[j][2] = tcIter->x;
			vertices[j][3] = tcIter->y;
			++posIter;
			++tcIter;
		}

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


}
