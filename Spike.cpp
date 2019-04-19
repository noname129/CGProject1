#include "stdafx.h"
#include "Spike.h"
#include "GameScene.h"

Spike::Spike() {
	AddVertices(
		{
			{-0.75f, -0.75f, -0.75f},
			{0.75f, 0.75f, -0.75f},
			{0.75f, -0.75f, 0.75f},
			{-0.75f, 0.75f, 0.75f}
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

	GameScene *gameScene = (GameScene *)scene;
	float distance = glm::distance(gameScene->player->transform.position, transform.position);
	if (gameScene->state == PLAYING && distance <= 1.0f * gameScene->player->cube->transform.scale.x + 0.306f) {
		gameScene->GameOver();
	}
}