#include "stdafx.h"

#ifndef	__GAMESCENE_H__
#define __GAMESCENE_H__

#include "GScene.h"
#include "GCamera.h"
#include "GTexturedMesh.h"

#include <deque>
#include <stack>
#include <random>
#include "GModel.h"
#include "text.h"
#include "GCanvas.h"

#include "Player.h"

using namespace Glory;

class GameScene : public GScene {
public:
	GCanvas canvas;
	Text *text;

	GTexturedMesh * background;

	GCamera * camera;
	GDirectionalLight * dl;

	Player *player;

	GObject *enemies;
	GObject *projectiles;
	GObject *explosions;

	float enemyCooldown;
	int score;
	bool restart;
	float restartTime;

	GameScene();

	void Update(float deltaTime);
	void Render();

	void LoadResources();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
};

#endif