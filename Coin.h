#include "stdafx.h"

#ifndef __COIN__H_
#define	__COIN__H_

#include "GPolyhedron.h"

using namespace Glory;

class Coin : public GPolyhedron {
private:
	static const int edgeCount;

public:
	GObject *player;
	Coin();

	void Update(float deltaTime);
};

#endif