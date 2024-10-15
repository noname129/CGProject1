#include "stdafx.h"
#include "GMathUtils.h"
#include "GApp.h"

namespace Glory {

namespace MathUtil {

float RandomRange(float a, float b) {
	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(a, b);
	return dist(mt);
}

float FaceTo2D(glm::vec2& from, glm::vec2& to) {
	float diffX = to.x - from.x;
	float diffY = to.y - from.y;
	return glm::atan(diffY, diffX);
}

glm::vec2 NDCToScreen(glm::vec2 ndc) {
	return glm::vec2((ndc.x + 1) / 2.0f * GApp::Instance()->GetWindowWidth(),
		(ndc.y + 1) / 2.0f * GApp::Instance()->GetWindowHeight());
}

glm::vec2 NDCToScreen(float x, float y) {
	return NDCToScreen(glm::vec2(x, y));
}

}

}