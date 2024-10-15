#include "stdafx.h"

#ifndef __GDIRECTIONALLIGHT_H__
#define	__GDIRECTIONALLIGHT_H__

#include "GObject.h"
#include "shader.h"

namespace Glory {

class GDirectionalLight : public GObject {
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	void SetUniform(int index, Shader& shader);
};

}

#endif