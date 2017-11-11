#pragma once
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Color.h"
#include "Rhomb.h"
using namespace std;

class Draw
{
	color outline; //цвет контура
	color filler; //цвет заливки
	HPEN hNewPen; //перо
	HBRUSH hNewBrush; //кисть
public:
	Draw();
	Draw(color*, color*);
	~Draw();
	void drawRhomb(HDC, Rhomb*);
	void drawFilledRhomb(HDC, Rhomb*);
	void setPen(int, int, int);
	void setBrush(int, int, int);
	void setDefaultPen();
	void setDefaultBrush();
};

