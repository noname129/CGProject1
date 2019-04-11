#include "stdafx.h"
#include "GDrawable.h"

namespace Glory {

GDrawable::GDrawable() {

}

GDrawable::~GDrawable() {
	if (shader) {
		delete shader;
	}
}

void GDrawable::Update(float deltaTime) {

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