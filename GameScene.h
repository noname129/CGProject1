#include "stdafx.h"

#ifndef	__GAMESCENE_H__
#define __GAMESCENE_H__

#include "GScene.h"
#include "GCamera.h"
#include "GPolyhedron.h"

using namespace Glory;

class GameScene : public GScene {
	GCamera *camera;
	GPolyhedron *cube;
	GPolyhedron *cube2;

public:
	GameScene();

	void Update(float deltaTime);
	void Render();
};

#endif