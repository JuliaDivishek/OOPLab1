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
	HWND hwnd;
	HDC hdc;
	color outline; //���� �������
	color filler; //���� �������
	HPEN hNewPen; //����
	HBRUSH hNewBrush; //�����

	void checkColor(short, short, short);

public:
	Draw();
	Draw(HWND, HDC, color*, color*);
	~Draw();
	void drawRhomb(Rhomb*);
	void drawFilledRhomb(Rhomb*);
	void drawRhombInRhomb(Rhomb*, Rhomb*);
	void moveRhomb(Rhomb*);
	void saveColorsToFile(string);
	void readColorsFromFile(string);
	void setOutlineColor(short, short, short);
	void setFillerColor(short, short, short);
};

