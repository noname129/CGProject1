#pragma once
#include "stdafx.h"
#include "GModel.h"

using namespace Glory;

class Explosion : public GObject {
public:
	float expireTime;
	float currentTime;
	glm::vec4 color;

	Explosion(float scale, float expireTime, glm::vec4 color = glm::vec4(1.0f, 0.32f, 0.06f, 1.0f));

	void Update(float deltaTime);
	void Render();
};