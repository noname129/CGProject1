#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"

Player::Player() {
	onGround = true;

	camera = new GCamera();
	camera->transform.position = glm::vec3(12.0f, 6.0f, 10.0f);
	camera->transform.rotation = glm::vec3(-30.0f, 45.0f, 30.0f);
	AddChild(camera);

	cube = new GMonoPoly();

	cube->AddVertices({ { -1,-1,-1 },{ -1,-1,1 },{ -1,1,-1 },{ -1,1,1 },{ 1,-1,-1 },{ 1,-1,1 },{ 1,1,-1 },{ 1,1,1 } });
	cube->AddIndices(
		{
			0,1,2,
			1,2,3,
			2,3,7,
			2,6,7,
			6,7,4,
			4,5,7,
			0,1,5,
			0,5,4,
			3,7,1,
			1,7,5,
			2,6,0,
			0,6,4,
		}
	);
	cube->color = glm::vec4(0.8f, 0.4f, 0.01f, 1.0f);
	cube->transform.position.y = 0.2f;
	cube->SetVao();
	AddChild(cube);

	for (int i = 0; i < 2; ++i) {
		wheel[i] = new GMonoPoly();

		float dTheta = 2 * glm::pi<float>() / 18;

		for (int j = -1; j <= 1; j = j + 2) {
			float x = j * 0.1f;
			for (int k = 0; k < 18; ++k) {
				wheel[i]->AddVertices({ { x, 0.2f * glm::sin(k * dTheta), 0.2f * glm::cos(k * dTheta) }, //3n+0, 3n+54
				{ x, 0.8f * glm::sin(k * dTheta), 0.8f * glm::cos(k * dTheta) } , //3n+1, 3n+55
				{ x, 0.9f * glm::sin(k * dTheta), 0.9f * glm::cos(k * dTheta) } }); //3n+2, 3n+56
			}
		}

		//inner circle
		for (unsigned int j = 0; j < 17; ++j) {
			wheel[i]->AddIndices({ 0, 3 * j, 3 * j + 3 });
			wheel[i]->AddIndices({ 54, 3 * j + 54, 3 * j + 57 });
			wheel[i]->AddIndices({ 3 * j, 3 * j + 54, 3 * j + 57, 3 * j, 3 * j + 57, 3 * j + 3 });
		}
		wheel[i]->AddIndices({ 51, 105, 54, 51, 54, 0 });

		wheel[i]->color = glm::vec4(0.5f, 0, 0, 1.0f);
		wheel[i]->SetVao();
		cube->AddChild(wheel[i]);

		//outer circle
		for (unsigned int j = 0; j < 17; ++j) {
			wheel[i]->AddIndices({ 3 * j + 1, 3 * j + 55, 3 * j + 58, 3 * j + 1, 3 * j + 58, 3 * j + 4 });
			wheel[i]->AddIndices({ 3 * j + 2, 3 * j + 56, 3 * j + 59, 3 * j + 2, 3 * j + 59, 3 * j + 5 });
		}
		wheel[i]->AddIndices({ 52, 106, 55, 52, 55, 1 });
		wheel[i]->AddIndices({ 53, 107, 56, 53, 56, 2 });

		for (unsigned int j = 0; j < 17; ++j) {
			wheel[i]->AddIndices({ 3 * j + 1, 3 * j + 2, 3 * j + 5, 3 * j + 1, 3 * j + 5, 3 * j + 4 });
			wheel[i]->AddIndices({ 3 * j + 55, 3 * j + 56, 3 * j + 59, 3 * j + 55, 3 * j + 59, 3 * j + 56 });
		}
		wheel[i]->AddIndices({ 52, 53, 2, 52, 2, 1 });
		wheel[i]->AddIndices({ 106, 107, 56, 106, 56, 55 });

		for (unsigned j = 0; j < 18; j = j + 2) {
			wheel[i]->AddIndices({ 3 * j, 3 * j + 1, 3 * j + 4, 3 * j, 3 * j + 4, 3 * j + 3 });
			wheel[i]->AddIndices({ 3 * j + 54, 3 * j + 55, 3 * j + 59, 3 * j + 54, 3 * j + 59, 3 * j + 57 });
			wheel[i]->AddIndices({ 3 * j, 3 * j + 54, 3 * j + 55, 3 * j, 3 * j + 55, 3 * j + 1 });
			wheel[i]->AddIndices({ 3 * j + 3, 3 * j + 57, 3 * j + 58, 3 * j + 3, 3 * j + 58, 3 * j + 4 });
		}

	}
	wheel[0]->transform.position = glm::vec3(-1.15f, -0.3f, 0);
	wheel[1]->transform.position = glm::vec3(1.15f, -0.3f, 0);
	wheel[0]->transform.scale.x = -1.0f;
}

void Player::Jump() {
	if (!onGround) {
		return;
	}
	transform.position.y = 1.2f * cube->transform.scale.x - 1.0f;
	jumpSpeed = 30.0f;
	onGround = false;
}

void Player::Update(float deltaTime) {
	GameScene *gameScene = (GameScene *)scene;

	if (gameScene->state == PLAYING) {
		if (!onGround) {
			transform.position.y += jumpSpeed * deltaTime;
			jumpSpeed -= 65.0f * deltaTime;

			if (transform.position.y < 1.2f * cube->transform.scale.x - 1.0f) {
				transform.position.y = 1.2f * cube->transform.scale.x - 1.0f;
				onGround = true;
			}
		} else {
			wheel[0]->transform.rotation.x -= zSpeed * 6.3f * deltaTime;
			wheel[1]->transform.rotation.x -= zSpeed * 6.3f * deltaTime;
		}
		transform.position.z -= zSpeed * deltaTime;
	}
}

void Player::Render() {
	cube->Render();
	wheel[0]->Render();
	wheel[1]->Render();
}