// lab2.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "lab2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
WCHAR mas[MAX_LOADSTRING];
WCHAR mas1[MAX_LOADSTRING];
HWND edit1, listbox1, listbox2;
int count, cnt;
int items[MAX_LOADSTRING];
int items1[MAX_LOADSTRING];

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 600, 350, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   CreateWindowEx(NULL, L"BUTTON", L"Add", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 40, 100, 20, hWnd, (HMENU)101, hInstance, NULL);
   edit1 = CreateWindowEx(NULL, L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10, 100, 20, hWnd, NULL, hInstance, NULL);
   listbox1 = CreateWindowEx(NULL, L"LISTBOX", L"lstbox1", WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_EXTENDEDSEL | LBS_STANDARD, 120, 35, 200, 200, hWnd, NULL, hInstance, NULL);
   listbox2 = CreateWindowEx(NULL, L"LISTBOX", L"lstbox2", WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_EXTENDEDSEL | LBS_STANDARD, 340, 35, 200, 200, hWnd, NULL, hInstance, NULL);
   CreateWindowEx(NULL, L"BUTTON", L"Clear", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 240, 100, 20, hWnd, (HMENU)102, hInstance, NULL);
   CreateWindowEx(NULL, L"BUTTON", L"ToRight", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 10, 200, 20, hWnd, (HMENU)103, hInstance, NULL);
   CreateWindowEx(NULL, L"BUTTON", L"Delete", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 240, 420, 20, hWnd, (HMENU)106, hInstance, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case 101:
				if (SendMessage(edit1, WM_GETTEXT, sizeof(mas), (LPARAM)mas))
				{
					count = SendMessage(listbox1, LB_GETCOUNT, 0, 0);
					if (count)
					{
						for (int i = 0; i < count; i++)
						{
							SendMessage(listbox1, LB_GETTEXT, i, (LPARAM)mas1);
							if (wcscmp(mas, mas1) == 0)
							{
								break;
							}
							else if (i == count - 1)
							{
								SendMessage(listbox1, LB_INSERTSTRING, 0, (LPARAM)mas);
								break;
							}
						}
					}
					else
					{
						SendMessage(listbox1, LB_INSERTSTRING, 0, (LPARAM)mas);
					}
				}
				break;
			case 102:
				SendMessage(listbox1, LB_RESETCONTENT, 0, 0);
				SendMessage(listbox2, LB_RESETCONTENT, 0, 0);
				break;
			case 103:
				if (SendMessage(listbox1, LB_GETSELITEMS, sizeof(items), (LPARAM)items)) {
					SendMessage(listbox1, LB_GETTEXT, items[0], (LPARAM)mas);
					count = SendMessage(listbox2, LB_GETCOUNT, 0, 0);
					if(count) {
						for(int i = 0; i < count; i++)
						{
							SendMessage(listbox2, LB_GETTEXT, i, (LPARAM)mas1);
							if (wcscmp(mas, mas1) == 0) {
								break;
							}
							else if (i == count - 1) {
								SendMessage(listbox2, LB_INSERTSTRING, 0, (LPARAM)mas);
								break;
							}
						}
					}
					else {
						SendMessage(listbox2, LB_INSERTSTRING, 0, (LPARAM)mas);
					}
				}
				break;
			case 106:
				if (cnt = SendMessage(listbox1, LB_GETSELITEMS, sizeof(items), (LPARAM)items)) {
					while (cnt) {
						SendMessage(listbox1, LB_DELETESTRING, items[--cnt], 0);
					}
				}
				if (cnt = SendMessage(listbox2, LB_GETSELITEMS, sizeof(items), (LPARAM)items)) {
					while (cnt) {
						SendMessage(listbox2, LB_DELETESTRING, items[--cnt], 0);
					}
				}
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
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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

// Обработчик сообщений для окна "О программе".
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
