#include "Rhomb.h"
#include "Draw.h"
#include "Queue.h"
#include "DrawHelpers.h"


int main()
{
	try {
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		Rhomb a(50, 50, 100, 20);
		Rhomb b(55, 50, 100, 35);
		

		color outlineColor = { 255, 0, 0 };
		color fillerColor = { 200, 100, 0 };
		Draw c(hwnd, hdc, &outlineColor, &fillerColor);
		

		std::ifstream in("colors.txt", std::ios::in);
		c.readColorsFromFile(in);
		in.close();
		
		c.drawFilledRhomb(&a);
		clearTheScreen(hwnd);
		c.drawRhomb(&a);
		clearTheScreen(hwnd);

		c.drawRhombInRhomb(&a, &b);
		clearTheScreen(hwnd);
		c.setFillerColor(100, 100, 100);
		c.setOutlineColor(0, 255, 0);
		a.shiftRhomb(-10, 50);
		
		c.drawRhomb(&a);
		clearTheScreen(hwnd);
		c.drawFilledRhomb(&a);
		clearTheScreen(hwnd);


		//Для второй лабораторной
		const int n = 5;
		Queue queue(n);

		for(int i = 0; i < n; i++)
		{ 
			Rhomb* rhomb = new Rhomb(50+50*i, 50+50*i, 100+50*i, 20+50*i);
			queue.enqueue(rhomb);
		}

		std::ofstream queueOut("queue.txt", std::ios::out);
		queueOut<<queue;
		queueOut.close();

		queue.showQueue();

		for (int i = 0; i < n; i++)
		{
			Rhomb *d = queue.dequeue();
			c.drawRhomb(d);
		}

		std::cout << queue.find(51, 51, 101, 21) << std::endl;

	
		std::ifstream queueIn("queue.txt", std::ios::in);
		queueIn >> queue;
		queue.showQueue();
		queueIn.close();
	}
	catch (std::exception ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}