#include "stdafx.h"
#include "GObject.h"

#ifndef __GCAMERA_H__
#define	__GCAMERA_H__

namespace Glory {

class GCamera : public GObject {
	struct Option {
		float fovAngle;
		float nearPlaneDistance;
		float farPlaneDistance;
		bool orthogonal;
	};

private:
	Option option;
	glm::mat4 projection;

public:
	GCamera();
	GCamera(Option option);
	GCamera(float fovAngle, float nearPlaneDistance, float farplaneDistance, bool orthogonal);

	Option GetCameraOption() const;
	void SetCameraOption(Option option);

	glm::mat4 ViewMatrix();
	glm::mat4 ProjectionMatrix();
};

}

#endif