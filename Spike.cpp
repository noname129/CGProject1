#include "stdafx.h"
#include "Spike.h"
#include "GameScene.h"

Spike::Spike() {
	AddVertices(
		{
			{-0.5f, -0.5f, -0.5f},
			{0.5f, 0.5f, -0.5f},
			{0.5f, -0.5f, 0.5f},
			{-0.5f, 0.5f, 0.5f}
		}
	);
	AddIndices(
		{
			0,1,2,
			1,3,2,
			0,2,3,
			0,1,3
		}
	);
	color = glm::vec4(0.8f, 0, 0, 1.0f);
}

void Spike::Update(float deltaTime) {
	GObject::Update(deltaTime);

	transform.rotation.y += 120.0f * deltaTime;
	transform.rotation.x += 60.0f * deltaTime;

	float distance = glm::distance(player->transform.position, transform.position);
	GameScene *gameScene = (GameScene *)scene;
	if (gameScene->state == PLAYING && distance <= 0.5f + 0.204) {
		gameScene->GameOver();
	}
}