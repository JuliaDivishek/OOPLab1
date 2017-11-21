#include "Rhomb.h"
#include "Draw.h"
#include "Queue.h"


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
		c.readColorsFromFile("colors.txt");

		
		c.drawFilledRhomb(&a);
		c.drawRhomb(&a);
		
		c.drawRhombInRhomb(&a, &b);
		c.setFillerColor(100, 100, 100);
		c.setOutlineColor(0, 255, 0);
		a.shiftRhomb(-10, 50);
		
		c.drawRhomb(&a);
		c.drawFilledRhomb(&a);

		const int n = 5;
		Queue queue(n);

		for(int i = 0; i < n; i++)
		{ 
			Rhomb* rhomb = new Rhomb(50+i, 50+i, 100+i, 20+i);
			queue.enqueue(rhomb);
		}
		queue.showQueue();
		//Rhomb *d = queue.dequeue();
		//queue.showQueue();
		//cout << queue.find(51, 51, 101, 21) << endl;

		ofstream out("queue.txt", ios::out);
		queue.saveQueueToFile(out);
		out.close();

		/*ifstream in("queue.txt", ios::in);
		queue.loadQueueFromFile(in);
		queue.showQueue();
		in.close();*/
	}
	catch (exception ex)
	{
		cerr << ex.what() << endl;
	}
	return 0;
}