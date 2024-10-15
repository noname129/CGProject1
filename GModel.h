#include "stdafx.h"

#ifndef __GMODEL_H__
#define	__GMODEL_H__

#include "GDrawable.h"

class Model;

namespace Glory {

class GModel : public GDrawable {
private:
	std::string path;
	Model *model;

public:
	GModel(std::string path);
	GModel(std::string path, Shader* shader);

	void Render();
};

}

#endif