#include "stdafx.h"
#include "GDrawable.h"

namespace Glory {

Shader GDrawable::defaultShader;

GDrawable::GDrawable() : GDrawable(&defaultShader) {

}

GDrawable::GDrawable(Shader* shader) {
	SetShader(shader);
}

GDrawable::~GDrawable() {

}

void GDrawable::SetShader(Shader* shader) {
	this->shader = shader;
}

void GDrawable::Update(float deltaTime) {
	GObject::Update(deltaTime);
}

void GDrawable::Render() {
	if (!shader || !isActive || !scene->mainCamera) {
		return;
	}

	shader->use();
	scene->CalculateLights(*shader);
	shader->setMat4("projection", scene->ProjectionMatrix());
	shader->setMat4("view", scene->ViewMatrix());
	shader->setMat4("model", ModelMatrix());
}

}