#include "Button.h"

Button::Button(string label, int x, int y, int w, int h,
	int r, int g, int b) {
	Button::x = x;
	Button::y = y;
	Button::w = w;
	Button::h = h;
	Button::label = label;
	Button::bgc = COLORREF(RGB(r, g, b));
	Button::fgc = inverse_color(bgc);
}

void Button::draw(HDC context) {
	// Create objects 
	HBRUSH bg = CreateSolidBrush(held ? darken_color(bgc) : hover ? lighten_color(bgc) : bgc);
	std::wstring unbind_label = std::wstring(label.begin(), label.end());
	LPCWSTR text = unbind_label.c_str();
	RECT rect = { x, y, x + w, y + h };

	// Draw
	SelectObject(context, bg);
	Rectangle(context, rect.left, rect.top, rect.right, rect.bottom);

	HFONT f = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	LOGFONT lf;
	GetObject(f, sizeof(lf), &lf);
	lf.lfHeight = 50;
	//other properties
	HFONT nf = CreateFontIndirect(&lf);
	HFONT of = (HFONT)SelectObject(context, nf);
	SetBkMode(context, TRANSPARENT);
	SetTextColor(context, fgc);
	DrawText(context, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_CENTER);
	SelectObject(context, of);

	// Destroy
	DeleteObject(bg);
	DeleteObject(f);
	DeleteObject(nf);
	DeleteObject(of);
}

bool Button::input(int x, int y, bool down) {
	if (Button::x < x && x < Button::x + Button::w && Button::y < y && y < Button::y + Button::h) {
		hover = true;
		held = hover && down;
		return true;
	}
	hover = false;
	return false;
}

COLORREF Button::inverse_color(COLORREF to_reverse) {
	return COLORREF(
		RGB(
			255 - GetRValue(to_reverse),
			255 - GetGValue(to_reverse),
			255 - GetBValue(to_reverse)
		)
	);
}

COLORREF Button::lighten_color(COLORREF to_lighten) {
	return COLORREF(
		RGB(
			GetRValue(to_lighten) + 30 > 255 ? 255 : GetRValue(to_lighten) + 30,
			GetGValue(to_lighten) + 30 > 255 ? 255 : GetGValue(to_lighten) + 30,
			GetBValue(to_lighten) + 30 > 255 ? 255 : GetBValue(to_lighten) + 30
		)
	);
}

COLORREF Button::darken_color(COLORREF to_darken) {
	return COLORREF(
		RGB(
			GetRValue(to_darken) - 30 < 0 ? 0 : GetRValue(to_darken) - 30,
			GetGValue(to_darken) - 30 < 0 ? 0 : GetGValue(to_darken) - 30,
			GetBValue(to_darken) - 30 < 0 ? 0 : GetBValue(to_darken) - 30
		)
	);
}