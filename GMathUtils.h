#include "stdafx.h"

#ifndef __GMATHUTILS_H__
#define	__GMATHUTILS_H__

#include <random>

namespace Glory {

namespace MathUtil {

float RandomRange(float a, float b);

float FaceTo2D(glm::vec2& from, glm::vec2& to);

glm::vec2 NDCToScreen(glm::vec2 ndc);

glm::vec2 NDCToScreen(float x, float y);

}

}

#endif