#include "stdafx.h"

#ifndef __GTRANSFORM_H__
#define __GTRANSFORM_H__

#include <glm/gtc/quaternion.hpp>

namespace Glory {

struct GTransform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	inline glm::mat4 Matrix() {
		auto result = glm::mat4(1.0f);
		result = glm::translate(result, position);
		result = glm::scale(result, scale);
		result = glm::rotate(result, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		result = glm::rotate(result, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		result = glm::rotate(result, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		return result;
	}
};

}

#endif