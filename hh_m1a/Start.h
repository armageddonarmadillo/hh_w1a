#pragma once
#include "framework.h"
#include "Button.h"

class Start
{
public:
	Button* button;
	Start();
	bool input(int x, int y, bool down);
	void render(HDC context);
};

