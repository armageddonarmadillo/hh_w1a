// hh_m1a.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "hh_m1a.h"
#include "Drawable.h"
#include "Player.h"
#include "Background.h"
#include "Box.h"
#include "Platform.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// GAME VARIABLES
Player* mc = new Player(100, 100);
Background* bg = new Background("Background3.jpg", 0, 0, 5118, 800, 0.5);
Background* ground = new Background("Ground.bmp", 0, GROUND, 774, 128, 1);

// GAME LISTS
list<Box*> boxes;
list<Platform*> platforms;


// CONTROL VARIABLES
HDC buffer_context;
int mpos = 0;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Custom method forward declarations
void	setup_buffer();
void	draw_buffer(HWND hWnd);

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
		250, 250, 700, 550, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	setup_buffer();
	SetTimer(hWnd, 1, 17, NULL);
	//big boxes
	for (int i = 0; i < 5; i++) boxes.add(new Box("Crate.bmp", 200 + i * 64, GROUND - 64, 64, 64));
	//small boxes
	for (int i = 0; i < 5; i++) boxes.add(new Box("SmallCrate.bmp", 600 + i * 32, GROUND - 32 - i * 32, 32, 32));
	//platforms
	platforms.add(new Platform(400, 200, 3));
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
		mc->update(boxes);
		for (Platform* p : platforms) p->update();
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
		mc->draw(buffer_context);
		mc->draw_bullets(buffer_context);
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