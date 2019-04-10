#include "stdafx.h"
#include "GObject.h"
#include "GScene.h"

namespace Glory {

GObject::GObject() : isActive(true), isDeleted(false) {

}

GObject::~GObject() {
	for (auto iter = childs.begin(); iter != childs.end(); ++iter) {
		delete *iter;
	}
}

void GObject::AddChild(GObject* const obj) {
	childs.push_back(obj);
	obj->parent = this;
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

void GObject::Update(float deltaTime) {
	for (auto iter = childs.begin(); iter != childs.end(); ++iter) {
		if ((*iter)->isDeleted) {
			delete *iter;
			iter = childs.erase(iter);
			if (iter == childs.end()) {
				break;
			}
		} else {
			(*iter)->Update(deltaTime);
		}
	}
}

void GObject::Render() {
	for (auto iter = childs.begin(); iter != childs.end(); ++iter) {
		(*iter)->Render();
	}
}

}