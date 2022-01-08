#pragma once
#include "Box.h"

class Platform
{
public:
	int xspeed, yspeed, sp, ep, dir;
	list<Box*> platform;
	Platform(int x, int y, int size, int limit, int speed);

	void update();
	void update_boxes();
	void draw_boxes(HDC context);
};

