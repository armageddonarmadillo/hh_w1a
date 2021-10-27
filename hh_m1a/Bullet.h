#pragma once
#include "Drawable.h"

class Bullet : public Drawable
{
public:
	int dt = 0, md = 300;
	bool active = true;

	Bullet(CString path, int x, int y, int w, int h, int xs, int ys);

	void move();
	void update();
};

