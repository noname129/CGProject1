#include "stdafx.h"
#include "GDirectionalLight.h"

namespace Glory {

void GDirectionalLight::SetUniform(int index, Shader& shader) {
	std::string lightIdentifier = std::string("dirLights[") + std::to_string(index) + "]";
	glm::vec4 direction = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	direction = ModelMatrix() * direction;
	shader.setVec3(lightIdentifier + ".direction", glm::vec3(direction));
	shader.setVec3(lightIdentifier + ".ambient", ambient);
	shader.setVec3(lightIdentifier + ".diffuse", diffuse);
	shader.setVec3(lightIdentifier + ".specular", specular);
}

}