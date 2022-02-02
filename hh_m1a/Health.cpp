#include "Health.h"

Health::Health() {
	Health::x = 15;
	Health::y = 15;
	Health::w = 10;
	Health::h = 100;
	Health::limit = php;
	Health::bgc = COLORREF(RGB(200, 10, 10));
	Health::fgc = COLORREF(RGB(10, 200, 10));
}

void Health::draw(HDC context) {
	//Create objects
	HBRUSH bg = CreateSolidBrush(bgc);
	HBRUSH fg = CreateSolidBrush(fgc);
	RECT rect = { x, y, x + w, y + h };

	//Draw
	SelectObject(context, fg);
	Rectangle(context, rect.left, rect.top, rect.right, rect.bottom);

	SelectObject(context, bg);
	Rectangle(context, rect.left, rect.top, rect.right, rect.top + (100 - (h / limit) * php));

	//Destroy
	DeleteObject(bg);
	DeleteObject(fg);
}

void Health::update() {

}