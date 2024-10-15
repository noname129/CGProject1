#include "stdafx.h"

#ifndef __GMODELMANAGER_H__
#define	__GMODELMANAGER_H__

class Model;

namespace Glory {

class GModelManager {
private:
	std::map<std::string, Model*> models;

public:
	static GModelManager* Instance();

	Model* Load(std::string path);

	void Unload(std::string path);
	void UnloadAll();
};

}

#endif