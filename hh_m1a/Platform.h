#pragma once
#include "Box.h"

class Platform
{
public:
	int xspeed, yspeed;
	list<Box*> platform;
	Platform(int x, int y, int size);

	void update();
	void update_boxes();
	void draw_boxes(HDC context);
};

