#include <windows.h>

void clearTheScreen(HWND hwnd)
{
	system("pause");
	InvalidateRect(hwnd, 0, TRUE);
	UpdateWindow(hwnd);
}

RECT getWindowSize(HWND hwnd)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	return rt;
}