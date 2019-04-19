#include "stdafx.h"

#ifndef __SPIKE_H__
#define	__SPIKE_H__

#include "GMonoPoly.h"

using namespace Glory;

class Spike : public GMonoPoly {
public:
	Spike();

	void Update(float deltaTime);
};

#endif