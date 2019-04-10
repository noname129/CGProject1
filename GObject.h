#include "stdafx.h"

#ifndef __GOBJECT_H__
#define __GOBJECT_H__

#include "GScene.h"
#include "GTransform.h"

namespace Glory {

class GObject {
private:
	std::vector<GObject*> childs;
	GScene *scene;
	GObject *parent;

public:
	GTransform transform;

	bool isActive;
	bool isDeleted;

	GObject();
	~GObject();

	void AddChild(GObject* const obj);

	inline GScene& Scene() const { return *scene; }

	inline GObject* Parent() const { return parent; }
	void SetParent(GObject* const obj);

	virtual void Update(float deltaTime);
	virtual void Render();
};

}

#endif