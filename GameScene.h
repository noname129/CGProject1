#include "stdafx.h"

#ifndef	__GAMESCENE_H__
#define __GAMESCENE_H__

#include "GScene.h"
#include "GCamera.h"
#include "GMonoPoly.h"

#include "Player.h"
#include "Coin.h"

#include <deque>
#include <stack>
#include <random>

using namespace Glory;

enum GameState {
	READY,
	PLAYING,
	DEAD
};

class GameScene : public GScene {
public:
	GameState state;
	float score;
	float coinCount;
	float enemyTimer, coinTimer;

	GCamera *camera;
	GPolyhedron *road[2];

	Player *player;
	std::deque<GObject*> activeEnemies;
	std::deque<GObject*> activeCoins;
	std::stack<GObject*> enemyPool;
	std::stack<GObject*> coinPool;
		
	float mouseX;

	GameScene();

	void GameReady();
	void GameStart();
	void GameOver();

	void Update(float deltaTime);
	void Render();

	void ActivateObject(std::stack<GObject*>& from, std::deque<GObject*>& out);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
};

#endif