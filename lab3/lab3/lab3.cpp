// lab3.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "lab3.h"

#define STRICT
#include <windows.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hButton1, hButton2;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void DrawButton(LPDRAWITEMSTRUCT);
void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap);

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
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));
	HWND hWnd;
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   hButton1 = CreateWindow(L"button", L"Button 1", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 20, 20, 50, 50, hWnd, (HMENU)1001, hInstance, NULL);
   hButton2 = CreateWindow(L"button", L"Button 2", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 20, 80, 50, 50, hWnd, (HMENU)1002, hInstance, NULL);


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
	static int draw = 0;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case 1001:
				draw = 1;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case 1002:
				draw = 2;
				InvalidateRect(hWnd, NULL, TRUE);
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
	case WM_DRAWITEM:
	{
		// Перерисовываем кнопку
		DrawButton((LPDRAWITEMSTRUCT)lParam);
		break;
	}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			HBRUSH hBrush;
            HDC hdc = BeginPaint(hWnd, &ps);
			POINT poly1[4];
			POINT poly2[5];
			if (draw == 1) {
				hBrush = (HBRUSH)SelectObject(hdc, CreateSolidBrush(RGB(187, 187, 187)));
				Rectangle(hdc, 300, 200, 600, 400);
				Rectangle(hdc, 400, 300, 500, 250);
				Rectangle(hdc, 390, 250, 510, 260);

				Rectangle(hdc, 250, 300, 300, 400);
				Rectangle(hdc, 600, 300, 650, 400);

				Rectangle(hdc, 260, 310, 290, 390);
				Rectangle(hdc, 270, 320, 280, 380);
				Rectangle(hdc, 280, 330, 270, 370);

				Rectangle(hdc, 610, 310, 640, 390);
				Rectangle(hdc, 620, 320, 630, 380);
				Rectangle(hdc, 630, 330, 620, 370);

				MoveToEx(hdc, 450, 300, NULL);
				LineTo(hdc, 450, 250);
				MoveToEx(hdc, 400, 275, NULL);
				LineTo(hdc, 500, 275);
				Arc(hdc, 300, 600, 400, 200, 300, 100, 200, 100);
				Arc(hdc, 500, 600, 600, 300, 500, 100, 400, 100);
				Ellipse(hdc, 370, 95, 535, 155);
				Ellipse(hdc, 370, 100, 530, 150);
				Ellipse(hdc, 400, 130, 490, 120);
				

				poly1[0].x = 300;
				poly1[0].y = 200;
				poly1[1].x = 450;
				poly1[1].y = 10;
				poly1[2].x = 600;
				poly1[2].y = 200;
				poly1[3].x = 300;
				poly1[3].y = 200;

				Polyline(hdc, poly1, 4);

				poly2[0].x = 300;
				poly2[0].y = 400;
				poly2[1].x = 380;
				poly2[1].y = 370;
				poly2[2].x = 480;
				poly2[2].y = 400;
				poly2[3].x = 580;
				poly2[3].y = 370;
				poly2[4].x = 600;
				poly2[4].y = 400;

				Polyline(hdc, poly2, 5);
				
			}
			else if (draw == 2) {
				RECT rect;
				GetClientRect(hWnd, &rect);
				FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			}
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

// =====================================
// Функция DrawButton
// Перерисовывает кнопку
// =====================================

void DrawButton(LPDRAWITEMSTRUCT lpInfo)
{
	HBITMAP hbm, hbm1;
	int ResourceID;

	// Обрабатываем сообщение WM_DRAWITEM
	// только если оно поступило от кнопки 
	if (lpInfo->CtlType != ODT_BUTTON)
		return;

	// Так как в приложении может быть несколько
	// кнопок, посылающих сообщение WM_DRAWITEM,
	// проверяем идентификатор кнопки
	switch (lpInfo->CtlID)
	{
	case 1001:
	{
		// Загружаем идентификатор изображения
		// кнопки в нормальном (отжатом) состоянии
		ResourceID = IDB_BITMAP3;
		break;
	}
	case 1002:
	{
		ResourceID = IDB_BITMAP4;
		break;
	}
	default:
		return;
	}

	// Если кнопка выбрана, рисуем ее в нажатом
	// состоянии
	if (lpInfo->itemState & ODS_SELECTED)
	{
		switch (lpInfo->CtlID)
		{
		case 1001:
		{
			// Загружаем идентификатор изображения
			// кнопки в нормальном (отжатом) состоянии
			ResourceID = IDB_BITMAP2;
			break;
		}
		case 1002:
		{
			ResourceID = IDB_BITMAP5;
			break;
		}
		}
	}
	// Загружаем изображение кнопки из ресурсов приложения
	hbm = LoadBitmap(hInst, MAKEINTRESOURCE(ResourceID));
	// При ошибке ничего не рисуем
	if (!hbm) return;

	// Если кнопка выбрана и ее надо целиком
	// перерисовать, вызываем функцию DrawBitmap
	if ((lpInfo->itemAction & ODA_DRAWENTIRE) || (lpInfo->itemAction & ODA_SELECT))
	{
		// Рисуем кнопку
		DrawBitmap(lpInfo->hDC, (lpInfo->rcItem).left, (lpInfo->rcItem).top, hbm);
	}

	// Удаляем изображение кнопки, так как оно
	// нам больше не нужно
	DeleteObject(hbm);
}
// ----------------------------------------
// Рисование изображения типа bitmap
// ----------------------------------------

void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap)
{
	HBITMAP hbm, hOldbm;
	HDC hMemDC;
	BITMAP bm;
	POINT  ptSize, ptOrg;

	// Создаем контекст памяти, совместимый
	// с контекстом отображения
	hMemDC = CreateCompatibleDC(hDC);

	// Выбираем изображение bitmap в контекст памяти
	hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);

	// Если не было ошибок, продолжаем работу
	if (hOldbm)
	{
		// Для контекста памяти устанавливаем тот же
		// режим отображения, что используется в
		// контексте отображения
		SetMapMode(hMemDC, GetMapMode(hDC));

		// Определяем размеры изображения
		GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

		ptSize.x = bm.bmWidth;   // ширина
		ptSize.y = bm.bmHeight;  // высота

								 // Преобразуем координаты устройства в логические
								 // для устройства вывода
		DPtoLP(hDC, &ptSize, 1);

		ptOrg.x = 0;
		ptOrg.y = 0;

		// Преобразуем координаты устройства в логические
		// для контекста памяти
		DPtoLP(hMemDC, &ptOrg, 1);

		// Рисуем изображение bitmap
		BitBlt(hDC, x, y, ptSize.x, ptSize.y,
			hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);

		// Восстанавливаем контекст памяти
		SelectObject(hMemDC, hOldbm);
	}

	// Удаляем контекст памяти
	DeleteDC(hMemDC);
}
