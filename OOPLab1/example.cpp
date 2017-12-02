#include "Shape.h"
#include "DrawHelpers.h"


int main()
{
	try {
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		color outlineColor = { 255, 0, 0 };
		color fillerColor = { 200, 100, 0 };

		Contour contour(outlineColor);

		Rhomb a(50, 50, 100, 20, &contour);
		Rhomb b(55, 50, 100, 35, &contour);
		
		a.draw(hwnd, hdc);
		a.shiftRhomb(-10, 50);
		a.draw(hwnd, hdc);

		Filled filled(outlineColor, fillerColor);
		FilledRhomb c(50, 50, 100, 20, &filled);
		clearTheScreen(hwnd);
		c.draw(hwnd, hdc);

		CombinedFilledRhomb d(50, 50, 100, 20, &b, &filled);
		clearTheScreen(hwnd);
		d.draw(hwnd, hdc);

	}
	catch (std::exception ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}