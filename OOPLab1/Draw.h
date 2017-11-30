#pragma once
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <string.h>
#include "Color.h"
#include "Rhomb.h"


class Draw
{
	HWND hwnd;
	HDC hdc;
	color outline; //цвет контура
	color filler; //цвет заливки
	HPEN hNewPen; //перо
	HBRUSH hNewBrush; //кисть

	void checkColor(short, short, short);
	void checkOutTheWindow(Rhomb*);

public:
	Draw();
	Draw(HWND, HDC, color*, color*);
	~Draw();
	void drawRhomb(Rhomb*);
	void drawFilledRhomb(Rhomb*);
	void drawRhombInRhomb(Rhomb*, Rhomb*);
	void saveColorsToFile(std::ofstream&);
	void readColorsFromFile(std::ifstream&);
	void setOutlineColor(short, short, short);
	void setFillerColor(short, short, short);
	
};

