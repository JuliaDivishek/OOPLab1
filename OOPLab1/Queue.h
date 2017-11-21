#pragma once
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Rhomb.h"


class Queue
{
	int maxSize_; //размер очереди
	int rear; //индекс конца очереди
	Rhomb **array; //массив указателей на экземпляры класса ромб

public:
	Queue(int);
	~Queue();
	void enqueue(Rhomb*);
	Rhomb* dequeue();
	void showQueue();
	const Rhomb* find(int, int, int, int);
	void setMaxSize(int);
	friend std::ofstream& operator << (std::ofstream& out, const Queue& queue);
	friend std::istream& operator >>(std::istream& in, Queue& queue);

	//ofstream& operator << (ofstream&);
};

