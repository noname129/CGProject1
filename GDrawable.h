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
	virtual ~GDrawable();

	virtual void Update(float deltaTime);
	virtual void Render();
};

}

#endif