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
		glm::translate(result, position);
		glm::scale(result, scale);
		return result;
	}

	inline GTransform WorldTransform() {
		GTransform result = {
			this->position,
			this->rotation,
			this->scale
		};
		return result;
	}
};

}

#endif