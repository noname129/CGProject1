#include "stdafx.h"
#include "GameScene.h"
#include "GApp.h"

#include "Coin.h"
#include "Spike.h"

GameScene::GameScene() {
	score = coinCount = enemyTimer = coinTimer = 0;

	for (int i = 0; i < 2; ++i) {
		road[i] = new GPolyhedron();
		road[i]->AddVertices({ 
			{ -25, -0.1f, -150 },{ 25, -0.1f, -150 },{ 25, -0.1f, 0 },{ -25, -0.1f, 0 },
			{ -6.15f, 0, -150 },{ 6.15f, 0, -150 },{ 6.15f, 0, 0 },{ -6.15f, 0, 0 }});
		road[i]->AddIndices({ 4, 5, 6, 6, 7, 4, 0, 1, 2, 2, 3, 0 });
		road[i]->transform.position.y = -1.0f;
		AddObject(road[i]);
	}
	road[0]->AddColors({ 
		{ 0.19f, 0.82f, 0.04f, 1.0f },{ 0.19f, 0.82f, 0.04f, 1.0f },{ 0.29f, 0.92f, 0.14f, 1.0f },{ 0.29f, 0.92f, 0.14f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 0.1f, 0.1f, 0.1f, 1.0f },{ 0.1f, 0.1f, 0.1f, 1.0f } });
	road[1]->AddColors({ 
		{ 0.29f, 0.92f, 0.14f, 1.0f },{ 0.29f, 0.92f, 0.14f, 1.0f },{ 0.19f, 0.82f, 0.04f, 1.0f },{ 0.19f, 0.82f, 0.04f, 1.0f },
		{ 0.1f, 0.1f, 0.1f, 1.0f },{ 0.1f, 0.1f, 0.1f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f } });

	player = new Player();
	AddObject(player);
	mainCamera = player->camera;

	for (int i = 0; i < 18; ++i) {
		Spike *spike = new Spike();
		AddObject(spike);
		spike->isActive = false;
		enemyPool.push(std::move(spike));

		Coin *coin = new Coin();
		AddObject(coin);
		coin->isActive = false;
		coinPool.push(std::move(coin));
	}

	glfwSetKeyCallback(GApp().Instance().Window(), KeyCallback);
	glfwSetCursorPosCallback(GApp::Instance().Window(), CursorPositionCallback);

	GameReady();
}

void GameScene::Update(float deltaTime) {
	GScene::Update(deltaTime);

	if (state == PLAYING) {
		float windowWidth = static_cast<float>(GApp::Instance().GetWindowWidth());
		float mouseXRatio = 2 * (mouseX / windowWidth - 0.5f);
		mouseXRatio = glm::clamp(mouseXRatio, -0.75f, 0.75f);
		player->transform.position.x = 4.0f / 3.0f * mouseXRatio * (6.0f - player->cube->transform.scale.x);

		for (auto iter = activeEnemies.begin(); iter != activeEnemies.end(); ++iter) {
			if (!(*iter)->isActive) {
				break;
			}
			if ((*iter)->transform.position.z >= player->transform.position.z + 10.0f) {
				(*iter)->isActive = false;
				enemyPool.push((*iter));
				iter = activeEnemies.erase(iter);
				if (iter == activeEnemies.end()) break;
			}
		}

		for (auto iter = activeCoins.begin(); iter != activeCoins.end(); ++iter) {
			if (!(*iter)->isActive) {
				break;
			} else if (glm::distance(player->transform.position, (*iter)->transform.position)
				<= player->cube->transform.scale.x + 0.75f) {
				(*iter)->isActive = false;
				coinPool.push((*iter));
				iter = activeCoins.erase(iter);
				coinCount += 1;
				player->cube->transform.scale += 0.1f;
				player->transform.position.y = 1.2f * player->cube->transform.scale.x - 1.0f;
				if (iter == activeCoins.end()) break;
			}
			if ((*iter)->transform.position.z >= player->transform.position.z + 10.0f) {
				(*iter)->isActive = false;
				coinPool.push((*iter));
				iter = activeCoins.erase(iter);
				if (iter == activeCoins.end()) break;
			}
		}
	
		enemyTimer -= deltaTime;
		coinTimer -= deltaTime;

		if (enemyTimer <= 0) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<float> dist(1.5f, glm::max(1.5f, 3.0f - score * (1.0f + 0.1f * coinCount) / 10000.0f));
			std::uniform_int_distribution<int> dist2(1, glm::min(6, (int)(score * (1.0f + 0.1f * coinCount)) / 1000 + 1));
			int count = dist2(mt);
			for (int i = 0; i < count; ++i) {
				ActivateObject(enemyPool, activeEnemies);
			}
			enemyTimer = dist(mt);
		}

		if (coinTimer <= 0) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<float> dist(3.0f + 0.3f * coinCount, 4.0f + 0.4f * coinCount);
			ActivateObject(coinPool, activeCoins);
			coinTimer = dist(mt);
		}

		for (int i = 0; i < 2; ++i) {
			if (road[i]->transform.position.z - player->transform.position.z >= 200.0f) {
				road[i]->transform.position.z -= 300.0f;
			}
		}

		player->zSpeed += 1.0f * deltaTime;
		score += player->zSpeed * 2 * deltaTime;
	} else if (state == DEAD) {
		float newScale = glm::max(0.0f, player->cube->transform.scale.x - 0.6f * deltaTime);
		player->cube->transform.scale = glm::vec3(newScale);
	}
}

void GameScene::Render() {
	GScene::Render();
	road[0]->Render();
	road[1]->Render();

	for (auto iter : activeEnemies) {
		iter->Render();
	}
	for (auto iter : activeCoins) {
		iter->Render();
	}

	player->Render();
}

void GameScene::ActivateObject(std::stack<GObject*>& from, std::deque<GObject*>& out) {
	if (from.size() == 0) return;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(-3.0f, 3.0f);

	GObject *obj = from.top();
	obj->transform.position.x = dist(mt);
	obj->transform.position.y = dist(mt) / 2 + 1.5f;
	obj->transform.position.z = player->transform.position.z - 65.0f;
	obj->isActive = true;
	out.push_back(obj);
	from.pop();
}

void GameScene::GameReady() {
	state = READY;
	player->transform.position = glm::vec3(0);
	player->cube->transform.scale = glm::vec3(1);
	road[0]->transform.position.z = 2.0f;
	road[1]->transform.position.z = -148.0f;
	score = coinCount = 0.0f;
}

void GameScene::GameStart() {
	state = PLAYING;
	player->zSpeed = 35.0f;
}

void GameScene::GameOver() {
	state = DEAD;
	player->zSpeed = 0.0f;
	printf("Score : %d\n", (int)(score * (1.0f + 0.1f * coinCount)));
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
	scene->mouseX = static_cast<float>(xpos);
}