// lab3.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "lab3.h"

#define STRICT
#include <windows.h>

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
HWND hButton1, hButton2;

// ��������� ���������� �������, ���������� � ���� ������ ����:
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

    // TODO: ���������� ��� �����.

    // ������������� ���������� �����
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));
	HWND hWnd;
    MSG msg;

    // ���� ��������� ���������:
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
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
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
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

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
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND � ���������� ���� ����������
//  WM_PAINT � ���������� ������� ����
//  WM_DESTROY � ��������� ��������� � ������ � ���������
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
            // ��������� ����� � ����:
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
		// �������������� ������
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

// ���������� ��������� ��� ���� "� ���������".
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
// ������� DrawButton
// �������������� ������
// =====================================

void DrawButton(LPDRAWITEMSTRUCT lpInfo)
{
	HBITMAP hbm, hbm1;
	int ResourceID;

	// ������������ ��������� WM_DRAWITEM
	// ������ ���� ��� ��������� �� ������ 
	if (lpInfo->CtlType != ODT_BUTTON)
		return;

	// ��� ��� � ���������� ����� ���� ���������
	// ������, ���������� ��������� WM_DRAWITEM,
	// ��������� ������������� ������
	switch (lpInfo->CtlID)
	{
	case 1001:
	{
		// ��������� ������������� �����������
		// ������ � ���������� (�������) ���������
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

	// ���� ������ �������, ������ �� � �������
	// ���������
	if (lpInfo->itemState & ODS_SELECTED)
	{
		switch (lpInfo->CtlID)
		{
		case 1001:
		{
			// ��������� ������������� �����������
			// ������ � ���������� (�������) ���������
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
	// ��������� ����������� ������ �� �������� ����������
	hbm = LoadBitmap(hInst, MAKEINTRESOURCE(ResourceID));
	// ��� ������ ������ �� ������
	if (!hbm) return;

	// ���� ������ ������� � �� ���� �������
	// ������������, �������� ������� DrawBitmap
	if ((lpInfo->itemAction & ODA_DRAWENTIRE) || (lpInfo->itemAction & ODA_SELECT))
	{
		// ������ ������
		DrawBitmap(lpInfo->hDC, (lpInfo->rcItem).left, (lpInfo->rcItem).top, hbm);
	}

	// ������� ����������� ������, ��� ��� ���
	// ��� ������ �� �����
	DeleteObject(hbm);
}
// ----------------------------------------
// ��������� ����������� ���� bitmap
// ----------------------------------------

void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap)
{
	HBITMAP hbm, hOldbm;
	HDC hMemDC;
	BITMAP bm;
	POINT  ptSize, ptOrg;

	// ������� �������� ������, �����������
	// � ���������� �����������
	hMemDC = CreateCompatibleDC(hDC);

	// �������� ����������� bitmap � �������� ������
	hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);

	// ���� �� ���� ������, ���������� ������
	if (hOldbm)
	{
		// ��� ��������� ������ ������������� ��� ��
		// ����� �����������, ��� ������������ �
		// ��������� �����������
		SetMapMode(hMemDC, GetMapMode(hDC));

		// ���������� ������� �����������
		GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

		ptSize.x = bm.bmWidth;   // ������
		ptSize.y = bm.bmHeight;  // ������

								 // ����������� ���������� ���������� � ����������
								 // ��� ���������� ������
		DPtoLP(hDC, &ptSize, 1);

		ptOrg.x = 0;
		ptOrg.y = 0;

		// ����������� ���������� ���������� � ����������
		// ��� ��������� ������
		DPtoLP(hMemDC, &ptOrg, 1);

		// ������ ����������� bitmap
		BitBlt(hDC, x, y, ptSize.x, ptSize.y,
			hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);

		// ��������������� �������� ������
		SelectObject(hMemDC, hOldbm);
	}

	// ������� �������� ������
	DeleteDC(hMemDC);
}
