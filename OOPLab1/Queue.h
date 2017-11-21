#pragma once
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Rhomb.h"
using namespace std;

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
	void saveQueueToFile(ofstream&);
	void loadQueueFromFile(ifstream&);
	void setMaxSize(int);
	friend void operator <<(ofstream&, Queue&); //Перегрузка оператора cout 
	friend void operator >> (istream&, Queue&); //Перегрузка оператора cin
};

