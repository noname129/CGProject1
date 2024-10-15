#include "stdafx.h"
#include "Projectile.h"
#include "GameScene.h"
#include "GMathUtils.h"

#include "Explosion.h"

void Projectile::Update(float deltaTime) {
	GameScene *scene = dynamic_cast<GameScene *>(this->scene);
	glm::mat2 rot;
	rot[0][0] = glm::cos(glm::radians(transform.rotation.z));
	rot[0][1] = -glm::sin(glm::radians(transform.rotation.z));
	rot[1][0] = glm::sin(glm::radians(transform.rotation.z));
	rot[1][1] = glm::cos(glm::radians(transform.rotation.z));
	glm::vec2 movement = rot * glm::vec2(speed, 0.0f);

	transform.position.x += movement.x * deltaTime;
	transform.position.y -= movement.y * deltaTime;

	Player *player = scene->player;
	if (scene->player->state != Player::DEAD) {
		glm::vec2 tail = glm::vec2(player->transform.position);
		glm::vec2 head = glm::vec2(transform.position);
		glm::vec2 playerDir = head - tail;
		float currentDistance = glm::length(playerDir);
		if (currentDistance < grazeSize) {
			if (!grazed) {
				grazed = true;
				scene->score += 500;
			}
			if (currentDistance < collisionSize) {
				if (player->state == Player::MOVING) {
					player->state = Player::DEAD;
					Explosion *exp = new Explosion(1.5f, 2.0f);
					exp->transform.position = player->WorldPos();
					scene->explosions->AddChild(exp);
				}
				isDeleted = true;
			}
		} else if (currentDistance > 25.0f) {
			isDeleted = true;
		}
	}
}

void Projectile::Render() {
	GameScene *scene = dynamic_cast<GameScene *>(this->scene);
	glm::vec4 posV4 = scene->ProjectionMatrix() * scene->ViewMatrix() * glm::vec4(WorldPos(), 1);
	glm::vec2 pos = MathUtil::NDCToScreen(posV4.x / posV4.z, posV4.y / posV4.z);
	scene->canvas.Draw("Resources/ui/Projectile.png",
		pos.x - 25.0f * transform.scale.x, pos.y - 25.0f * transform.scale.y,
		50.0f * transform.scale.x, 50.0f * transform.scale.y);
}