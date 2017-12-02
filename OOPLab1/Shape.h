#pragma once

#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Color.h"
#include "DrawHelpers.h"


class Shape {

public: 
	virtual void draw(HWND hwnd, HDC hdc) = 0;
};


class Contour {
protected:
	color outline; //цвет контура
	HPEN hPen; //перо

	void checkColor(short, short, short);
	
public:
	Contour(color);
	HPEN getHpen();
	color getOutlineColor();
};


class Filled: public Contour {
	
	color filler; //цвет заливки
	HBRUSH hBrush; //кисть

public:
	Filled(color, color);
	HBRUSH getHbrush();
	color getFillerColor();
};


class Rhomb: public Shape
{
	Contour *contour;

protected:
	POINT *points; //вершины
	void checkPoints(int, int, int, int);

public:
	Rhomb(int, int, int, int, Contour*);
	~Rhomb();
	void setPoints(int, int, int, int);
	void shiftRhomb(int, int);
	POINT* getPoints();
	void draw(HWND hwnd, HDC hdc);
	void checkOutTheWindow(HWND hwnd);
};


class FilledRhomb : public Rhomb {
protected:
	Filled *filled;
public:
	FilledRhomb(int, int, int, int, Filled*);
	void draw(HWND hwnd, HDC hdc);
};

class CombinedFilledRhomb : public FilledRhomb {
	void isRhombInside(Rhomb*);
	Rhomb* innerRhomb;

public:
	CombinedFilledRhomb(int, int, int, int, Rhomb*, Filled*);
	void draw(HWND hwnd, HDC hdc);
};