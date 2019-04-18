#include "stdafx.h"
#include "GObject.h"
#include "GScene.h"

namespace Glory {

GObject::GObject() : isActive(true), isDeleted(false) {
	transform.scale = glm::vec3(1.0f);
}

GObject::~GObject() {
	for (auto iter = childs.begin(); iter != childs.end(); ++iter) {
		delete *iter;
	}
}

void GObject::AddChild(GObject* const obj) {
	childs.push_back(obj);
	obj->parent = this;
	obj->scene = this->scene;
}

void GObject::SetScene(GScene* const scene) {
	this->scene = scene;
	for (auto iter = childs.begin(); iter != childs.end(); ++iter) {
		(*iter)->SetScene(scene);
	}
}

void GObject::SetParent(GObject* const obj) {
	if (parent) {
		auto iter = std::find(parent->childs.begin(), parent->childs.end(), this);
		if (iter == parent->childs.end()) {
			//ERROR
			return;
		}
		parent->childs.erase(iter);
	}
	if (obj) {
		obj->childs.push_back(this);
	}
	parent = obj;
}

glm::mat4 GObject::ModelMatrix() {
	glm::mat4 result = glm::mat4(1.0f);
	for (GObject *ptr = this; ptr != nullptr; ptr = ptr->parent) {
		result = ptr->transform.Matrix() * result;
	}
	return result;
}

void GObject::Update(float deltaTime) {
	for (auto iter = childs.begin(); iter != childs.end(); ++iter) {
		if ((*iter)->isDeleted) {
			delete *iter;
			iter = childs.erase(iter);
			if (iter == childs.end()) {
				break;
			}
		} else if ((*iter)->isActive) {
			(*iter)->Update(deltaTime);
		}
	}
}

void GObject::Render() {
	for (auto iter = childs.begin(); iter != childs.end(); ++iter) {
		if ((*iter)->isActive) {
			(*iter)->Render();
		}
	}
}

}