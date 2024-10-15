#include "stdafx.h"
#include "GModelManager.h"
#include "Model.h"

namespace Glory {

GModelManager* GModelManager::Instance() {
	static GModelManager instance;
	return &instance;
}

Model* GModelManager::Load(std::string path) {
	if (models.count(path) <= 0) {
		Model *newModel = new Model(const_cast<char*>(path.data()));
		models[path] = newModel;
	}
	return models[path];
}

void GModelManager::Unload(std::string path) {
	auto iter = models.find(path);
	if (iter != models.end()) {
		delete iter->second;
		models.erase(iter);
	}
}

void GModelManager::UnloadAll() {
	for (auto iter : models) {
		delete iter.second;
	}
	models.clear();
}

}