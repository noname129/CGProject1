#include "stdafx.h"
#include "GDrawable.h"

namespace Glory {

GDrawable::GDrawable() : GDrawable(new Shader("global.vs", "global.fs")) {

}

GDrawable::GDrawable(Shader* shader) {
	SetShader(shader);
}

GDrawable::~GDrawable() {
	if (shader) {
		delete shader;
	}
}

void GDrawable::SetShader(Shader* shader) {
	this->shader = shader;
}

void GDrawable::Update(float deltaTime) {
	GObject::Update(deltaTime);
}

void GDrawable::Render() {
	if (!shader || !scene->mainCamera) {
		return;
	}

	shader->use();
	shader->setMat4("projection", scene->ProjectionMatrix());
	shader->setMat4("view", scene->ViewMatrix());
	shader->setMat4("model", ModelMatrix());
}

}