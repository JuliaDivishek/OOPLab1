#include "Rhomb.h"

int main() {
	
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	Rhomb a;
	a.readFromFile("rhomb.txt");
	a.drawFilledRhomb(hdc);
	system("pause");
	a.drawRhomb(hdc);
	//a.saveToFile("rhomb.txt");
	return 0;
}