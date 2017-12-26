#include <Windows.h>

__declspec(dllexport)
void MyEllipse(HDC hDC, int x1, int y1, int x2, int y2) {
	int x_centre = (x1 + x2) / 2, y_centre = (y1 + y2) / 2, a = abs(x2 - x1) / 2, b = abs(y2 - y1) / 2, x = 0, y = b;
	int delta = b*b - 2 * b*a*a + a*a; // переписане рівняння еліпса
	while (y >= 0)
	{
		SetPixel(hDC, x_centre + x, y_centre + y, RGB(0, 0, 0));
		SetPixel(hDC, x_centre + x, y_centre - y, RGB(0, 0, 0));
		SetPixel(hDC, x_centre - x, y_centre + y, RGB(0, 0, 0));
		SetPixel(hDC, x_centre - x, y_centre - y, RGB(0, 0, 0));
		if (delta < 0 && (2 * (delta + y*a*a) - a*a) <= 0)
		{
			x++;
			delta += b*b*(2 * x + 1);  
			continue;
		}
		if (delta > 0 && (2 * (delta - x*b*b) - b*b) > 0)
		{
			y--;
			delta += a*a*(-2 * y + 1);
			continue;
		}
		x++;
		y--;
		delta += 2 * (x*b*b - y*a*a) + b*b + a*a;
	}
}
