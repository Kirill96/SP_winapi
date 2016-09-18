// lab5.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "lab5.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND RButton_1, RButton_2, RButton_3, RButton_4, RButton_5, RButton_6, RButton_7, CBox_1;
HBRUSH hBrush;
int xPos, yPos, R, G, B;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc_Child(HWND, UINT, WPARAM, LPARAM);
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
    LoadStringW(hInstance, IDC_LAB5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB5);
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
      CW_USEDEFAULT, 0, 480, 150, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   RButton_1 = CreateWindowEx(NULL, L"BUTTON", L"Красный", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 5, 5, 100, 20, hWnd, (HMENU)1001, hInstance, NULL);
   RButton_2 = CreateWindowEx(NULL, L"BUTTON", L"Синий", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 110, 5, 100, 20, hWnd, (HMENU)1002, hInstance, NULL);
   RButton_3 = CreateWindowEx(NULL, L"BUTTON", L"Зеленый", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 220, 5, 100, 20, hWnd, (HMENU)1003, hInstance, NULL);
   RButton_4 = CreateWindowEx(NULL, L"BUTTON", L"Ромб", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 5, 30, 100, 20, hWnd, (HMENU)1004, hInstance, NULL);
   RButton_5 = CreateWindowEx(NULL, L"BUTTON", L"Квадрат", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 110, 30, 100, 20, hWnd, (HMENU)1005, hInstance, NULL);
   RButton_6 = CreateWindowEx(NULL, L"BUTTON", L"Круг", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 220, 30, 100, 20, hWnd, (HMENU)1006, hInstance, NULL);
   RButton_7 = CreateWindowEx(NULL, L"BUTTON", L"Звезда", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 330, 30, 100, 20, hWnd, (HMENU)1007, hInstance, NULL);

   CBox_1 = CreateWindowEx(NULL, L"BUTTON", L"Draw", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 5, 55, 100, 20, hWnd, (HMENU)1008, hInstance, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void PrintPicture(HDC hdc)
{
	if (SendMessage(CBox_1, BM_GETCHECK, 1, 0))
	{
		if (SendMessage(RButton_1, BM_GETCHECK, 1, 0))
		{
			R = 255;
			G = 0;
			B = 0;
		}
		else if (SendMessage(RButton_2, BM_GETCHECK, 1, 0))
		{
			R = 0;
			G = 0;
			B = 255;
		}
		else if (SendMessage(RButton_3, BM_GETCHECK, 1, 0))
		{
			R = 0;
			G = 255;
			B = 0;
		}
		else
		{
			R = 255;
			G = 255;
			B = 255;
		}

		if (SendMessage(RButton_4, BM_GETCHECK, 1, 0))
		{
			POINT poly[5];

			hBrush = CreateSolidBrush(RGB(R, G, B));
			SelectObject(hdc, hBrush);

			poly[0].x = xPos - 50;
			poly[0].y = yPos;

			poly[1].x = xPos;
			poly[1].y = yPos - 50;

			poly[2].x = xPos + 50;
			poly[2].y = yPos;

			poly[3].x = xPos;
			poly[3].y = yPos + 50;

			poly[4].x = xPos - 50;
			poly[4].y = yPos;

			Polygon(hdc, poly, 5);
		}
		else if (SendMessage(RButton_5, BM_GETCHECK, 1, 0))
		{
			hBrush = CreateSolidBrush(RGB(R, G, B));
			SelectObject(hdc, hBrush);
			Rectangle(hdc, xPos - 50, yPos - 50, xPos + 50, yPos + 50);
		}
		else if (SendMessage(RButton_6, BM_GETCHECK, 1, 0))
		{
			hBrush = CreateSolidBrush(RGB(R, G, B));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, xPos - 50, yPos - 50, xPos + 50, yPos + 50);
		}
		else if (SendMessage(RButton_7, BM_GETCHECK, 1, 0))
		{
			POINT poly[10];

			hBrush = CreateSolidBrush(RGB(R, G, B));
			SelectObject(hdc, hBrush);

			poly[0].x = xPos;
			poly[0].y = yPos - 80;

			poly[1].x = xPos + 20;
			poly[1].y = yPos - 20;

			poly[2].x = xPos + 70;
			poly[2].y = yPos;

			poly[3].x = xPos + 30;
			poly[3].y = yPos + 30;

			poly[4].x = xPos + 70;
			poly[4].y = yPos + 100;

			poly[5].x = xPos;
			poly[5].y = yPos + 60;

			poly[6].x = xPos - 70;
			poly[6].y = yPos + 100;

			poly[7].x = xPos - 30;
			poly[7].y = yPos + 30;

			poly[8].x = xPos - 70;
			poly[8].y = yPos;

			poly[9].x = xPos - 20;
			poly[9].y = yPos - 20;

			Polygon(hdc, poly, 10);
		}
	}
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
	case WM_CREATE:
		HWND hwnd;
		WNDCLASS w;
		hInst = hInst;
		memset(&w, 0, sizeof(WNDCLASS));
		w.style = CS_HREDRAW | CS_VREDRAW;
		w.lpfnWndProc = WndProc_Child;
		w.hInstance = hInst;
		w.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		w.lpszClassName = L"C Windows";
		w.hCursor = LoadCursor(NULL, IDC_ARROW);
		RegisterClass(&w);
		hwnd = CreateWindow(L"C Windows", L"C Windows", WS_OVERLAPPEDWINDOW,
			10, 10, 600, 480, NULL, NULL, hInst, NULL);
		ShowWindow(hwnd, SW_NORMAL);
		UpdateWindow(hwnd);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case 1001:
				SendMessage(RButton_1, BM_SETCHECK, 1, 0);
				SendMessage(RButton_2, BM_SETCHECK, 0, 0);
				SendMessage(RButton_3, BM_SETCHECK, 0, 0);
				break;
			case 1002:
				SendMessage(RButton_1, BM_SETCHECK, 0, 0);
				SendMessage(RButton_2, BM_SETCHECK, 1, 0);
				SendMessage(RButton_3, BM_SETCHECK, 0, 0);
				break;
			case 1003:
				SendMessage(RButton_1, BM_SETCHECK, 0, 0);
				SendMessage(RButton_2, BM_SETCHECK, 0, 0);
				SendMessage(RButton_3, BM_SETCHECK, 1, 0);
				break;
			case 1004:
				SendMessage(RButton_4, BM_SETCHECK, 1, 0);
				SendMessage(RButton_5, BM_SETCHECK, 0, 0);
				SendMessage(RButton_6, BM_SETCHECK, 0, 0);
				SendMessage(RButton_7, BM_SETCHECK, 0, 0);
				break;
			case 1005:
				SendMessage(RButton_4, BM_SETCHECK, 0, 0);
				SendMessage(RButton_5, BM_SETCHECK, 1, 0);
				SendMessage(RButton_6, BM_SETCHECK, 0, 0);
				SendMessage(RButton_7, BM_SETCHECK, 0, 0);
				break;
			case 1006:
				SendMessage(RButton_4, BM_SETCHECK, 0, 0);
				SendMessage(RButton_5, BM_SETCHECK, 0, 0);
				SendMessage(RButton_6, BM_SETCHECK, 1, 0);
				SendMessage(RButton_7, BM_SETCHECK, 0, 0);
				break;
			case 1007:
				SendMessage(RButton_4, BM_SETCHECK, 0, 0);
				SendMessage(RButton_5, BM_SETCHECK, 0, 0);
				SendMessage(RButton_6, BM_SETCHECK, 0, 0);
				SendMessage(RButton_7, BM_SETCHECK, 1, 0);
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

LRESULT CALLBACK WndProc_Child(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		InvalidateRect(hWnd, 0, 0);
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		PrintPicture(hdc);
		EndPaint(hWnd, &ps);
	}
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
