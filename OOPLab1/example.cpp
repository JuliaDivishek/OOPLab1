#include "Rhomb.h"
#include "Draw.h"



int main()
{
	try {
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		Rhomb a(50, 50, 100, 20);
		Rhomb b(55, 50, 100, 35);
		

		color outlineColor = { 255, 0, 0 };
		color fillerColor = { 200, 100, 0 };
		Draw c(hwnd, hdc, &outlineColor, &fillerColor);
		c.readColorsFromFile("colors.txt");

		
		c.drawFilledRhomb(&a);
		c.drawRhomb(&a);
		
		c.drawRhombInRhomb(&a, &b);
		c.setFillerColor(100, 100, 100);
		c.setOutlineColor(0, 255, 0);
		c.moveRhomb(&a);
		
		c.drawRhomb(&a);
		c.drawFilledRhomb(&a);
	}
	catch (exception ex)
	{
		cerr << ex.what() << endl;
	}
	return 0;
}