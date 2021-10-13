#include "Drawable.h"

Drawable::Drawable(CString p, int x, int y, int w, int h) {
	Drawable::x = x;
	Drawable::y = y;
	Drawable::w = w;
	Drawable::h = h;
	xspeed = 0;
	yspeed = 0;

	image.Load("./assets/" + p);
}

void Drawable::draw(HDC c) {
	//Sets the specific pink color in our images to transparent
	image.SetTransparentColor(RGB(255, 174, 201));

	//Draws to the screen
	image.TransparentBlt(c, x, y, w, h, 0, 0, w, h);
}