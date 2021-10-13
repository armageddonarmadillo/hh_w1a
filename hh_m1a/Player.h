#pragma once
#include "Drawable.h"

class Player : public Drawable
{
public:
	bool grounded = false;
	Player(int x, int y);
	void move();
	void update();
};
