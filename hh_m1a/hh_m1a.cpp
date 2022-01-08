// hh_m1a.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "hh_m1a.h"
#include "Drawable.h"
#include "Player.h"
#include "Background.h"
#include "Box.h"
#include "Platform.h"
#include "Enemy.h"
#include "Crab.h"
#include "Spawner.h"
#include "Grid.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// GAME VARIABLES
Grid* grid = new Grid(6400);
Player* mc = new Player(100, 100);
Background* bg = new Background("Background3.jpg", 0, 0, 5118, 800, 0.5);
Background* ground = new Background("Ground.bmp", 0, GROUND, 774, 128, 1);

// GAME LISTS
list<Box*> boxes;
list<Platform*> platforms;
list<Enemy*> enemies;
list<Spawner*> spawners;


// CONTROL VARIABLES
HDC buffer_context;
int mpos = 0;
int plx = 0;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Custom method forward declarations
void				setup_buffer();
void				draw_buffer(HWND hWnd);
list<list<string>>	load_level(CString lvl);
void				build_level(list<list<string>> lvl);
void				start_level(CString lvl);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_HHM1A, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HHM1A));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HHM1A));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_HHM1A);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		1920 / 2 - gsw / 2, 1080 / 2 - gsh / 2, gsw, gsh, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	start_level("level1.txt");
	setup_buffer();
	SetTimer(hWnd, 1, 17, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam) {
		case 0x41: // A
			mc->xspeed = -PSPEED;
			break;
		case 0x44: // D
			mc->xspeed = PSPEED;
			break;
		case 0x53: // S
			// WILL IMPLEMENT LATER
			break;
		case 0x57: // W
			if (mc->grounded || mc->landed) mc->yspeed = -PSPEED * 2;
			break;
		case VK_SPACE:
			mc->shooting = true;
			break;
		}
	}
	break;
	case WM_KEYUP:
	{
		switch (wParam) {
		case 0x41: // A
			mc->xspeed = 0;
			break;
		case 0x44: // D
			mc->xspeed = 0;
			break;
		case 0x53: // S
			// WILL IMPLEMENT LATER
			break;
		case 0x57: // W
			// WILL IMPLEMENT LATER
			break;
		case VK_SPACE:
			mc->shooting = false;
			break;
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		POINT p;
		if (GetCursorPos(&p))
			if (ScreenToClient(hWnd, &p)) {
				//drawable->x = p.x;
				//drawable->y = p.y;
			}
	}
	break;
	case WM_RBUTTONUP:
	{

	}
	break;
	case WM_LBUTTONUP:
	{

	}
	break;
	case WM_TIMER:
	{
		mc->update(boxes, platforms);
		for (Platform* p : platforms) p->update();
		for (Enemy* e : enemies) e->update(mc, boxes, platforms);
		for (Spawner* s : spawners) s->update(mc, boxes, platforms);
		//ADD ABOVE THIS LINE
		PostMessage(hWnd, WM_PAINT, 0, 0);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		bg->draw(buffer_context);
		ground->draw(buffer_context);
		for (Box* b : boxes) b->draw(buffer_context);
		for (Platform* p : platforms) p->draw_boxes(buffer_context);
		for (Enemy* e : enemies) e->draw(buffer_context);
		for (Enemy* e : enemies) e->draw_bullets(buffer_context);
		for (Spawner* s : spawners) s->draw_crabs(buffer_context);
		mc->draw(buffer_context);
		mc->draw_bullets(buffer_context);
		grid->draw(buffer_context);
		draw_buffer(hWnd);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void setup_buffer() {
	HDC temp = GetDC(0);									//context of nothing
	HBITMAP bmp = CreateCompatibleBitmap(temp, 800, 600);	//create an image out of temp context
	buffer_context = CreateCompatibleDC(temp);				//initialize buffer context using temp context
	SelectObject(buffer_context, bmp);						//bind image to buffer context
	ReleaseDC(0, temp);										//destroy object to release memory
}

void draw_buffer(HWND hWnd) {
	HDC temp = GetDC(hWnd);
	TransparentBlt(temp, 0, 0, 700, 550, buffer_context, 0, 0, 700, 550, RGB(255, 174, 201));
	DeleteDC(temp);
}

list<list<string>> load_level(CString lvl) {
	std::ifstream file("./levels/" + lvl);
	string str;
	list<string> lines;
	list<list<string>> level;

	while (std::getline(file, str)) lines.add(str);

	string de = "|"; //setting delimiter to pipe character NOT L or I
	list<string> elements;
	size_t p = 0;
	for (string s : lines) {
		while ((p = s.find(de)) != string::npos) {
			elements.add(s.substr(0, p));
			s.erase(0, p + de.length());
		}
		level.add(elements);
		elements.clear();
	}
	return level;
}

void build_level(list<list<string>> lvl) {
	int r = 0, c = 0; //row in lvl, column in lvl
	for (list<string> line : lvl) {
		for (string s : line) {
			if (s == "[b]") boxes.add(new Box("SmallCrate.bmp", c * gcellw, r * gcellh, gcellw, gcellh));
			if (s == "[W]") boxes.add(new Box("woodblock.png", c * gcellw, r * gcellh, gcellw, gcellh));
			if (s == "[I]") boxes.add(new Box("iceblock.png", c * gcellw, r * gcellh, gcellw, gcellh));
			if (s == "[T]") boxes.add(new Box("toxicblock.png", c * gcellw, r * gcellh, gcellw, gcellh));
			if (s == "[L]") boxes.add(new Box("lavablock.png", c * gcellw, r * gcellh, gcellw, gcellh));
			if (s == "[B]") boxes.add(new Box("Crate.bmp", c * gcellw, r * gcellh, gcellw * 2, gcellh * 2));
			if (s == "[S]") spawners.add(new Spawner(c * gcellw, r * gcellh, 2, 150));
			if (s == "[K]") enemies.add(new Crab(c * gcellw, r * gcellh));
			if (s == "[P]") {
				mc = new Player(c * gcellw, r * gcellh);
				mpos = mc->x - 100;
			}

			/*END COLS*/ if (c++ == line.size() - 1) c = 0;
		}
		/*END ROWS*/ if (r++ == lvl.size() - 1) r = 0;
	}
}

void start_level(CString lvl) {
	build_level(load_level(lvl));
}