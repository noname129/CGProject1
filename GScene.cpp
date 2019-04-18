#include "stdafx.h"
#include "GScene.h"
#include "GObject.h"
#include "GCamera.h"

namespace Glory {

GScene::GScene() {

}

GScene::~GScene() {
	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {
		delete *iter;
	}
}

void GScene::AddObject(GObject* obj) {
	objects.push_back(obj);
	obj->SetScene(this);
}

void GScene::Update(float deltaTime) {
	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {
		if ((*iter)->isDeleted) {
			delete *iter;
			iter = objects.erase(iter);
			if (iter == objects.end()) {
				break;
			}
		} else if ((*iter)->isActive) {
			(*iter)->Update(deltaTime);
		}
	}
}

void GScene::Render() {
	if (!mainCamera) {
		return;
	}
	projection = mainCamera->ProjectionMatrix();
	view = mainCamera->ViewMatrix();
}

}