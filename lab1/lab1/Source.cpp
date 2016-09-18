#include <windows.h>
#include <tchar.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
LPCWSTR IpNameFile = L"C:\\Hand.ani";
int APIENTRY _tWinMain(HINSTANCE This,
	HINSTANCE Prev, LPTSTR cmd,
	int mode)
{
	HWND hWnd; MSG msg; WNDCLASS wc;
	HMENU hmenu = CreateMenu();
	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(This, MAKEINTRESOURCE(IDI_ICON1)); // My icon
	wc.hCursor = LoadCursorFromFile(IpNameFile); // My cursor
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 
	if (!RegisterClass(&wc)) return 0;
	hWnd = CreateWindow(WinName, 
		_T("Lab 1"), 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP, 
		NULL,
		This,
		NULL); 
	ShowWindow(hWnd, mode);
							
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); // Посылает сообщение функции WndProc()
	}
	return 0;
}
TCHAR *text = _T("Текст для вывода в окне");
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps; 
	HDC hdc; 
	static int x = 0;
	static int y = 0;
	static int draw = 0;
	static int flag = 1;
	switch (message)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_MENU_START:
			SetTimer(hWnd, 1, 50, 0);
			break;
		case ID_MENU_STOP:
			KillTimer(hWnd, 1);
			break;
		case ID_SPEED_4X:
			flag = 4;
			break;
		case ID_EXIT:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_TIMER:
		if (x <= 800) {
			if (flag == 4) {
				x += 20;
			}
			else {
				x += 5;
			}
		} else while (x != 0) {
			x -= 5;
		}
		draw = 1;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (draw) {
			SetBkColor(hdc, RGB(255, 255, 0)); // Желтый фон 
			SetTextColor(hdc, RGB(0, 0, 128)); // Синий шрифт 
			TextOut(hdc, 10 + x, 200 + y, text, _tcsclen(text));
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY: 
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}