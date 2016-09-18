#include "stdafx.h"
#include "Win32Project111.h"
#include <math.h>
#include <commctrl.h>


#define MAX_LOADSTRING 100

HINSTANCE hInst;                               
WCHAR szTitle[MAX_LOADSTRING];                 
WCHAR szWindowClass[MAX_LOADSTRING];         
HANDLE hThreads[3];
BOOL flag = FALSE;
HWND hwnd, prbar, prbar1;
struct winparams { 
	int x; 
	int y; 
};
struct winparams coord;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WIN32PROJECT111, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT111));

	MSG msg;

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT111));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32PROJECT111);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; 
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	CreateWindowEx(NULL, L"BUTTON", L"Start", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 5, 100, 20, hWnd, (HMENU)1001, hInstance, NULL);
	CreateWindowEx(NULL, L"BUTTON", L"Stop", WS_VISIBLE | WS_CHILD | WS_BORDER, 105, 5, 100, 20, hWnd, (HMENU)1002, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

DWORD WINAPI Func_Thread(LPVOID lpParameter)
{
	struct winparams strct = *((struct winparams*)lpParameter);
	do {
		SendMessage(prbar, PBM_SETRANGE, 0, MAKELPARAM(0, strct.x));
		SendMessage(prbar, PBM_STEPIT, 0, 0);
		Sleep(1000);
	} while (TRUE);
	return 0;
}
DWORD WINAPI Func_Thread1(LPVOID lpParameter)
{
	struct winparams strct = *((struct winparams*)lpParameter);
	do {
		SendMessage(prbar1, PBM_SETRANGE, 0, MAKELPARAM(0, strct.y));
		SendMessage(prbar1, PBM_STEPIT, 0, 0);
		Sleep(1000);
	} while (TRUE);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		prbar = CreateWindowEx(0, PROGRESS_CLASS, NULL,
			WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
			20, 100, 900, 17,
			hWnd, NULL, hInst, NULL);
		SendMessage(prbar, PBM_SETSTEP, (WPARAM)1, 0);
		prbar1 = CreateWindowEx(0, PROGRESS_CLASS, NULL,
			WS_CHILD | WS_VISIBLE,
			20, 300, 900, 17,
			hWnd, NULL, hInst, NULL);
		SendMessage(prbar1, PBM_SETSTEP, (WPARAM)1, 0);
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1001:
			hwnd = hWnd;
			if (flag)
			{
				ResumeThread(hThreads[1]);
				ResumeThread(hThreads[2]);
				
			}
			else
			{
				coord.x = 3;
				coord.y = 50;
				hThreads[1] = CreateThread(NULL, 0, Func_Thread, &coord, 0, NULL);
				hThreads[2] = CreateThread(NULL, 0, Func_Thread1, &coord, 0, NULL);
				Sleep(100);
				if (!flag) flag = TRUE;
			}
			break;
		case 1002:
				SuspendThread(hThreads[1]);
				SuspendThread(hThreads[2]);
			break;
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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
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