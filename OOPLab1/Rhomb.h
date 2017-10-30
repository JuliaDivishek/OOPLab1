#pragma once
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct
{
	int R;
	int G;
	int B;
} color;

class Rhomb
{
	POINT *points; //вершины
	color outline; //цвет контура
	color filling; //цвет заливки

public:
	Rhomb();
	~Rhomb();
	void saveToFile(char*);
	void readFromFile(char*);
	void drawRhomb(HDC);
	void drawFilledRhomb(HDC);
};

