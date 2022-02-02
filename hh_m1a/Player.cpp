#include "Player.h"

Player::Player(int x, int y) : Combat("ViktorTesla.bmp", x, y, 54, 42) {
	durability = 25;
	php = durability;
}

void Player::move() {
	px = x;
	py = y;
	x += xspeed;
	y += yspeed;
	plx = x;
	facing_right = xspeed != 0 ? xspeed > 0 ? true : false : facing_right;
	if (!grounded && !landed) yspeed += GRAVITY;
	if (grounded = y + h > GROUND) y = GROUND - h;
	if ((x - mpos < 50 && xspeed != 0) || (x - mpos > 600 && xspeed != 0)) mpos += xspeed;
	//lineout("Player's adjusted positon is: " << x - mpos);
}

void Player::update(list<Box*> boxes, list<Platform*> platforms) {
	php = durability;
	if (y > 600) durability = 0;
	move();
	fire();
	platform(boxes, platforms);
	clear_inactive_bullets();
	update_bullets();
	update_animations();
	animate();
}

void Player::platform(list<Box*> boxes, list<Platform*> platforms) {
	//static box collision
	for (Box* b : boxes)
		if (b->collides(this)) {
			if (py + hh < b->py) {
				landed = true;
				y = b->py - hh - 1;
				return;
			}
			else if (px + hw < b->px) x = b->px - hw - 1;
			else if (px > b->x + b->hw) x = b->x + b->hw + 1;
			else if (py > b->y + b->hh) { y = b->y + b->hh + 1; yspeed = 0; }

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
					mpos += b->xspeed;
				}
				else if (px + hw < b->px) x = b->x - hw - 1;
				else if (px > b->px + b->hw) x = b->x + b->hw + 1;
				else if (py > b->py + b->hh) { y = b->y + b->hh + 1; yspeed = 0; }
				return;
			}
			else landed = false;
}

void Player::fire() {
	if (shooting) bullets.add(new Bullet("VBullet.bmp", x + (facing_right ? w : 0), py + 10, 6, 6, PSPEED * 1.8 * (facing_right ? 1 : -1), 0));
}

void Player::update_animations() {
	//Animation Controller
	grounded || landed ? xspeed == 0 ? shooting ?
		facing_right ? shootright() : shootleft() :
		facing_right ? idleright() : idleleft() :
		facing_right ? moveright() : moveleft() :
		facing_right ? jumpright() : jumpleft();
}

void Player::moveright() {
	srcx = 52;
	srcy = 0;
	w = 54;
	h = 42;
	loop = true;
	ec = 8;
	sc = 1;
}

void Player::moveleft() {
	srcx = 52;
	srcy = 42;
	w = 54;
	h = 42;
	loop = true;
	ec = 8;
	sc = 1;
}

void Player::idleright() {
	srcx = 0;
	srcy = 0;
	w = 54;
	h = 42;
	loop = false;
	ec = 0;
	sc = 0;
}

void Player::idleleft() {
	srcx = 0;
	srcy = 42;
	w = 54;
	h = 42;
	loop = false;
	ec = 0;
	sc = 0;
}

void Player::jumpright() {
	srcx = 0;
	srcy = 86;
	w = 48;
	h = 56;
	loop = false;
	ec = 5;
	sc = 0;
}

void Player::jumpleft() {
	srcx = 0;
	srcy = 146;
	w = 48;
	h = 56;
	loop = false;
	ec = 5;
	sc = 0;
}

void Player::shootright() {
	srcx = 0;
	srcy = 199;
	w = 60;
	h = 38;
	loop = false;
	ec = 0;
	sc = 0;
}

void Player::shootleft() {
	srcx = 0;
	srcy = 237;
	w = 60;
	h = 38;
	loop = false;
	ec = 0;
	sc = 0;
}
