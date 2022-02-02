// hh_m1a.cpp : Defines the entry point for the application.
#include "framework.h"
#include "hh_m1a.h"
#include "Game.h"
#include "Grid.h"
#include "Start.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// CONTROL VARIABLES
HDC buffer_context;
int mpos = 0, plx = 0, php = 0;
bool started = false, paused = false, lost = false;

// GAME VARIABLES
Start* start = new Start();
Game* game = new Game();
Grid* grid = new Grid(6400);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Custom method forward declarations
void				setup_buffer();
void				draw_buffer(HWND hWnd);

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
		game->inputs(wParam, false);
	}
	break;
	case WM_KEYUP:
	{
		game->inputs(wParam, true);
	}
	break;
	case WM_MOUSEMOVE:
	{
		POINT p;
		if (GetCursorPos(&p)) if (!ScreenToClient(hWnd, &p)) break;
		//DO MOUSEMOVE LOGIC BELOW THIS LINE
		start->input(p.x, p.y, false);

	}
	break;
	case WM_RBUTTONDOWN:
	{

	}
	break;
	case WM_LBUTTONDOWN:
	{
		POINT p;
		if (GetCursorPos(&p)) if (!ScreenToClient(hWnd, &p)) break;
		start->input(p.x, p.y, true);
		//grid->fill(grid->search(p.x + mpos, p.y));
	}
	break;
	case WM_LBUTTONUP:
	{
		POINT p;
		if (GetCursorPos(&p)) if (!ScreenToClient(hWnd, &p)) break;
		if (!started) started = start->input(p.x, p.y, false);
	}
	break;
	case WM_TIMER:
	{
		if (started) game->update();
		//ADD ABOVE THIS LINE
		PostMessage(hWnd, WM_PAINT, 0, 0);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		if (!started) start->render(buffer_context);
		else game->render(buffer_context);
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
