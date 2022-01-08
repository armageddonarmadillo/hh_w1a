#include "Crab.h"

Crab::Crab(int x, int y) :
	Enemy("SkullCrab.bmp", x, y, 28, 36) {
	dirdelay = 30;
	md = 400;
	xspeed = -ESPEED;
	durability = 5;
}

void Crab::move() {
	if (ko) return;
	px = x;
	py = y;
	dircount > dirdelay ? xspeed = ESPEED * (plx > x ? 1 : plx < x ? -1 : 1), dircount = 0 : dircount++;
	x += xspeed;
	y += yspeed;
	facing_right = xspeed != 0 ? xspeed > 0 ? true : false : facing_right;
	if (!grounded && !landed) yspeed += GRAVITY;
	if (grounded = y + h > GROUND) y = GROUND - h;
}

void Crab::koed(Combat* c) {
	if (!ko) return;
	xspeed = kicked ? xspeed : 0;
	yspeed = kicked ? yspeed : 0;
	if (!grounded && !landed) yspeed += GRAVITY;
	if ((c->collides(this) || drop) && !kicked) {
		kicked = true;
		yspeed = -ESPEED * 3;
		xspeed = ESPEED * (plx > x ? -1 : plx < x ? 1 : 1) * 2;
	}
	x += xspeed;
	y += yspeed;
	dt += abs(xspeed);
	if (grounded = y + h > GROUND && !(drop = dt > md || drop)) y = GROUND - h;
	active = y < 650;
}

void Crab::fire() {
	bullets.add(new Bullet("GreenFire.bmp", x + (facing_right ? w : 0), py + 10, 6, 6, ESPEED * 1.8 * (facing_right ? 1 : -1), 0));
}

void Crab::update_animations() {
	ko ? facing_right ? koright() : koleft() :
		facing_right ? moveright() : moveleft();
}

void Crab::update(Combat* c, list<Box*> boxes, list<Platform*> platforms) {
	ko = durability <= 0;
	move();
	platform(boxes, platforms);
	koed(c);
	!ko ? counter > delay ? fire(), counter = 0 : counter++ : 0;
	update_bullets();
	check_combat(c);
	clear_inactive_bullets();
	update_animations();
	animate();
}

void Crab::check_combat(Combat* c) {
	bullet_collision(c);
	c->bullet_collision(this);
}

void Crab::platform(list<Box*> boxes, list<Platform*> platforms) {
	//static box collision
	for (Box* b : boxes)
		if (b->collides(this)) {
			if (py + hh < b->py) {
				landed = true;
				y = b->py - hh - 1;
			}
			else if (px + hw < b->px) { x = b->px - hw - 1; xspeed *= -1; }
			else if (px > b->x + b->hw) { x = b->x + b->hw + 1; xspeed *= -1; }
			else if (py > b->y + b->hh) { y = b->y + b->hh + 1; yspeed = 0; }
			return;
		}
		else landed = false;

	//moving platform collision
	for (Platform* p : platforms)
		for (Box* b : p->platform)
			if (b->collides(this)) {
				if (py + hh < b->py) {
					landed = true;
					y = b->py - hh - 1;
					x += b->xspeed;
				}
				else if (px + hw < b->px) x = b->x - hw - 1;
				else if (px > b->px + b->hw) x = b->x + b->hw + 1;
				else if (py > b->py + b->hh) { y = b->y + b->hh + 1; yspeed = 0; }
				return;
			}
			else landed = false;
}

void Crab::moveright() {
	srcx = 0;
	srcy = 36;
	w = 28;
	h = 36;
	sc = 0;
	ec = 9;
	loop = true;
}

void Crab::moveleft() {
	srcx = 0;
	srcy = 0;
	w = 28;
	h = 36;
	sc = 0;
	ec = 9;
	loop = true;
}

void Crab::koright() {
	srcx = 0;
	srcy = 114;
	w = 28;
	h = 25;
	sc = 0;
	ec = 0;
	loop = false;
}

void Crab::koleft() {
	srcx = 0;
	srcy = 80;
	w = 28;
	h = 25;
	sc = 0;
	ec = 0;
	loop = false;
}
