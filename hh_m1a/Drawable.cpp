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
	px = x;
	py = y;
	hw = w;
	hh = h;
	sc = 0;
	cc = 0;
	ec = 0;
	durability = 25;
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

bool Drawable::collides(Drawable* d) {
	return (x < d->x + d->hw && x + hw > d->x &&
		y < d->y + d->hh && y + hh > d->y);
}