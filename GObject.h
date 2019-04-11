#include "stdafx.h"

#ifndef __GOBJECT_H__
#define __GOBJECT_H__

#include "GScene.h"
#include "GTransform.h"

namespace Glory {

class GObject {
	friend void GScene::AddObject(GObject* obj);

protected:
	std::vector<GObject*> childs;
	GScene *scene;
	GObject *parent;

public:
	GTransform transform;

	bool isActive;
	bool isDeleted;

	GObject();
	virtual ~GObject();
	GObject(const GObject& other) = delete;
	GObject& operator=(const GObject& other) = delete;

	void AddChild(GObject* const obj);

	inline GScene& Scene() const { return *scene; }

	inline GObject* Parent() const { return parent; }
	void SetParent(GObject* const obj);

	glm::mat4 ModelMatrix();
	inline glm::vec3 WorldPos() { return ModelMatrix() * glm::vec4(transform.position, 1.0f); }

	virtual void Update(float deltaTime);
	virtual void Render();
};

}

#endif