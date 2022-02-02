#pragma once
#include "framework.h"

class Button
{
public:
	int x, y, w, h;
	COLORREF bgc, fgc;
	string label;
	bool hover = false, held = false;

	Button(string label, int x, int y, int w, int h, int r, int g, int b);
	void draw(HDC context);
	bool input(int x, int y, bool down);
	COLORREF inverse_color(COLORREF to_reverse);
	COLORREF lighten_color(COLORREF to_lighten);
	COLORREF darken_color(COLORREF to_darken);
};

