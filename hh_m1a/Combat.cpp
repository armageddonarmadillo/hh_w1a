#include "Combat.h"

Combat::Combat(CString path, int x, int y, int w, int h) :
	Drawable(path, x, y, w, h) {

}

void Combat::draw_bullets(HDC context) {
	for (Bullet* b : bullets) b->draw(context);
}

void Combat::update_bullets() {
	for (Bullet* b : bullets) b->update();
}

void Combat::clear_inactive_bullets() {
	for (Bullet* b : bullets)
		if (!b->active) {
			bullets.remove(b);
			break;
		}
}

void Combat::bullet_collision(Drawable* d) {
	for (Bullet* b : bullets) if (b->collides(d)) {
		b->active = false;
		d->durability--;
	}
}