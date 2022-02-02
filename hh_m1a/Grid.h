#pragma once
#include "framework.h"

struct Cell {
	int x, y, w = gcellw, h = gcellh;
	bool filled = false;
};

class Grid {
public:
	int ix = 0, iy = 0;
	list<Cell*> cells;

	Grid(int w);

	void draw(HDC context);

	void cell_maker(int gw);
	Cell* search(int x, int y);
	void fill(Cell* c);
};
