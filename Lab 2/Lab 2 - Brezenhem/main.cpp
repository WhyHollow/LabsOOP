#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

typedef void(*function)(HDC hDC, int x1, int y1, int x2, int y2);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {

	HWND hWnd;
	MSG lpMsg;
	WNDCLASS wc;

	LPCWSTR szClassName = L"WndClass";

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, L"Cannot register class!", L"Error", MB_OK);
		return 0;
	}

	hWnd = CreateWindow(//создаёт окошко
		szClassName,
		L"Brezenhem circle",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, NULL,
		CW_USEDEFAULT, NULL,
		(HWND)NULL,
		NULL,
		HINSTANCE(hInst),
		NULL);

	if (!hWnd) {
		MessageBox(NULL, L"Cannot create window!", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	
	return lpMsg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	RECT Rect;
	HDC hDC, hCmpDC;
	HBITMAP hBmp;
	static int x1, y1, x2, y2;
	static bool win_paint = true;
	static int state = 0;

	switch (msg) {

	case WM_PAINT:  // поки малює
		GetClientRect(hWnd, &Rect);//рахує область де буде знаходитися наш обьект
		hDC = BeginPaint(hWnd, &ps);
		hCmpDC = CreateCompatibleDC(hDC);
		hBmp = CreateCompatibleBitmap(hDC, Rect.right - Rect.left, Rect.bottom - Rect.top);
		SelectObject(hCmpDC, hBmp);
		LOGBRUSH br;
		br.lbStyle = BS_SOLID;
		br.lbColor = RGB(255, 255, 255);
		HBRUSH brush;
		brush = CreateBrushIndirect(&br);
		FillRect(hCmpDC, &Rect, brush);
		DeleteObject(brush);
		SetBkColor(hCmpDC, RGB(255, 255, 255));
		win_paint ? TextOut(hCmpDC, 10, 10, L"System", 6) : TextOut(hCmpDC, 10, 10, L"My Function", 11);
		if (state != 0)
			if (win_paint)
				Ellipse(hCmpDC, x1, y1, x2, y2);
			else {
				HMODULE hM = LoadLibrary(L"BrezenhemDLL.dll");
				function MyEllipse = (function)GetProcAddress(hM, "MyEllipse");
				MyEllipse(hCmpDC, x1, y1, x2, y2);
				FreeLibrary(hM);
			}
		SetStretchBltMode(hDC, COLORONCOLOR);
		BitBlt(hDC, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, hCmpDC, 0, 0, SRCCOPY);
		DeleteDC(hCmpDC);
		DeleteObject(hBmp);
		hCmpDC = NULL;
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN: // натиснули на мишку
		if (state == 0) {
			x1 = x2 = LOWORD(lParam);
			y1 = y2 = HIWORD(lParam);
		}
		if (state == 2) {
			x1 = x2 = y1 = y2 = 0;
			state = 0;
		}
		else
			state++;
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE: // поки мишка натиснута
		if (state == 1) {
			x2 = LOWORD(lParam);
			y2 = HIWORD(lParam);
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_KEYDOWN: // коли відпустили мишку
		win_paint = !win_paint;
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

