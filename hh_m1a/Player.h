#pragma once
#include "Combat.h"
#include "Box.h"
#include "Platform.h"

class Player : public Combat
{
public:
	bool grounded = false, facing_right = false,
		shooting = false, landed = false;
	Player(int x, int y);
	void move();
	void fire();
	void update_animations();
	void update(list<Box*> boxes, list<Platform*> platforms);
	void platform(list<Box*> boxes, list<Platform*> platforms);

	void moveright();
	void moveleft();
	void idleright();
	void idleleft();
	void jumpright();
	void jumpleft();
	void shootright();
	void shootleft();
};
