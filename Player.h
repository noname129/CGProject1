#pragma once

#include "stdafx.h"
#include "GObject.h"
#include "GModel.h"
#include "GCamera.h"
#include "keyframe.h"

using namespace Glory;

class Player : public GObject {
public:
	enum State {
		MOVING,
		RUSHING,
		DEAD
	};

	static constexpr float rushMaxCool = 3.0f;

	GObject * modelObject;
	GModel * model;
	GCamera * camera;

	KeyFraming rushRotX;

	State state;
	glm::vec2 moveVec;

	glm::vec2 rushVec;
	float currentAnimTime;
	float rushCooldown;

	Player();

	void BeginRush(glm::vec2 destDir);

	void Update(float deltaTime);
	void Render();

};