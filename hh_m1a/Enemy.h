#pragma once
#include "Combat.h"
#include "Box.h"
#include "Platform.h"

class Enemy : public Combat
{
public:
	int counter = 0, delay = 30;
	bool grounded = false, facing_right = false,
		shooting = false, landed = false,
		active = true, ko = false;

	Enemy(CString path, int x, int y, int w, int h) :
		Combat(path, x, y, w, h) {}

	virtual void move() = 0;
	virtual void fire() = 0;
	virtual void update_animations() = 0;
	virtual void update(Combat* c, list<Box*> boxes, list<Platform*> platforms) = 0;
	virtual void platform(list<Box*> boxes, list<Platform*> platforms) = 0;
};

