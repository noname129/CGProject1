#include "stdafx.h"
#include "Coin.h"

const int Coin::edgeCount = 32;

Coin::Coin() {
	vertices.reserve(2 * edgeCount + 2);
	colors.reserve(2 * edgeCount + 2);
	indices.reserve(3 * 2 * edgeCount * 4);

	float dTheta = 2 * glm::pi<float>() / edgeCount;

	for (int i = 0; i < edgeCount; ++i) {
		vertices.emplace_back(glm::vec3(0.5f * glm::cos(i * dTheta), 0.5f * glm::sin(i * dTheta), -0.05f));
		vertices.emplace_back(glm::vec3(0.5f * glm::cos(i * dTheta), 0.5f * glm::sin(i * dTheta), +0.05f));
		indices.insert(indices.end(),
			{
				2 * edgeCount, (GLuint)((2 * i) % (2 * edgeCount)), (GLuint)((2 * i + 2) % (2 * edgeCount)),
				(GLuint)((2 * i) % (2 * edgeCount)), (GLuint)((2 * i + 2) % (2 * edgeCount)), (GLuint)((2 * i + 1) % (2 * edgeCount)),
				(GLuint)((2 * i + 2) % (2 * edgeCount)), (GLuint)((2 * i + 1) % (2 * edgeCount)), (GLuint)((2 * i + 3) % (2 * edgeCount)),
				2 * edgeCount + 1, (GLuint)((2 * i + 1) % (2 * edgeCount)), (GLuint)((2 * i + 3) % (2 * edgeCount))
			}
		);
	}

	vertices.emplace_back(glm::vec3(0.0f, 0.0f, -0.05f));
	vertices.emplace_back(glm::vec3(0.0f, 0.0f, +0.05f));

	colors.insert(colors.end(), 2 * edgeCount + 2, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	SetVao();
}

void Coin::Update(float deltaTime) {
	GObject::Update(deltaTime);
	transform.rotation.y += 180.0f * deltaTime;
}