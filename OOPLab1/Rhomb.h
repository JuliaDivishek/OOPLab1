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

public:
	Rhomb();
	Rhomb(int, int, int, int);
	~Rhomb();
	friend class Draw;
	void saveToFile(char*);
	void readFromFile(char*);
};

