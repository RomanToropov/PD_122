#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<windowsx.h>
#include<stdio.h>
#include<CommCtrl.h>
#include"resource.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define IDC_STATIC_RESOLUTION	1000

TOOLINFO g_toolItem = { 0 };
HWND g_hwndTrackingTT;
BOOL g_TrackingMouse = FALSE;
TRACKMOUSEEVENT tme = { sizeof(TRACKMOUSEEVENT) };

CONST CHAR g_szClassName[] = "MyWindowClass";
CONST CHAR g_szTitle[] = "My first Window";
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID CreateTooltTipForRect(HWND hwnd);
HWND CreateTrackingTooltip(HWND hwnd);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.style = 0;
	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_STAR));
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_MOON));
	wc.hIcon = (HICON)LoadImage(hInstance, "umbrella.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "raining.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);
	INT window_width = screen_width - screen_width / 4;
	INT window_height = screen_height - screen_height / 4;
	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_height / 8;
	HWND hwnd = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		g_szClassName,		//Имя класса окна
		g_szTitle,		//Заголовок окна
		WS_OVERLAPPEDWINDOW,//Для главного окна программы всегда задается такой стиль
		window_start_x, window_start_y,//Начальная позиция окна на экране
		window_width, window_height,//Исходный размер окна
		NULL,	//Родительское окно отсутствует
		NULL,	//Меню тоже отсутствует
		hInstance,	//EXE-файл окна
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);//Задаем режим отображения окна (развернуто на весь экран, светнуто на панель задач, и т.д.)
	UpdateWindow(hwnd);//Прорисовка окна

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		/*RECT rect;
		GetClientRect(hwnd, &rect);
		CreateWindowEx
		(
			NULL,
			"STATIC",
			"ScreenResolution",
			WS_CHILD | WS_VISIBLE,
			rect.top, rect.left,
			520, 15,
			hwnd,
			(HMENU)IDC_STATIC_RESOLUTION,
			GetModuleHandle(NULL),
			NULL
		);*/
		//Tooltip - Всплывающая подсказка:
		InitCommonControls();
		//CreateTooltTipForRect(hwnd);
		g_hwndTrackingTT = CreateTrackingTooltip(hwnd);
		return TRUE;
	}
	break;
	case WM_MOUSELEAVE:
	{
		SendMessage(g_hwndTrackingTT, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)&g_toolItem);
		g_TrackingMouse = FALSE;
		return FALSE;
	}
	break;
	case WM_MOUSEMOVE:
	{
		//CreateTooltTipForRect(hwnd);
		//SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&ti);
		static int oldX, oldY;
		int newX, newY;
		if (!g_TrackingMouse)
		{
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hwnd;

			TrackMouseEvent(&tme);

			SendMessage(g_hwndTrackingTT, TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)&g_toolItem);
			g_TrackingMouse = TRUE;
		}
		newX = GET_X_LPARAM(lParam);
		newY = GET_Y_LPARAM(lParam);

		if ((newX != oldX) || (newY != oldY))
		{
			oldX = newX;
			oldY = newY;

			CHAR coords[18];
			sprintf(coords, "%dx%d", newX, newY);

			g_toolItem.lpszText = coords;
			SendMessage(g_hwndTrackingTT, TTM_SETTOOLINFO, 0, (LPARAM)&g_toolItem);

			POINT pt = { newX, newY };
			ClientToScreen(hwnd, &pt);
			SendMessage(g_hwndTrackingTT, TTM_TRACKPOSITION, 0, (LPARAM)MAKELONG(pt.x+20, pt.y-20));
		}
		SendMessage(g_hwndTrackingTT, TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)&g_toolItem);
		return FALSE;
	}
	break;
	case WM_COMMAND:
		break;
	case WM_SIZE:
	case WM_MOVE:
	{
		CONST INT SIZE = 256;
		CHAR buffer[SIZE] = {};
		RECT rect;	//Прямоугольник
		GetWindowRect(hwnd, &rect);
		int window_start_x = rect.left;
		int window_start_y = rect.top;
		int window_width = rect.right - rect.left;
		int window_height = rect.bottom - rect.top;
		sprintf(buffer, "%s - position: %dx%d, size: %dx%d", g_szTitle, window_start_x, window_start_y, window_width, window_height);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);
		//MessageBox(hwnd, buffer, "", MB_OK);
		//SendMessage(GetDlgItem(hwnd, IDC_STATIC_RESOLUTION), WM_SETTEXT, 0, (LPARAM)buffer);
	}
	break;

	case WM_CLOSE:
		if (MessageBox(hwnd, "Вы действительно хотите выйти?", "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
VOID CreateTooltTipForRect(HWND hwnd)
{
	HWND hwndTT = CreateWindowEx
	(
		WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
		TOOLTIPS_CLASS,
		NULL,
		WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,//WS_POPUP - всплывающее окно, TTS_NOPREFIX - игнорировать символ &, TTS_ALWAYSTIP - подсказка появляется даже над неактивным окном.
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		hwnd,
		NULL,
		GetModuleHandle(NULL),	//Получаем HINSTANCE (EXE-файл) программы
		NULL
	);
	if (hwndTT == NULL)
	{
		MessageBox(hwnd, "Tooltip window creation failed", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	SetWindowPos(hwndTT, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	TOOLINFO ti;
	ZeroMemory(&ti, sizeof(TOOLINFO));
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_SUBCLASS;
	ti.hwnd = hwnd;
	ti.hinst = GetModuleHandle(NULL);
	ti.lpszText = (LPSTR)"This is a tooltip";
	GetClientRect(hwnd, &ti.rect);
	SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&ti);
}
HWND CreateTrackingTooltip(HWND hwnd)
{
	// Create a tooltip.
	HWND hwndTT = CreateWindowEx
	(
		WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
		WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hwnd, NULL, GetModuleHandle(NULL), NULL
	);

	if (!hwndTT)
	{
		MessageBox(NULL, "Tooltip Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return NULL;
	}
	/*SetWindowPos(hwndTT, HWND_TOPMOST, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);*/

		// Set up the tool information. In this case, the "tool" is the entire parent window.
	g_toolItem.cbSize = sizeof(TOOLINFO);
	g_toolItem.uFlags = TTF_IDISHWND | TTF_TRACK | TTF_ABSOLUTE;
	g_toolItem.hwnd = hwnd;
	g_toolItem.hinst = GetModuleHandle(NULL);
	//g_toolItem.lpszText = pText;
	g_toolItem.lpszText = (LPSTR)TEXT("Tracking Tooltip");
	g_toolItem.uId = (UINT_PTR)hwnd;

	GetClientRect(hwnd, &g_toolItem.rect);

	// Associate the tooltip with the tool window.
	SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&g_toolItem);
	//SendMessage(hwndTT, TTM_ACTIVATE, (WPARAM)TRUE, 0);	//my
	return hwndTT;
}