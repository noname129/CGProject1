#include "stdafx.h"
#include "GScene.h"
#include "GObject.h"

namespace Glory {

void GScene::AddObject(GObject* obj) {
	objects.push_back(obj);
}

void GScene::Update(float deltaTime) {
	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {
		if ((*iter)->isDeleted) {
			delete *iter;
			iter = objects.erase(iter);
			if (iter == objects.end()) {
				break;
			}
		} else {
			(*iter)->Update(deltaTime);
		}
	}
}

void GScene::Render() {

}

}