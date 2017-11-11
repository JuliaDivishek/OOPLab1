#include "Rhomb.h"

Rhomb::Rhomb()
{
	points = new POINT[4];
	points[0] = {70, 125};
	points[1] = {100, 50};
	points[2] = {130, 125};
	points[3] = {100, 200};
}


Rhomb::~Rhomb()
{
	delete[]points;
}

Rhomb::Rhomb(int x1, int y1, int x2, int y2)
{
	points = new POINT[4];
	points[0] = { x1, y1 };
	points[1] = { x2, y2 };
	points[2] = { points[1].x + (points[1].x - points[0].x), points[0].y };
	points[3] = { points[1].x, points[0].y * 2 - points[1].y };
};

void Rhomb::saveToFile(char *filename)
{
	ofstream out(filename, ios::out);
	 //достаточно сохранить две вершины, левую и верхнюю
	out << this->points[0].x;
	out << " ";
	out << this->points[0].y;
	out << " ";
	out << this->points[1].x;
	out << " ";
	out << this->points[1].y;
	out << " ";
	/*//—охран€ем цвета контура и заливки
	out << this->outline.R;
	out << " ";
	out << this->outline.G;
	out << " ";
	out << this->outline.B;
	out << " ";
	out << this->filler.R;
	out << " ";
	out << this->filler.G;
	out << " ";
	out << this->filler.B;*/
}

void Rhomb::readFromFile(char *filename) 
{
	ifstream in(filename, ios::in);
	if (in.is_open())
	{
	   //—читываем координаты двух точек
		in >> this->points[0].x;
		in >> this->points[0].y;
		in >> this->points[1].x;
		in >> this->points[1].y;
		//ќстальные две высчитываем
		this->points[2] = { this->points[1].x + (this->points[1].x - this->points[0].x), this->points[0].y };
		this->points[3] = { this->points[1].x, this->points[0].y * 2 - this->points[1].y };
		/*//—читываем цвета контура и заливки
		in >> this->outline.R;
		in >> this->outline.G;
		in >> this->outline.B;
		in >> this->filler.R;
		in >> this->filler.G;
		in >> this->filler.B;*/
		in.close();
	}
	else cout << "Unable to open file";
}



