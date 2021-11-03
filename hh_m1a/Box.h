#pragma once
#include "Drawable.h"

class Box : public Drawable
{
public:
	Box(CString path, int x, int y, int w, int h);
	void update();
};

