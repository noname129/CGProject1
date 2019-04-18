#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"

Player::Player() {
	onGround = true;

	camera = new GCamera();
	camera->transform.position = glm::vec3(12.0f, 6.0f, 10.0f);
	camera->transform.rotation = glm::vec3(-30.0f, 45.0f, 30.0f);
	AddChild(camera);

	AddVertices({ { -1,-1,-1 },{ -1,-1,1 },{ -1,1,-1 },{ -1,1,1 },{ 1,-1,-1 },{ 1,-1,1 },{ 1,1,-1 },{ 1,1,1 } });
	AddIndices(
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
	color = glm::vec4(1.0f, 0.9f, 0.93f, 1.0f);
	SetVao();

	for (int i = 0; i < 2; ++i) {
		wheel[i] = new GMonoPoly();

		float dTheta = 2 * glm::pi<float>() / 18;

		for (int j = -1; j <= 1; j = j + 2) {
			float x = j * 0.2f;
			wheel[i]->AddVertices({ {x, 0, 0} }); //0, 54
			for (int k = 0; k < 18; ++k) {
				wheel[i]->AddVertices({ { x, 0.2f * glm::sin(k * dTheta), 0.2f * glm::cos(k * dTheta) }, //3n+1, 3n+55
				{ x, 0.6f * glm::sin(k * dTheta), 0.6f * glm::cos(k * dTheta) } , //3n+2, 3n+56
				{ x, 0.7f * glm::sin(k * dTheta), 0.6f * glm::cos(k * dTheta) } }); //3n+3, 3n+57
			}
		}

		for (unsigned int j = 0; j < 18; ++j) {
			//inner circle
			wheel[i]->AddIndices(
				{
					0, (3 * j + 1) % 54, (3 * j + 4) % 54,
					54, (3 * j + 1) % 54 + 54, (3 * j + 4) % 54 + 54,
					(3 * j + 1) % 54, (3 * j + 1) % 54 + 54, (3 * j + 4) % 54 + 54,
					(3 * j + 1) % 54, (3 * j + 4) % 54 + 54, (3 * j + 4) % 54
				}
			);

			//outer circle
			//wheel[i]->AddIndices(
			//	{
			//		(3 * j + 2) % 54,(3 * j + 3) % 54,(3 * j + 5) % 54,
			//		(3 * j + 3) % 54,(3 * j + 5) % 54,(3 * j + 6) % 54,

			//		(3 * j + 2) % 54 + 54,(3 * j + 3) % 54 + 54,(3 * j + 5) % 54 + 54,
			//		(3 * j + 3) % 54 + 54,(3 * j + 5) % 54 + 54,(3 * j + 6) % 54 + 54,

			//		(3 * j + 2) % 54,(3 * j + 2) % 54 + 54,(3 * j + 5) % 54,
			//		(3 * j + 5) % 54,(3 * j + 2) % 54 + 54,(3 * j + 5) % 54,

			//		(3 * j + 3) % 54,(3 * j + 3) % 54 + 54,(3 * j + 3) % 54,
			//		(3 * j + 6) % 54,(3 * j + 6) % 54 + 54,(3 * j + 6) % 54,
			//	}
			//);
		}

		wheel[i]->color = glm::vec4(0.5f, 0, 0, 1.0f);
		wheel[i]->SetVao();
		AddChild(wheel[i]);
	}
	wheel[0]->transform.position = glm::vec3(-1.2f, -0.2f, 0);
	wheel[1]->transform.position = glm::vec3(1.2f, -0.2f, 0);
}

void Player::Jump() {
	if (!onGround) {
		return;
	}
	transform.position.y = 0.0f;
	jumpSpeed = 30.0f;
	onGround = false;
}

void Player::Update(float deltaTime) {
	GameScene *gameScene = (GameScene *)scene;

	if (gameScene->state == PLAYING) {
		if (!onGround) {
			transform.position.y += jumpSpeed * deltaTime;
			jumpSpeed -= 50.0f * deltaTime;

			if (transform.position.y <= 0.0f) {
				transform.position.y = 0.0f;
				onGround = true;
			}
		}
		transform.position.z -= zSpeed;
	}

	glm::clamp(transform.position.x, -1.5f, 1.5f);
}

void Player::Render() {
	GMonoPoly::Render();
	//wheel[0]->Render();
	//wheel[1]->Render();
}