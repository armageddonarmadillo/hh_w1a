#include "Player.h"

Player::Player(int x, int y) : Drawable("ViktorTesla.bmp", x, y, 55, 46) {

}

void Player::move() {
	x += xspeed;
	y += yspeed;
	if (!grounded) yspeed += GRAVITY;
	if (grounded = y + h > GROUND) y = GROUND - h;

	if ((x - mpos < 50 && xspeed != 0) || (x - mpos > 600 && xspeed != 0)) mpos += xspeed;
}

void Player::update() {
	move();
}