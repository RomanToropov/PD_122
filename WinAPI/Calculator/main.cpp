﻿#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include"resource.h"


CONST UINT start_x = 10;
CONST UINT start_y = 70;
CONST UINT i_btn_size = 50;	//Размер кнопки
CONST UINT interval = 2;		//Интервал между кнопками

CONST UINT WINDOW_WIDTH = 293;//(i_btn_size+interval)*5+start_x*3;
CONST UINT WINDOW_HEIGHT = 324;

DOUBLE a, b;//Операнды.
INT s;		//Sign - знак операции.
BOOL stored = FALSE;	//Показывает, результат уже сохранен, или нет.

CONST CHAR g_szClassName[] = "Calculator";
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = (HICON)LoadImage(hInstance, "calc8.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "calc8.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = g_szClassName;
	wc.lpszMenuName = NULL;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}


	HWND hwnd = CreateWindowEx
	(
		NULL,	//exStyles
		g_szClassName,//Window class
		g_szClassName,//Window title
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,//Главное окно, со строкой заголовка, не изменяется по размеру.
		CW_USEDEFAULT, CW_USEDEFAULT,//Position
		WINDOW_WIDTH, WINDOW_HEIGHT,//Size
		NULL,	//Parent
		NULL,	//Menu
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

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
		/////////////////////////////////////////////////////////////////////
		////////////////////		Create display		/////////////////////
		/////////////////////////////////////////////////////////////////////
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",	//Window class for EditControl
			NULL,//Text
			WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY | ES_NUMBER | WS_BORDER,
			10, 10,
			(WINDOW_WIDTH - 35), i_btn_size,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);

		/////////////////////////////////////////////////////////////////////
		////////////////////		Create buttons		/////////////////////
		/////////////////////////////////////////////////////////////////////

		/*UINT start_x = 10;
		UINT start_y = 70;*/
		//UINT i_btn_size = 50;	//Размер кнопки
		//UINT interval = 2;		//Интервал между кнопками

		INT		digit = 1;
		CHAR	sz_digit[5];
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < 3; j++)
			{
				CreateWindowEx
				(
					NULL, "Button", _itoa(digit, sz_digit, 10),
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					start_x + (i_btn_size + interval)*j, start_y + (i_btn_size + interval)*i,
					i_btn_size, i_btn_size,
					hwnd, (HMENU)(IDC_BTN_0 + digit),
					GetModuleHandle(NULL), NULL
				);
				digit++;
			}
		}
		//							Zero & Point
		CreateWindowEx
		(
			NULL, "Button", "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x, start_y + (i_btn_size + interval) * 3,
			i_btn_size * 2 + interval, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_0), GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", ".", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 2, start_y + (i_btn_size + interval) * 3,
			i_btn_size, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_POINT), GetModuleHandle(NULL), NULL
		);

		//					Operations:
		CreateWindowEx
		(
			NULL, "Button", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 3, start_y + (i_btn_size + interval) * 0, i_btn_size, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_DIVISION), GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 3, start_y + (i_btn_size + interval) * 1, i_btn_size, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_MULTIPLICATION), GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 3, start_y + (i_btn_size + interval) * 2, i_btn_size, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_MINUS), GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 3, start_y + (i_btn_size + interval) * 3, i_btn_size, i_btn_size,
			hwnd, (HMENU)(IDC_BTN_PLUS), GetModuleHandle(NULL), NULL
		);

		CreateWindowEx
		(
			NULL, "Button", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 4, start_y,
			i_btn_size, i_btn_size * 2 + interval,
			hwnd, (HMENU)(IDC_BTN_CLEAR), GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			start_x + (i_btn_size + interval) * 4, start_y + (i_btn_size + interval) * 2,
			i_btn_size, i_btn_size * 2 + interval,
			hwnd, (HMENU)(IDC_BTN_EQUAL), GetModuleHandle(NULL), NULL
		);

		/*CHAR sz_focus_window[256]{};
		SendMessage(GetFocus(), WM_GETTEXT, 256, (LPARAM)sz_focus_window);
		MessageBox(hwnd, _itoa((INT)GetFocus(), sz_focus_window, 10), "Info", MB_OK);*/
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) >= IDC_BTN_0 && LOWORD(wParam) <= IDC_BTN_9 || LOWORD(wParam) == IDC_BTN_POINT)
		{
			if (stored)
			{
				SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)"");
				stored = FALSE;
			}
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (LOWORD(wParam)==IDC_BTN_POINT && strchr(sz_buffer, '.'))break;
			CHAR sz_digit[2] = {};
			sz_digit[0] = LOWORD(wParam) - 1000 + 48;
			strcat(sz_buffer, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		if (LOWORD(wParam) == IDC_BTN_CLEAR)
		{
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)"");
			a = b = 0;
			s = 0;
			stored = FALSE;
		}
		if (LOWORD(wParam) >= IDC_BTN_DIVISION && LOWORD(wParam) <= IDC_BTN_PLUS)
		{
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BTN_EQUAL), 0);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			a = strtod(sz_buffer, NULL);
			s = LOWORD(wParam);
			stored = TRUE;
		}
		if (LOWORD(wParam)==IDC_BTN_EQUAL)
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			b = strtod(sz_buffer, NULL);
			switch (s)
			{
			case IDC_BTN_PLUS: a += b; break;
			case IDC_BTN_MINUS: a -= b; break;
			case IDC_BTN_MULTIPLICATION: a *= b; break;
			case IDC_BTN_DIVISION: a /= b; break;
			default: a = b;
			}
			sprintf(sz_buffer, "%f", a);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			s = 0;
			stored = TRUE;
		}

		SetFocus(hwnd);
	}
	break;
	case WM_KEYDOWN:
	{
		if (LOWORD(wParam) >= '0'&&LOWORD(wParam) <= '9')SendMessage(hwnd, WM_COMMAND, LOWORD(wParam) + 1000 - '0', 0);
		switch (LOWORD(wParam))
		{
		case VK_OEM_PERIOD: SendMessage(hwnd, WM_COMMAND, IDC_BTN_POINT, 0); break;
		case VK_ESCAPE: SendMessage(hwnd, WM_COMMAND, IDC_BTN_CLEAR, 0); break;
		}
	}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}