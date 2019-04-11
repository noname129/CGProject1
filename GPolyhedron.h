#include "stdafx.h"
#include "GDrawable.h"

#ifndef	__GPOLYHEDRON_H__
#define __GPOLYHEDRON_H__

namespace Glory {

class GPolyhedron : public GDrawable {
protected:
	std::vector<glm::vec3> vertices;
	std::vector<int> indices;

public:
	GPolyhedron();
};

}

#endif