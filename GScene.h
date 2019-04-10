#include "stdafx.h"

#ifndef __GSCENE_H__
#define __GSCENE_H__

namespace Glory {
class GObject;

class GScene {

private:
	std::vector<GObject*> objects;

public:
	void AddObject(GObject* obj);

	virtual void Update(float deltaTime);
	virtual void Render();
};

}

#endif