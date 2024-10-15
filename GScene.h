#include "stdafx.h"

#ifndef __GSCENE_H__
#define __GSCENE_H__

#define NR_DIR_LIGHTS 2
#define NR_POINT_LIGHTS 2
#define NR_SPOT_LIGHTS 2

class Shader;

namespace Glory {

class GObject;
class GCamera;
class GDirectionalLight;
class GSpotLight;

class GScene {

protected:
	std::vector<GObject*> objects;

	glm::mat4 projection;
	glm::mat4 view;

	Shader *lastUsedShader;

public:
	GCamera * mainCamera;
	GDirectionalLight* dirLights[NR_DIR_LIGHTS];
	GSpotLight* spotLights[NR_SPOT_LIGHTS];

	GScene();
	virtual ~GScene();

	void AddObject(GObject* obj);
	void CalculateLights(Shader& shader);

	virtual void Update(float deltaTime);
	virtual void Render();

	inline glm::mat4 ProjectionMatrix() { return projection; }
	inline glm::mat4 ViewMatrix() { return view; }
};

}

#endif