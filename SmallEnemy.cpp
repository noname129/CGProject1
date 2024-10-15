#include "stdafx.h"
#include "SmallEnemy.h"
#include "Player.h"
#include "GameScene.h"
#include "Projectile.h"
#include "Explosion.h"
#include "GMathUtils.h"

SmallEnemy::SmallEnemy() {
	model = new GModel("Resources/models/smallenemy/Luminaris OBJ.obj");
	model->transform.scale = glm::vec3(0.06f);
	AddChild(model);
}

void SmallEnemy::Update(float deltaTime) {
	Enemy::Update(deltaTime);

	GameScene *scene = dynamic_cast<GameScene *>(this->scene);
	Player *player = scene->player;

	if (scene->player->state != Player::DEAD) {
		glm::vec2 tail = glm::vec2(player->transform.position);
		glm::vec2 head = glm::vec2(transform.position);
		glm::vec2 playerDir = head - tail;
		float currentDistance = glm::length(playerDir);
		if (currentDistance < collisionSize) {
			if (currentDistance < collisionSize) {
				if (player->state == Player::MOVING) {
					player->state = Player::DEAD;
					Explosion *exp = new Explosion(1.5f, 2.0f);
					exp->transform.position = player->WorldPos();
					scene->explosions->AddChild(exp);
				} else {
					for (int i = 0; i < 3; ++i) {
						float randomAngle = MathUtil::RandomRange(0.0f, 2.0f * glm::pi<float>());
						float randomRadius = MathUtil::RandomRange(0.0f, 1.5f);
						float randomScale = MathUtil::RandomRange(1.0f, 2.0f);
						float randomExp = MathUtil::RandomRange(1.0f, 3.0f);
						Explosion *exp = new Explosion(randomScale, randomExp);
						exp->transform.position = WorldPos();
						exp->transform.position.x += randomRadius * glm::cos(randomAngle);
						exp->transform.position.y += randomRadius * glm::sin(randomAngle);
						scene->explosions->AddChild(exp);
					}
					scene->score += 3000;
					isDeleted = true;
				}
			}
		}
	}
}

void SmallEnemy::Act(Player* player, float deltaTime) {
	glm::vec2 tail = glm::vec2(player->transform.position);
	glm::vec2 head = glm::vec2(transform.position);
	glm::vec2 playerDir = head - tail;
	float currentDistance = glm::length(playerDir);

	float moveAmount = glm::min(glm::abs(objDistance - currentDistance), moveSpeed * deltaTime);
	float playerDeg = glm::degrees(glm::atan(-playerDir.y, -playerDir.x));

	transform.position += glm::vec3((glm::sign(objDistance - currentDistance) * glm::normalize(playerDir) * moveAmount), 0.0f);
	transform.rotation.z = playerDeg + 90.0f;

	attackCooldown = glm::max(0.0f, attackCooldown - deltaTime);

	if (attackCooldown <= 0.0f && currentDistance <= attackDistance) {
		attackCooldown += attackMaxCool;
		GameScene *scene = dynamic_cast<GameScene *>(this->scene);
		Projectile *p = new Projectile();
		p->transform.position = WorldPos();
		p->transform.rotation.z = playerDeg;
		scene->projectiles->AddChild(p);
	}
}