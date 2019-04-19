#include "stdafx.h"

#ifndef __PLAYER_H__
#define	__PLAYER_H__

#include "GPolyhedron.h"
#include "GMonoPoly.h"
#include "GCamera.h"

using namespace Glory;

class Player : public GObject {

public:
	float zSpeed;
	float jumpSpeed;
	bool onGround;

	GMonoPoly *cube;
	GMonoPoly *wheel[2];
	GCamera *camera;

	Player();

	void Jump();

	void Update(float deltaTime);

	void Render();
};

#endif