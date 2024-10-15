#include "stdafx.h"
#include "Player.h"
#include "GMathUtils.h"
#include "GApp.h"

Player::Player() : rushRotX(6) {
	modelObject = new GObject();
	modelObject->transform.scale = glm::vec3(0.35f);
	AddChild(modelObject);

	model = new GModel("Resources/models/spaceship/Intergalactic_Spaceship-(Wavefront).obj");
	modelObject->AddChild(model);
	model->transform.rotation.x = 90.0f;
	model->transform.rotation.y = 90.0f;

	camera = new GCamera();
	camera->transform.position.z = 22.5f;
	camera->transform.position.y = -13.0f;
	camera->transform.rotation.x = 30.0f;
	AddChild(camera);

	rushRotX.setKey(0, 0.0f, 0.0f);
	rushRotX.setKey(1, 0.25f, 180.0f);
	rushRotX.setKey(2, 0.5f, 540.0f);
	rushRotX.setKey(3, 1.5f, 2700.0f);
	rushRotX.setKey(4, 1.75f, 2880.0f);
	rushRotX.setKey(5, 2.0f, 3060.0f);

	state = MOVING;
	moveVec = glm::vec2(0.0f);
	rushCooldown = 0.0f;
}

void Player::Update(float deltaTime) {
	GObject::Update(deltaTime);

	if (state == MOVING) {
		glm::vec2 dir = glm::length(moveVec) == 0 ? moveVec : glm::normalize(moveVec);
		if (dir.x > 0.0f) {
			if (dir.y > 0.0f) {
				modelObject->transform.rotation.z = 45.0f;
			} else if (dir.y < 0.0f) {
				modelObject->transform.rotation.z = 315.0f;
			} else {
				modelObject->transform.rotation.z = 0.0f;
			}
		} else if (dir.x < -0.0f) {
			if (dir.y > 0.0f) {
				modelObject->transform.rotation.z = 135.0f;
			} else if (dir.y < 0.0f) {
				modelObject->transform.rotation.z = 225.0f;
			} else {
				modelObject->transform.rotation.z = 180.0f;
			}
		} else {
			if (dir.y > 0.0f) {
				modelObject->transform.rotation.z = 90.0f;
			} else if (dir.y < 0.0f) {
				modelObject->transform.rotation.z = 270.0f;
			}
		}
		transform.position.x += 5.5f * dir.x * deltaTime;
		transform.position.y += 5.5f * dir.y * deltaTime;

		rushCooldown = glm::max(rushCooldown - deltaTime, 0.0f);
	} else if (state == RUSHING) {
		currentAnimTime += deltaTime;
		if (currentAnimTime < rushRotX.keys[rushRotX.nKeys - 1].time) {
			model->transform.rotation.x = rushRotX.getValLinear(currentAnimTime) + 90.0f;
			transform.position.x += rushVec.x * 16.0f * deltaTime;
			transform.position.y += rushVec.y * 16.0f * deltaTime;
		} else {
			model->transform.rotation.x = 90.0f;
			state = MOVING;
		}
	}
}

void Player::BeginRush(glm::vec2 dir) {
	if (rushCooldown > 0.0f || state != MOVING) {
		return;
	}

	rushCooldown = rushMaxCool;
	state = RUSHING;
	currentAnimTime = 0.0f;
	rushVec = glm::normalize(dir);// glm::normalize(destDir - glm::vec2(transform.position.x, transform.position.y));
	modelObject->transform.rotation.z = glm::degrees(glm::atan(rushVec.y, rushVec.x));
}

void Player::Render() {
	if (state != DEAD) {
		model->Render();
	}
}