#include "Platform.h"
Platform::Platform(int x, int y, int size) {
	for (int i = 0; i < size; i++)
		platform.add(new Box("SmallCrate.bmp", x + i * 32, y, 32, 32));

	xspeed = 5;
	yspeed = 0;
}

void Platform::update() {
	update_boxes();
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