#pragma once

#include "stdafx.h"
#include "Enemy.h"
#include "GSpotLight.h"

class LargeEnemy : public Enemy {
public:
	static constexpr float attackMaxCool = 0.125f;
	static constexpr float objDistance = 10.0f;
	static constexpr float attackDistance = 25.0f;
	static constexpr float moveSpeed = 4.5f;
	static constexpr float collisionSize = 6.5f;

	GSpotLight *spotLight;

	int angleOffset;

	LargeEnemy();
	~LargeEnemy();

	void Act(Player* player, float deltaTime);
	void Update(float deltaTime);
};