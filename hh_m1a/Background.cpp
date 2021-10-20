#include "Background.h"

Background::Background(CString path, int x, int y, int w, int h, double ss) : Drawable(path, x, y, w, h) {
	scrollspeed = ss;
}

void Background::draw(HDC c) {
	int rx = (int)((x - mpos) * scrollspeed) % w;

	image.SetTransparentColor(RGB(255, 174, 201));
	image.TransparentBlt(c, rx, y, w, h, 0, 0, w, h);
	image.TransparentBlt(c, rx - w, y, w, h, 0, 0, w, h);
	image.TransparentBlt(c, rx + w, y, w, h, 0, 0, w, h);
}