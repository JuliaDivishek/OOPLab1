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
	checkPoints(x1, y1, x2, y2);
	points = new POINT[4];
	points[0] = { x1, y1 };
	points[1] = { x2, y2 };
	points[2] = { points[1].x + (points[1].x - points[0].x), points[0].y };
	points[3] = { points[1].x, points[0].y * 2 - points[1].y };
};

void Rhomb::saveToFile(string filename)
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
	out.close();
}

void Rhomb::readFromFile(string filename) 
{
	ifstream in(filename, ios::in);
	if (in.is_open())
	{
		POINT *points = this->getPoints();
	   //Считываем координаты двух точек
		in >> points[0].x;
		in >> points[0].y;
		in >> points[1].x;
		in >> points[1].y;
		checkPoints(points[0].x, points[0].y, points[1].x, points[1].y);
		//Остальные две высчитываем
		points[2] = { points[1].x + (points[1].x - points[0].x), points[0].y };
		points[3] = { points[1].x, points[0].y * 2 - points[1].y };
		in.close();
	}
	else throw exception("Unable to open file");
}

void Rhomb::setPoints(int x1, int y1, int x2, int y2)
{
	checkPoints(x1, y1, x2, y2);
	POINT *points = this->getPoints();
	points[0] = { x1, y1 };
	points[1] = { x2, y2 };
	points[2] = { points[1].x + (points[1].x - points[0].x), points[0].y };
	points[3] = { points[1].x, points[0].y * 2 - points[1].y };
};


void Rhomb::checkPoints(int x1, int y1, int x2, int y2)
{
	if ((x1 >= x2) || (y1 <= y2))
		throw exception("Incorrect points");
}


void Rhomb::isRhombInside(Rhomb *innerRhomb)
{
	POINT *points1 = this->getPoints();
	POINT *points2 = innerRhomb->getPoints();
	//при проверке используется запас в 5 пикселей, чтобы при отрисовке фигура внутри фигуры смотрелась красиво
	if((points2[0].x < points1[0].x + 5)||(points2[2].x > points1[2].x - 5)|| (points2[1].y < points1[1].y + 5)|| (points2[3].y > points1[3].y - 5))
		throw exception("Incorrect points of innerRhomb");
}


POINT* Rhomb::getPoints()
{
	return this->points;
}

void Rhomb::shiftRhomb(int x, int y) {
	POINT *points = this->getPoints();
	setPoints(points[0].x + x, points[0].y + y, points[1].x + x, points[1].y + y);
}
