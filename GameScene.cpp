#include "stdafx.h"
#include "GameScene.h"
#include "GApp.h"

#include "Coin.h"
#include "Spike.h"

GameScene::GameScene() {
	score = coinCount = enemyTimer = coinTimer = 0;

	for (int i = 0; i < 2; ++i) {
		road[i] = new GPolyhedron();
		road[i]->AddVertices({ { -6, 0, -100 },{ 6, 0, -100 },{ 6, 0, 0 },{ -6, 0, 0 } });
		road[i]->AddIndices({ 0, 1, 2, 2, 3, 0 });
		road[i]->AddColors({ { 0.5f, 0.5f, 0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 0.1f, 0.1f, 0.1f, 1.0f },{ 0.1f, 0.1f, 0.1f, 1.0f } });
		road[i]->transform.position.y = -1.0f;
		AddObject(road[i]);
	}
	road[1]->transform.position.z = -100.0f;

	player = new Player();
	AddObject(player);
	mainCamera = player->camera;

	for (int i = 0; i < 20; ++i) {
		Spike *spike = new Spike();
		AddObject(spike);
		spike->isActive = false;
		enemies.push_back(std::move(spike));

		Coin *coin = new Coin();
		AddObject(coin);
		coin->isActive = false;
		coins.push_back(std::move(coin));
	}

	glfwSetKeyCallback(GApp().Instance().Window(), KeyCallback);
	glfwSetCursorPosCallback(GApp::Instance().Window(), CursorPositionCallback);

	GameReady();
}

void GameScene::Update(float deltaTime) {
	GScene::Update(deltaTime);

	if (state == PLAYING) {
		GObject *obj = enemies.front();
		while (obj->isActive) {
			if (obj->transform.position.z <= player->transform.position.z + 10.0f) {
				enemies.pop_front();
				enemies.push_back(obj);
				obj = enemies.front();
			}
		}

		obj = coins.front();
		while (obj->isActive) {
			if (obj->transform.position.z <= player->transform.position.z + 10.0f) {
				obj->isActive = false;
				coins.pop_front();
				coins.push_back(obj);
				obj = coins.front();
			}
		}

		enemyTimer -= deltaTime;
		coinTimer -= deltaTime;

		if (enemyTimer <= 0) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<float> dist(1.5f, 3.0f);
			ActivateObject(enemies);
			enemyTimer = dist(mt);
		}

		if (coinTimer <= 0) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<float> dist(3.0f, 4.0f);
			ActivateObject(coins);
			coinTimer = dist(mt);
		}

		for (int i = 0; i < 2; ++i) {
			if (road[i]->transform.position.z - player->transform.position.z >= 125.0f) {
				road[i]->transform.position.z -= 200.0f;
			}
		}
	}
}

void GameScene::Render() {
	GScene::Render();
	road[0]->Render();
	road[1]->Render();

	for (auto iter : enemies) {
		iter->Render();
	}
	for (auto iter : coins) {
		iter->Render();
	}

	player->Render();
}

void GameScene::ActivateObject(std::deque<GObject*> queue) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(-3.0f, 3.0f);

	GObject *obj = queue.front();
	obj->transform.position.x = dist(mt);
	obj->transform.position.z = player->transform.position.z - 50.0f;
}

void GameScene::GameReady() {
	state = READY;
	score = coinCount = 0.0f;
}

void GameScene::GameStart() {
	state = PLAYING;
	player->zSpeed = 1.0f;
}

void GameScene::GameOver() {
	state = DEAD;
	player->zSpeed = 0.0f;
}

void GameScene::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	GameScene* scene = dynamic_cast<GameScene*>(GApp::Instance().Scene());
	switch (scene->state) {
	case READY:
		if (action == GLFW_PRESS) {
			scene->GameStart();
		}
		break;

	case PLAYING:
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
			scene->player->Jump();
		}
		break;

	case DEAD:
		if (action == GLFW_PRESS) {
			scene->GameReady();
		}
		break;
	}
}

void GameScene::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	GameScene* scene = dynamic_cast<GameScene*>(GApp::Instance().Scene());

}