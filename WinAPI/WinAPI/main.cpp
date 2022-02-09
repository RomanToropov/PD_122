#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox(FindWindow(NULL, "WinAPI - Microsoft Visual Studio"), "Привет! Это мое первое окно сообщения", "Hello World",
		MB_DEFBUTTON4 |MB_ICONWARNING | MB_YESNOCANCEL | MB_HELP |  MB_SYSTEMMODAL);*/

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:	//Инициализация окна (создание значков и т.д.)
		break;
	case WM_COMMAND:	//Обработка команд нажатия кнопок и т.д.
	{
		//WORD = 2 BYTES
		//DWORD = 4 BYTES
		//LOWORD - два младших Байта в двойном слове
		//HIWORD - два старших Байта в двойном слове
		switch (LOWORD(wParam))
		{
		case IDOK:		MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_ICONINFORMATION | MB_OK); break;
		case IDCANCEL:	EndDialog(hwnd, 0);	break;
		}
	}
	break;
	case WM_CLOSE:
		//Закрытие окна:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}