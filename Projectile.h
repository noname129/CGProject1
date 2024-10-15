#pragma once

#include "GObject.h"

using namespace Glory;

class Projectile : public GObject {
public:
	static constexpr float collisionSize = 1.0f;
	static constexpr float grazeSize = 2.5f;
	static constexpr float speed = 9.0f;

	bool grazed;

	void Update(float deltaTime);
	void Render();
};