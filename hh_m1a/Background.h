#pragma once
#include "Drawable.h"

class Background : public Drawable
{
public:
	double scrollspeed;
	Background(CString path, int x, int y, int w, int h, double ss);
	void draw(HDC context);
};
