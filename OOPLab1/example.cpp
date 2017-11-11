#include "Rhomb.h"
#include "Draw.h"

void clearTheScreen(HWND hwnd)
{
	InvalidateRect(hwnd, 0, TRUE);
	UpdateWindow(hwnd);
}

int main()
{
	
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	Rhomb a(90, 200, 200, 50);
	//a.readFromFile("rhomb.txt");
	//a.drawFilledRhomb(hdc);
	
	
	Rhomb b;
	b.readFromFile("rhomb.txt");

	color outlineColor = { 125, 125, 125 };
	color fillerColor = { 200, 100, 0 };
	Draw c(&outlineColor, &fillerColor);
	c.drawFilledRhomb(hdc, &a);

	clearTheScreen(hwnd);

	c.drawRhomb(hdc, &b);
	

	clearTheScreen(hwnd);


	c.setPen(0, 255, 0);
	c.setBrush(255, 0, 0);
	c.drawFilledRhomb(hdc, &a);
	
	clearTheScreen(hwnd);

	c.drawRhomb(hdc, &a);

	
	//a.saveToFile("rhomb.txt");
	ReleaseDC(hwnd, hdc);
	return 0;
}