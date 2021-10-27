#include "Player.h"

Player::Player(int x, int y) : Combat("ViktorTesla.bmp", x, y, 55, 46) {

}

void Player::move() {
	x += xspeed;
	y += yspeed;
	facing_right = xspeed != 0 ? xspeed > 0 ? true : false : facing_right;
	if (!grounded) yspeed += GRAVITY;
	if (grounded = y + h > GROUND) y = GROUND - h;

	if ((x - mpos < 50 && xspeed != 0) || (x - mpos > 600 && xspeed != 0)) mpos += xspeed;
}

void Player::update() {
	move();
	fire();
	update_animations();
	animate();
	update_bullets();
	clear_inactive_bullets();
}

void Player::fire() {
	if (shooting) bullets.add(new Bullet("VBullet.bmp", x + (facing_right ? w : 0), y + 10, 6, 6, PSPEED * 1.8 * (facing_right ? 1 : -1), 0));
}

void Player::update_animations() {
	//Animation Controller
	grounded ? xspeed == 0 ? shooting ?
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
