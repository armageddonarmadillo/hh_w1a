#include "Platform.h"
Platform::Platform(int x, int y, int size, int limit, int speed) {
	for (int i = 0; i < size; i++)
		platform.add(new Box("SmallCrate.bmp", x + i * 32, y, 32, 32));
	sp = x;
	ep = x + limit;
	dir = limit > 0 ? 1 : limit < 0 ? -1 : 0;
	xspeed = speed * dir;
	yspeed = 0;
}

void Platform::update() {
	update_boxes();
	if (
		dir > 0 ? platform.front()->x <= sp || platform.back()->x + platform.back()->w >= ep :
		dir < 0 ? platform.front()->x >= sp || platform.back()->x + platform.back()->w <= ep :
		false
		) xspeed *= -1;
}

void Platform::update_boxes() {
	for (Box* b : platform) {
		b->xspeed = xspeed;
		b->update();
	}
}

void Platform::draw_boxes(HDC context) {
	for (Box* b : platform) b->draw(context);
}