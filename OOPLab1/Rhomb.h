#pragma once
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string.h>


class Rhomb
{
	POINT *points; //вершины

	void checkPoints(int, int, int, int);
	
public:
	Rhomb();
	Rhomb(int, int, int, int);
	~Rhomb();
	void saveToFile(std::ofstream&);
	void readFromFile(std::ifstream&);
	void setPoints(int, int, int, int);
	void isRhombInside(Rhomb*);
	void shiftRhomb(int, int);
	POINT* getPoints();
	friend class Draw;
	friend class Queue;
	friend std::ofstream& operator << (std::ofstream& out, const Queue& queue);
	friend std::istream& operator >> (std::istream& in, Queue& queue);
};

