#pragma once
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Rhomb
{
	POINT *points; //вершины

	void checkPoints(int, int, int, int);
	
public:
	Rhomb();
	Rhomb(int, int, int, int);
	~Rhomb();
	void saveToFile(string);
	void readFromFile(string);
	void setPoints(int, int, int, int);
	void isRhombInside(Rhomb*);
	void shiftRhomb(int, int);
	POINT* getPoints();
	friend class Queue;
};

