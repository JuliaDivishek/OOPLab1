#include "Rhomb.h"

Rhomb::Rhomb()
{
	points = new POINT[4];
	points[0] = {70, 125};
	points[1] = {100, 50};
	points[2] = {130, 125};
	points[3] = {100, 200};

	outline = {0, 0, 0};

	filling = {255,255,255};
}


Rhomb::~Rhomb()
{
	delete[]points;
}

void Rhomb::drawRhomb(HDC hdc)
{
	HPEN hOldPen;
	HPEN hNewPen = CreatePen(PS_SOLID, 3, RGB(this->outline.R, this->outline.G, this->outline.B));
	hOldPen = SelectPen(hdc, hNewPen);
	Polygon(hdc, this->points, 4);
	SelectPen(hdc, hOldPen);
	DeletePen(hNewPen);
}

void Rhomb::drawFilledRhomb(HDC hdc)
{
	HPEN hOldPen;
	HPEN hNewPen = CreatePen(PS_SOLID, 3, RGB(this->outline.R, this->outline.G, this->outline.B));
	hOldPen = SelectPen(hdc, hNewPen);
	HBRUSH hOldBrush;
	HBRUSH hNewBrush = CreateSolidBrush(RGB(this->filling.R, this->filling.G, this->filling.B));
	hOldBrush = SelectBrush(hdc, hNewBrush);
	Polygon(hdc, this->points, 4);
	SelectPen(hdc, hOldPen);
	DeletePen(hNewPen);
	SelectBrush(hdc, hOldBrush);
	DeleteBrush(hNewBrush);
}

void Rhomb::saveToFile(char *filename)
{
	ofstream out(filename, ios::out);
	for (int i = 0; i < 2; i++) { //достаточно сохранить две вершины, левую и верхнюю
		out << this->points[i].x;
		out << " ";
		out << this->points[i].y;
		out << " ";
	}
	out << this->outline.R;
	out << " ";
	out << this->outline.G;
	out << " ";
	out << this->outline.B;
	out << " ";
	out << this->filling.R;
	out << " ";
	out << this->filling.G;
	out << " ";
	out << this->filling.B;
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
		//—читываем цвета контура и заливки
		in >> this->outline.R;
		in >> this->outline.G;
		in >> this->outline.B;
		in >> this->filling.R;
		in >> this->filling.G;
		in >> this->filling.B;
		in.close();
	}
	else cout << "Unable to open file";
}

