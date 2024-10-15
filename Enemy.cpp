#include "stdafx.h"
#include "Enemy.h"
#include "GameScene.h"

Enemy::Enemy() {
	state = MOVING;
	attackCooldown = 0.0f;
}

void Enemy::Update(float deltaTime) {
	GObject::Update(deltaTime);
	GameScene *scene = dynamic_cast<GameScene *>(this->scene);
	Act(scene->player, deltaTime);
}

void Enemy::Render() {
	model->Render();
}