#include "stdafx.h"
#include "LargeEnemy.h"
#include "Player.h"
#include "Projectile.h"
#include "Explosion.h"
#include "GameScene.h"
#include "GMathUtils.h"

LargeEnemy::LargeEnemy() {
	model = new GModel("Resources/models/largeenemy/MK6_OBJ.obj");
	model->transform.scale = glm::vec3(0.008f);
	model->transform.rotation.x = 90.0f;
	AddChild(model);

	spotLight = new GSpotLight();
	spotLight->ambient = glm::vec3(0.8f, 0.0f, 0.0f);
	spotLight->diffuse = glm::vec3(0.9f, -0.5f, -0.5f);
	spotLight->specular = glm::vec3(1.0f, -0.8f, -0.8f);
	
	spotLight->quadratic = 0.0f;

	spotLight->cutOff = glm::cos(glm::radians(10.0f));
	spotLight->outerCutOff = glm::cos(glm::radians(15.0f));
	spotLight->transform.rotation.x = 60.0f;
	AddChild(spotLight);
	angleOffset = 1;
}

LargeEnemy::~LargeEnemy() {
	scene->spotLights[0] = nullptr;
}

void LargeEnemy::Update(float deltaTime) {
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
					for (int i = 0; i < 5; ++i) {
						float randomAngle = MathUtil::RandomRange(0.0f, 2.0f * glm::pi<float>());
						float randomRadius = MathUtil::RandomRange(0.0f, 4.0f);
						float randomScale = MathUtil::RandomRange(1.5f, 3.0f);
						float randomExp = MathUtil::RandomRange(1.0f, 3.0f);
						Explosion *exp = new Explosion(randomScale, randomExp);
						exp->transform.position = WorldPos();
						exp->transform.position.x += randomRadius * glm::cos(randomAngle);
						exp->transform.position.y += randomRadius * glm::sin(randomAngle);
						scene->explosions->AddChild(exp);
					}
					scene->score += 10000;
					isDeleted = true;
				}
			}
		}
	}
}

void LargeEnemy::Act(Player* player, float deltaTime) {

	glm::vec2 tail = glm::vec2(player->transform.position);
	glm::vec2 head = glm::vec2(transform.position);
	glm::vec2 playerDir = head - tail;
	float currentDistance = glm::length(playerDir);

	float moveAmount = glm::min(glm::abs(objDistance - currentDistance), moveSpeed * deltaTime);
	float playerDeg = glm::degrees(glm::atan(-playerDir.y, -playerDir.x));

	transform.position += glm::vec3((glm::sign(objDistance - currentDistance) * glm::normalize(playerDir) * moveAmount), 0.0f);

	transform.rotation.z = playerDeg - 90.0f;
	spotLight->transform.rotation.z = glm::degrees(glm::atan(playerDir.y, playerDir.x)) + 180.0f;
	spotLight->transform.position.z = currentDistance / 1.73f;

	attackCooldown = glm::max(0.0f, attackCooldown - deltaTime);

	if (attackCooldown <= 0.0f && currentDistance <= attackDistance) {
		float pi = glm::pi<float>();
		attackCooldown += attackMaxCool;
		GameScene *scene = dynamic_cast<GameScene *>(this->scene);

		Projectile *p = new Projectile();
		p->transform.position = WorldPos();
		p->transform.rotation.z = playerDeg + 90.0f * glm::sin(pi / 12.0f * angleOffset);
		scene->projectiles->AddChild(p);

		p = new Projectile();
		p->transform.position = WorldPos();
		p->transform.rotation.z = playerDeg - 90.0f * glm::sin(pi / 12.0f * angleOffset);
		scene->projectiles->AddChild(p);

		++angleOffset;

		//attack;
	}
}