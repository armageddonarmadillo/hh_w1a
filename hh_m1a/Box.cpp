#include "Box.h"

Box::Box(CString path, int x, int y, int w, int h) :
	Drawable(path, x, y, w, h) {

}

void Box::update() {
	px = x;
	py = y;
	x += xspeed;
	y += yspeed;
}