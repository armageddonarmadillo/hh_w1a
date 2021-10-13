#include "Player.h"

Player::Player(int x, int y) : Drawable("ViktorTesla.bmp", x, y, 55, 46) {

}

void Player::move() {
	x += xspeed;
	y += yspeed;
	if (!grounded) yspeed += GRAVITY;
	if (grounded = y + h > GROUND) y = GROUND - h;
}

void Player::update() {
	move();
}