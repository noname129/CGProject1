#pragma once

#include "stdafx.h"
#include "GModel.h"

using namespace Glory;

class Player;

class Enemy : public GObject {
	enum State {
		MOVING,
		RUSHING,
		DEAD
	};

public:
	GModel * model;
	State state;

	float attackCooldown;

	Enemy();

	virtual void Act(Player* player, float deltaTime) = 0;

	void Update(float deltaTime);
	void Render();
};