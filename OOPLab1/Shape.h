#pragma once

#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Color.h"
#include "DrawHelpers.h"


class Shape
{
public: 
	virtual void draw(HWND, HDC) = 0;
	virtual void shiftShape(int, int) = 0;
	virtual void saveToFile(std::ofstream&) = 0;
	virtual void readFromFile(std::ifstream&) = 0;
};


class Contour
{
protected:
	color outline; //цвет контура
	HPEN hPen; //перо

	void checkColor(short, short, short);
	
public:
	Contour(color);
	HPEN getHpen();
	color getOutlineColor();

	void saveToFile(std::ofstream&);
	void readFromFile(std::ifstream&);
	void setColor(short, short, short);
};


class Filled: public Contour
{
	color filler; //цвет заливки
	HBRUSH hBrush; //кисть

public:
	Filled(color, color);
	HBRUSH getHbrush();
	color getFillerColor();
	void setColor(short, short, short);
	void saveToFile(std::ofstream&);
	void readFromFile(std::ifstream&);
};


class Rhomb: public Shape
{
protected:
	Contour *contour;
	POINT *points; //вершины
	void checkPoints(int, int, int, int);

public:
	Rhomb(int, int, int, int, Contour*);
	~Rhomb();
	void setPoints(int, int, int, int);
	void shiftShape(int, int);
	POINT* getPoints();
	void draw(HWND hwnd, HDC hdc);
	void checkOutTheWindow(HWND hwnd);
	void saveToFile(std::ofstream&);
	void readFromFile(std::ifstream&);
};


class FilledRhomb : public Rhomb
{
protected:
	Filled *filled;
public:
	FilledRhomb(int, int, int, int, Filled*);
	void draw(HWND, HDC);
	void saveToFile(std::ofstream&);
	void readFromFile(std::ifstream&);
};

class CombinedFilledRhomb : public FilledRhomb
{
	Rhomb* innerRhomb;

	void isRhombInside();

public:
	CombinedFilledRhomb(int, int, int, int, Rhomb*, Filled*);
	void draw(HWND, HDC);
	void saveToFile(std::ofstream&);
	void readFromFile(std::ifstream&);
	void shiftShape(int, int);
};