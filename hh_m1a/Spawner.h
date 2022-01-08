#pragma once
#include "Crab.h"

class Spawner
{
public:
	list<Crab*> crabs;
	int x, y, limit, counter = 0, delay;

	Spawner(int x, int y, int limit, int delay);

	void update(Combat* c, list<Box*> boxes, list<Platform*> platforms);
	void update_crabs(Combat* c, list<Box*> boxes, list<Platform*> platforms);
	void spawn_crab();
	void kicked_collision();
	void remove_inactive_crabs();
	void draw_crabs(HDC c);
};

