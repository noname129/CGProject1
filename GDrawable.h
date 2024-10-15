#include "stdafx.h"

#ifndef	__GDRAWABLE_H_
#define __GDRAWABLE_H_

#include "GObject.h"
#include "shader.h"

namespace Glory {

class GDrawable : public GObject {
protected:
	Shader *shader;
	
public:
	GDrawable();
	GDrawable(Shader* shader);
	virtual ~GDrawable();

	Shader* GetShader() { return shader; }
	void SetShader(Shader* shader);

	virtual void Update(float deltaTime);
	virtual void Render();

	static Shader defaultShader;
};

}

#endif