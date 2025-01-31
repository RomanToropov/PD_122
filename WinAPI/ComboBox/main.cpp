#include<Windows.h>
#include<stdio.h>
#include"resource.h"

CONST CHAR* words[] =
{
	"This", "is", "my", "first", "Combo", "Box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(words) / sizeof(CHAR*); i++)
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)words[i]);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR buffer[SIZE]{};
			INT cursel = SendMessage(GetDlgItem(hwnd, IDC_COMBO1), CB_GETCURSEL, 0, 0);
			if (cursel != CB_ERR)
			{
				CHAR text[SIZE]{};
				SendMessage(GetDlgItem(hwnd, IDC_COMBO1), CB_GETLBTEXT, cursel, (LPARAM)text);
				sprintf(buffer, "�� ������� ������� %d - %s", cursel, text);
			}
			else
			{
				sprintf(buffer, "�� ������ �� �������");
			}
			MessageBox(hwnd, buffer, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}