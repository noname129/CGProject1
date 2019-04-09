#include "stdafx.h"
#include <glm/gtc/quaternion.hpp>

namespace Glory {

struct GTransform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	inline glm::mat4 Matrix() {
		return glm::mat4(1.0f);
	}
};

}