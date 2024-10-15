#include "stdafx.h"

#ifndef __GSPOTLIGHT_H__
#define	__GSPOTLIGHT_H__

#include "GObject.h"
#include "shader.h"

namespace Glory {

class GSpotLight : public GObject {
public:
	float cutOff = glm::cos(glm::radians(15.0f));
	float outerCutOff = glm::cos(glm::radians(22.5f));

	float constant = 1.0f;
	float linear = 0.045f;
	float quadratic = 0.0075f;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	void SetUniform(int index, Shader& shader);
};

}

#endif