#include "Bullet.h"

Bullet::Bullet(CString path, int x, int y, int w, int h, int xs, int ys) :
	Drawable(path, x, y, w, h) {
	xspeed = xs;
	yspeed = ys;
}

void Bullet::move() {
	x += xspeed;
	y += yspeed;
}

void Bullet::update() {
	move();
	dt += abs(xspeed);
	active = dt < md;
}