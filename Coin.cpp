#include "stdafx.h"
#include "Coin.h"

const int Coin::edgeCount = 32;

Coin::Coin() {
	vertices.reserve(2 * edgeCount + 2 + 9);
	colors.reserve(2 * edgeCount + 2 + 9);
	indices.reserve(3 * 2 * edgeCount * 4 + 24);

	float dTheta = 2 * glm::pi<float>() / edgeCount;

	for (int i = 0; i < edgeCount; ++i) {
		vertices.emplace_back(glm::vec3(0.5f * glm::cos(i * dTheta), 0.75f * glm::sin(i * dTheta), -0.05f));
		vertices.emplace_back(glm::vec3(0.5f * glm::cos(i * dTheta), 0.75f * glm::sin(i * dTheta), +0.05f));
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

	vertices.insert(vertices.end(), {
		{ 0.25f, 0.1f, 0.051f },
		{ 0.5f, 0.1f, 0.051f },
		{ 0.0f, 0.5f, 0.051f },
		{ 0.0f, 0.25f, 0.051f },
		{ -0.5f, 0.0f, 0.051f },
		{ -0.25f, 0.0f, 0.051f },
		{ 0.0f, -0.5f, 0.051f },
		{ 0.0f, -0.25f, 0.051f },
		{ 0.25f, -0.1f, 0.051f },
		{ 0.5f, -0.1f, 0.051f },
		});
	colors.insert(colors.end(), 9, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	GLuint offset = 2 * edgeCount + 2;
	indices.insert(indices.end(), {
		offset + 0, offset + 1, offset + 2,
		offset + 2, offset + 3, offset + 0,
		offset + 2, offset + 4, offset + 3,
		offset + 4, offset + 5, offset + 3,
		offset + 4, offset + 6, offset + 5,
		offset + 6, offset + 7, offset + 5,
		offset + 6, offset + 9, offset + 8,
		offset + 6, offset + 8, offset + 7,
	});

	SetVao();
}

void Coin::Update(float deltaTime) {
	GObject::Update(deltaTime);
	transform.rotation.y += 180.0f * deltaTime;
}