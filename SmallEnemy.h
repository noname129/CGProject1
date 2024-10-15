#pragma once

#include "stdafx.h"
#include "Enemy.h"

class SmallEnemy : public Enemy {
public:
	static constexpr float attackMaxCool = 1.5f;
	static constexpr float objDistance = 9.0f;
	static constexpr float attackDistance = 20.0f;
	static constexpr float moveSpeed = 3.5f;
	static constexpr float collisionSize = 4.0f;

	SmallEnemy();

	void Act(Player* player, float deltaTime);
	void Update(float deltaTime);
};