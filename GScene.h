#include "stdafx.h"
#include "GObject.h"

namespace Glory {

class GScene {
private:
	std::vector<GObject> objects;

public:
	void AddObject(GObject* object);

	void Update(float deltaTime);
};

}