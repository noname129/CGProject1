#include "stdafx.h"
#include "GSpotLight.h"

namespace Glory {

void GSpotLight::SetUniform(int index, Shader& shader) {
	std::string lightIdentifier = std::string("spotLights[") + std::to_string(index) + "]";
	glm::vec3 position = WorldPos();
	glm::vec3 direction = glm::vec3(ModelMatrix() * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)) - position;
	shader.setVec3(lightIdentifier + ".position", position);
	shader.setVec3(lightIdentifier + ".direction", direction);

	shader.setFloat(lightIdentifier + ".cutOff", cutOff);
	shader.setFloat(lightIdentifier + ".outerCutOff", outerCutOff);

	shader.setFloat(lightIdentifier + ".constant", constant);
	shader.setFloat(lightIdentifier + ".linear", linear);
	shader.setFloat(lightIdentifier + ".quadratic", quadratic);

	shader.setVec3(lightIdentifier + ".ambient", ambient);
	shader.setVec3(lightIdentifier + ".diffuse", diffuse);
	shader.setVec3(lightIdentifier + ".specular", specular);
}

}