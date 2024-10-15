#include "stdafx.h"
#include "GScene.h"
#include "GObject.h"
#include "GCamera.h"
#include "GDirectionalLight.h"
#include "GSpotLight.h"
#include "shader.h"

namespace Glory {

GScene::GScene() {

}

GScene::~GScene() {
	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {
		delete *iter;
	}
}

void GScene::AddObject(GObject* obj) {
	objects.push_back(obj);
	obj->SetScene(this);
}

void GScene::CalculateLights(Shader& shader) {
	if (lastUsedShader == &shader) return;
	lastUsedShader = &shader;
	for (int i = 0; i < NR_DIR_LIGHTS; ++i) {
		if (dirLights[i] == nullptr || !dirLights[i]->isActive) {
			std::string lightIdentifier = std::string("dirLights[") + std::to_string(i) + "]";
			shader.setVec3(lightIdentifier + ".ambient", 0, 0, 0);
			shader.setVec3(lightIdentifier + ".diffuse", 0, 0, 0);
			shader.setVec3(lightIdentifier + ".specular", 0, 0, 0);
		} else {
			dirLights[i]->SetUniform(i, shader);
		}
	}

	for (int i = 0; i < NR_POINT_LIGHTS; ++i) {
		if (true) {
			std::string lightIdentifier = std::string("pointLights[") + std::to_string(i) + "]";
			shader.setVec3(lightIdentifier + ".ambient", 0, 0, 0);
			shader.setVec3(lightIdentifier + ".diffuse", 0, 0, 0);
			shader.setVec3(lightIdentifier + ".specular", 0, 0, 0);
			shader.setFloat(lightIdentifier + ".constant", 1);
			shader.setFloat(lightIdentifier + ".linear", 0);
			shader.setFloat(lightIdentifier + ".quadratic", 0);
		} else {
			//dirLights[i]->SetUniform(i, shader);
		}
	}

	for (int i = 0; i < NR_SPOT_LIGHTS; ++i) {
		if (spotLights[i] == nullptr || !spotLights[i]->isActive) {
			std::string lightIdentifier = std::string("spotLights[") + std::to_string(i) + "]";
			shader.setVec3(lightIdentifier + ".ambient", 0, 0, 0);
			shader.setVec3(lightIdentifier + ".diffuse", 0, 0, 0);
			shader.setVec3(lightIdentifier + ".specular", 0, 0, 0);
			shader.setFloat(lightIdentifier + ".constant", 1);
			shader.setFloat(lightIdentifier + ".linear", 0);
			shader.setFloat(lightIdentifier + ".quadratic", 0);
		} else {
			spotLights[i]->SetUniform(i, shader);
		}
	}
}

void GScene::Update(float deltaTime) {
	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {
		if ((*iter)->isDeleted) {
			delete *iter;
			iter = objects.erase(iter);
			if (iter == objects.end()) {
				break;
			}
		} else if ((*iter)->isActive) {
			(*iter)->Update(deltaTime);
		}
	}
}

void GScene::Render() {
	if (!mainCamera) {
		return;
	}
	projection = mainCamera->ProjectionMatrix();
	view = mainCamera->ViewMatrix();
	lastUsedShader = nullptr;
}

}