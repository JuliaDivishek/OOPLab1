#include "Queue.h"



Queue::Queue(int maxSize)
{
	maxSize_ = maxSize;
	rear = -1;
	array = new Rhomb*[maxSize];
}


Queue::~Queue()
{
	delete[] array;
}

void Queue::enqueue(Rhomb *rhomb)
{
	if (rear == maxSize_ - 1)
		throw exception("Queue is overflow");

	array[++rear] = rhomb;
}

Rhomb* Queue::dequeue()
{
	if (rear==-1)
		throw exception("Queue is empty");
	
	Rhomb *a = array[0]; //взяли из очереди элемент
	
	//передвигаем очередь. В с++ нет аналога realloc, поэтому так
	Rhomb **newArray = new Rhomb*[maxSize_];
	for (int i = 0; i < rear; i++)
	{
		newArray[i] = array[i+1];
	}
	delete[] array;
	array = newArray;
	rear--;

	return a;
}

void Queue::showQueue()
{
	if (rear == -1)
		throw exception("Queue is empty");

	for (int i = 0; i <= rear; i++)
	{
		cout << i<<". ("<<array[i]->points[0].x<<"; "<<array[i]->points[0].y<<") ("<<array[i]->points[1].x<<"; "<<array[i]->points[1].y<<")" << endl;
	}
}

const Rhomb* Queue::find(int x1, int y1, int x2, int y2)
{
	const Rhomb *a = NULL;
	for (int i = 0; i <= rear; i++)
	{
		if (array[i]->points[0].x == x1 && array[i]->points[0].y == y1 &&array[i]->points[1].x == x2 && array[i]->points[1].y == y2)
			a = array[i];
	}
	return a;
}

void Queue::saveQueueToFile(ofstream& out)
{
	out << this;

	/*if (out.is_open())
	{
		out << maxSize_ << " ";
		out << rear << " ";
		for (int i = 0; i <= rear; i++)
		{
			out << array[i]->points[0].x;
			out << " ";
			out << array[i]->points[0].y;
			out << " ";
			out << array[i]->points[1].x;
			out << " ";
			out << array[i]->points[1].y;
			out << " ";
		}
	}
	else exception("The stream is not open");*/
}

void Queue::loadQueueFromFile(ifstream& in)
{
	
	if (in.is_open())
	{
		int frear, fMaxSize;
		in >> fMaxSize;
		in >> frear;
		setMaxSize(fMaxSize);
			
		for (int i = 0; i <= frear; i++)
		{
			int x1, y1, x2, y2;
			in >> x1;
			in >> y1;
			in >> x2;
			in >> y2;
			Rhomb* rhomb = new Rhomb(x1, y1, x2, y2);
			enqueue(rhomb);
		}
	
	}
	else exception("The stream is not open");
}

void Queue::setMaxSize(int maxSize)
{
	maxSize_ = maxSize;
	rear = -1;
	delete[] array;
	array = new Rhomb*[maxSize];
}

void operator << (ofstream& out, Queue& queue)
{
	if (out.is_open())
	{
		out << queue.maxSize_ << " ";
		out << queue.rear << " ";
		for (int i = 0; i <= queue.rear; i++)
		{
			out << queue.array[i]->points[0].x;
			out << " ";
			out << queue.array[i]->points[0].y;
			out << " ";
			out << queue.array[i]->points[1].x;
			out << " ";
			out << queue.array[i]->points[1].y;
			out << " ";
		}
	}
	else exception("The stream is not open");
}