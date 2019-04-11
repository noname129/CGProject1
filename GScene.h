#include "stdafx.h"

#ifndef __GSCENE_H__
#define __GSCENE_H__

namespace Glory {

class GObject;
class GCamera;

class GScene {

private:
	std::vector<GObject*> objects;

	glm::mat4 projection;
	glm::mat4 view;

public:
	GCamera * mainCamera;

	GScene();
	virtual ~GScene();

	void AddObject(GObject* obj);

	virtual void Update(float deltaTime);
	virtual void Render();

	inline glm::mat4 ProjectionMatrix() { return projection; }
	inline glm::mat4 ViewMatrix() { return view; }
};

}

#endif