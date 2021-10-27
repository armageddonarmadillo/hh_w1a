#pragma once
#include "Drawable.h"
#include "Bullet.h"

class Combat : public Drawable
{
public:
	list<Bullet*> bullets;

	Combat(CString path, int x, int y, int w, int h);
	void draw_bullets(HDC context);
	void update_bullets();
	void clear_inactive_bullets();
};
