#pragma once
#include "framework.h"

class Health
{
public:
	int x, y, w, h, limit;
	COLORREF bgc, fgc;

	Health();
	void draw(HDC context);
	void update();
};

