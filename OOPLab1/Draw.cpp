#include "Draw.h"
#include "DrawHelpers.h"


Draw::Draw()
{
	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
	outline = { 0, 0, 0 };
	filler = { 255,255,255 };
	hNewPen = CreatePen(PS_SOLID, 1, RGB(this->outline.R, this->outline.G, this->outline.B));
	hNewBrush = CreateSolidBrush(RGB(this->filler.R, this->filler.G, this->filler.B));
}

Draw::Draw(HWND hwnd, HDC hdc, color *outlineColor, color *fillerColor)
{
	this->hwnd = hwnd;
	this->hdc = hdc;
	outline = *outlineColor;
	filler = *fillerColor;
	checkColor(this->outline.R, this->outline.G, this->outline.B);
	checkColor(this->filler.R, this->filler.G, this->filler.B);
	hNewPen = CreatePen(PS_SOLID, 1, RGB(this->outline.R, this->outline.G, this->outline.B));
	hNewBrush = CreateSolidBrush(RGB(this->filler.R, this->filler.G, this->filler.B));
}

Draw::~Draw()
{
	ReleaseDC(this->hwnd, this->hdc);
}

void Draw::drawRhomb(Rhomb *rhomb)
{
	checkOutTheWindow(rhomb);
	SelectPen(this->hdc, this->hNewPen);
	SelectBrush(hdc, GetStockBrush(NULL_BRUSH));
	Polygon(this->hdc, rhomb->points, 4);
	
}

void Draw::drawFilledRhomb(Rhomb *rhomb)
{
	checkOutTheWindow(rhomb);
	SelectPen(this->hdc, this->hNewPen);
	SelectBrush(this->hdc, this->hNewBrush);
	Polygon(this->hdc, rhomb->points, 4);
}

void Draw::drawRhombInRhomb(Rhomb* outerRhomb, Rhomb* innerRhomb)
{
	checkOutTheWindow(outerRhomb);
	checkOutTheWindow(innerRhomb);
	outerRhomb->isRhombInside(innerRhomb);
	SelectPen(this->hdc, this->hNewPen);
	SelectBrush(this->hdc, GetStockBrush(NULL_BRUSH));
	Polygon(this->hdc, outerRhomb->points, 4);
	Polygon(this->hdc, innerRhomb->points, 4);
	//Меняем цвет кисти
	SelectBrush(this->hdc, this->hNewBrush);
	//делаем заливку, указываем точку, гарантированно лежащую внутри фигуры
	FloodFill(this->hdc, outerRhomb->points[0].x + 1, outerRhomb->points[0].y, RGB(this->outline.R, this->outline.G, this->outline.B));
}


void Draw::checkColor(short R, short G, short B)
{
	if ((R < 0 || R > 255) || (G < 0 || G > 255) || (B < 0 || B > 255))
		throw std::exception("Incorrect color");
}

void Draw::saveColorsToFile(std::ofstream& out)
{
	//Сохраняем цвета контура и заливки
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
	out << this->filler.B;
}
void Draw::readColorsFromFile(std::ifstream& in)
{
	if (in.is_open())
	{
		//Считываем цвета контура и заливки
		in >> this->outline.R;
		in >> this->outline.G;
		in >> this->outline.B;
		in >> this->filler.R;
		in >> this->filler.G;
		in >> this->filler.B;
		checkColor(this->outline.R, this->outline.G, this->outline.B);
		checkColor(this->filler.R, this->filler.G, this->filler.B);
		this->hNewPen = CreatePen(PS_SOLID, 1, RGB(this->outline.R, this->outline.G, this->outline.B));
		this->hNewBrush = CreateSolidBrush(RGB(this->filler.R, this->filler.G, this->filler.B));
	}
	else throw std::exception("Unable to open file");
}

void Draw::setOutlineColor(short R, short G, short B)
{
	checkColor(R, G, B);
	this->outline = { R, G, B };
	hNewPen = CreatePen(PS_SOLID, 1, RGB(R, G, B));
}
void Draw::setFillerColor(short R, short G, short B)
{
	checkColor(R, G, B);
	filler = { R, G, B };
	hNewBrush = CreateSolidBrush(RGB(R, G, B));
}

void Draw::checkOutTheWindow(Rhomb* rhomb)
{
	RECT rt = getWindowSize(this->hwnd);
	if((rhomb->points[0].x < rt.left) || (rhomb->points[2].x > rt.right) || (rhomb->points[1].y < rt.top) || (rhomb->points[3].y > rt.bottom))
		throw std::exception("Figure is off-screen");
}