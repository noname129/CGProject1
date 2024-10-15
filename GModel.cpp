#include "stdafx.h"
#include "GModel.h"
#include "GModelManager.h"
#include "Model.h"

namespace Glory {

GModel::GModel(std::string path) : GDrawable(), path(path) {
	model = GModelManager::Instance()->Load(path);
}

GModel::GModel(std::string path, Shader* shader) : GDrawable(shader), path(path) {
	model = GModelManager::Instance()->Load(path);
}

void GModel::Render() {
	GDrawable::Render();
	model->Draw(shader);
}

}