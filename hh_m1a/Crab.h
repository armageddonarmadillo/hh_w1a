#pragma once
#include "Enemy.h"

class Crab : public Enemy
{
public:
	Crab(int x, int y);
	int dircount = 0, dirdelay, dt = 0, md;
	bool kicked = false, drop = false;

	void move();
	void koed(Combat* c);
	void fire();
	void update_animations();
	void update(Combat* c, list<Box*> boxes, list<Platform*> platforms);
	void platform(list<Box*> boxes, list<Platform*> platforms);
	void check_combat(Combat* c);
	void moveright();
	void moveleft();
	void koright();
	void koleft();
};

