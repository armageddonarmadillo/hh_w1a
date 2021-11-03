#pragma once
#include "framework.h"

class Drawable
{
public:
	int x, y, w, h, px, py;
	int srcx, srcy, hw, hh, sc, cc, ec;
	int xspeed, yspeed;
	bool loop;
	CImage image;
	CString path;

	Drawable(CString path, int x, int y, int w, int h);
	void draw(HDC context);
	void animate();
	bool collides(Drawable* d);
};