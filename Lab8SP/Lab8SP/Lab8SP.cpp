#include "stdafx.h"
#include "Lab8SP.h"
#include <tlhelp32.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND listbox1, listbox2;
DWORD processIDs[100];
HANDLE hStdOut;
DWORD id = 0;
HANDLE hProcess;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID PrintProcessList(HANDLE hStdOut);
VOID PrintModuleList(HANDLE hStdOut, DWORD dwProcessId);

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
	LoadStringW(hInstance, IDC_LAB8SP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB8SP));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB8SP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB8SP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 815, 650, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	listbox1 = CreateWindowEx(NULL, L"LISTBOX", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | LBS_EXTENDEDSEL | LBS_STANDARD, 0, 0, 400, 600, hWnd, (HMENU)150, hInst, NULL);
	listbox2 = CreateWindowEx(NULL, L"LISTBOX", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | LBS_EXTENDEDSEL | LBS_STANDARD, 400, 0, 400, 600, hWnd, NULL, hInst, NULL);

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // дескрипт для ввода/вывода данных
	PrintProcessList(hStdOut);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:

		break;
	case WM_CONTEXTMENU:
		int itemarea[40];
		if (SendMessage(listbox1, LB_GETSELITEMS, sizeof(itemarea), (LPARAM)itemarea) > 0) {
			HMENU hMenu = CreatePopupMenu();
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id = processIDs[itemarea[0]]);
			DWORD ong = GetPriorityClass(hProcess);
			TCHAR low[1024];
			wsprintf(low, L"Простаивающий %s", ong == IDLE_PRIORITY_CLASS ? L"!" : L"");
			TCHAR norm[1024];
			wsprintf(norm, L"Нормальный %s", ong == NORMAL_PRIORITY_CLASS ? L"!" : L"");
			TCHAR high[1024];
			wsprintf(high, L"Высокий %s", ong == HIGH_PRIORITY_CLASS ? L"!" : L"");
			TCHAR rltm[1024];
			wsprintf(rltm, L"Реального времени %s", ong == REALTIME_PRIORITY_CLASS ? L"!" : L"");
			AppendMenu(hMenu, MFT_STRING, 151, low);
			AppendMenu(hMenu, MFT_STRING, 152, norm);
			AppendMenu(hMenu, MFT_STRING, 153, high);
			AppendMenu(hMenu, MFT_STRING, 154, rltm);

			TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
			DestroyMenu(hMenu);
		}
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case 150:
			int itemarea[40];
			if (SendMessage(listbox1, LB_GETSELITEMS, sizeof(itemarea), (LPARAM)itemarea) > 0) {
				PrintModuleList(hStdOut, processIDs[itemarea[0]]);
			}
			break;
		case 151:
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
			SetPriorityClass(hProcess, IDLE_PRIORITY_CLASS);
			break;
		case 152:
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
			SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
			break;
		case 153:
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
			SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
			break;
		case 154:
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, id);
			SetPriorityClass(hProcess, REALTIME_PRIORITY_CLASS);
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
		// TODO: Add any drawing code that uses hdc here...
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

VOID PrintProcessList(HANDLE hStdOut) {
	PROCESSENTRY32 peProcessEntry;
	TCHAR szBuff[1024];
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return;
	}

	peProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	Process32First(hSnapshot, &peProcessEntry);
	int i = 0;
	do {
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, peProcessEntry.th32ProcessID);
		DWORD ong = GetPriorityClass(hProcess);
		DWORD res = peProcessEntry.pcPriClassBase;
		processIDs[i++] = peProcessEntry.th32ProcessID;
		wsprintf(szBuff, L"%08X...%s", peProcessEntry.th32ProcessID, peProcessEntry.szExeFile);
		SendMessage(listbox1, LB_ADDSTRING, 0, (LPARAM)szBuff);
	} while (Process32Next(hSnapshot, &peProcessEntry));

	CloseHandle(hSnapshot);
}

VOID PrintModuleList(HANDLE hStdOut, DWORD dwProcessId) {
	SendMessage(listbox2, LB_RESETCONTENT, NULL, NULL);
	MODULEENTRY32 meModuleEntry;
	TCHAR szBuff[1024];
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return;
	}

	meModuleEntry.dwSize = sizeof(MODULEENTRY32);
	Module32First(hSnapshot, &meModuleEntry);
	do {
		wsprintf(szBuff, L"ADRESS: %08X, SIZE: %08X, %s\r\n", meModuleEntry.modBaseAddr, meModuleEntry.modBaseSize, meModuleEntry.szModule);
		SendMessage(listbox2, LB_ADDSTRING, 0, (LPARAM)szBuff);
	} while (Module32Next(hSnapshot, &meModuleEntry));

	CloseHandle(hSnapshot);
}