#include "stdafx.h"
#include "Explosion.h"
#include "GameScene.h"
#include "GMathUtils.h"

Explosion::Explosion(float scale, float expireTime, glm::vec4 color) : expireTime(expireTime), currentTime(0), color(color) {
	transform.scale = glm::vec3(scale);
}

void Explosion::Update(float deltaTime) {
	transform.scale += 2.5f * deltaTime;

	currentTime += deltaTime;
	if (currentTime > expireTime) {
		isDeleted = true;
	}
}

void Explosion::Render() {
	GameScene *scene = dynamic_cast<GameScene *>(this->scene);
	glm::vec4 posV4 = scene->ProjectionMatrix() * scene->ViewMatrix() * glm::vec4(WorldPos(), 1);
	glm::vec2 pos = MathUtil::NDCToScreen(posV4.x / posV4.z, posV4.y / posV4.z);
	scene->canvas.Draw("Resources/ui/Explosion.png",
		pos.x - 25.0f * transform.scale.x, pos.y - 25.0f * transform.scale.y,
		50.0f * transform.scale.x, 50.0f * transform.scale.y);
}