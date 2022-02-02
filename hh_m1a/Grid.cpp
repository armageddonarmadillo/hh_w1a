#include "Grid.h"

Grid::Grid(int w) {
	cell_maker(w);
	//for (int i = 0; i < 50; i++) fill(search(rand() % w, rand() % GROUND));
}

void Grid::draw(HDC context) {
	//create a brush with a specific color
	HBRUSH color = CreateSolidBrush(RGB(255, 0, 0));
	//pair context to crush
	SelectObject(context, color);
	//draw
	for (Cell* c : cells) {
		if (c->x < plx - 650 || c->x + c->w > plx + 650) continue;
		c->filled ? Rectangle(context, c->x - mpos, c->y, c->x + c->w - mpos, c->y + c->h)
			: (
				Rectangle(context, c->x - mpos, c->y, c->x + c->w - mpos, c->y + 1),
				Rectangle(context, c->x - mpos, c->y + c->h, c->x + c->w - mpos, c->y + c->h + 1),
				Rectangle(context, c->x - mpos, c->y, c->x + 1 - mpos, c->y + c->h),
				Rectangle(context, c->x + c->w - mpos, c->y, c->x + c->w + 1 - mpos, c->y + c->h)
				);
	}
	//pop or delete brush
	DeleteObject(color);
}

void Grid::cell_maker(int gw) {
	for (int y = 0; y < (GROUND / gcellh); y++) {
		for (int x = 0; x < (gw / gcellw); x++) {
			Cell* c = new Cell();
			c->x = x * gcellw;
			c->y = y * gcellh;
			cells.add(c);
		}
	}
}

Cell* Grid::search(int x, int y) {
	for (Cell* c : cells)
		if (c->x < x && x < c->x + c->w && c->y < y && y < c->y + c->h)
			return c;
}

void Grid::fill(Cell* c) {
	if (c == NULL) return;
	c->filled = true;
}