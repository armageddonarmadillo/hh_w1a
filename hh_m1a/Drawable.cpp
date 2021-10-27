#include "Drawable.h"

Drawable::Drawable(CString p, int x, int y, int w, int h) {
	Drawable::x = x;
	Drawable::y = y;
	Drawable::w = w;
	Drawable::h = h;
	xspeed = 0;
	yspeed = 0;
	srcx = 0;
	srcy = 0;
	hw = w;
	hh = h;
	sc = 0;
	cc = 0;
	ec = 0;
	loop = false;

	image.Load("./assets/" + p);
}

void Drawable::draw(HDC c) {
	//Sets the specific pink color in our images to transparent
	image.SetTransparentColor(RGB(255, 174, 201));

	//Draws to the screen
	image.TransparentBlt(c, x - mpos, y, w, h, srcx, srcy, w, h);
}

void Drawable::animate() {
	cc = cc >= ec ? loop ? sc : ec : ++cc;
	srcx = cc * w;
}