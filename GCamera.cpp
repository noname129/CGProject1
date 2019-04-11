#include "stdafx.h"
#include "GCamera.h"
#include "GApp.h"

namespace Glory {

GCamera::GCamera() : GCamera(glm::radians(45.f), 0.1f, 100.0f, false) {

}

GCamera::GCamera(Option option) {
	this->option = option;
	SetCameraOption(option);
}

GCamera::GCamera(float fovAngle, float nearPlaneDistance, float farplaneDistance, bool orthogonal) {
	Option option = {
		fovAngle,
		nearPlaneDistance,
		farplaneDistance,
		orthogonal
	};
	SetCameraOption(option);
}

GCamera::Option GCamera::GetCameraOption() const {
	return option;
}

void GCamera::SetCameraOption(Option option) {
	this->option = option;
	float screenWidth = static_cast<float>(GApp::Instance().GetWindowWidth());
	float screenHeight = static_cast<float>(GApp::Instance().GetWindowHeight());
	if (option.orthogonal) {
		projection = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, option.nearPlaneDistance, option.farPlaneDistance);
	} else {
		projection = glm::perspective(option.fovAngle, screenWidth / screenHeight, option.nearPlaneDistance, option.farPlaneDistance);
	}
}

glm::mat4 GCamera::ViewMatrix() {
	glm::mat4 view;
	glm::vec4 direction = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	direction = ModelMatrix() * direction;
	glm::vec3 pos = WorldPos();
	view = glm::lookAt(pos, pos + glm::vec3(direction), glm::vec3(0.0f, 1.0f, 0.0f));
	return view;
}

glm::mat4 GCamera::ProjectionMatrix() {
	return projection;
}

}