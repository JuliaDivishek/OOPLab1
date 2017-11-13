#include "Draw.h"
#include "helper.h"


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
}

void Draw::drawRhomb(Rhomb *rhomb)
{
	clearTheScreen(this->hwnd);
	SelectPen(this->hdc, this->hNewPen);
	SelectBrush(hdc, GetStockBrush(NULL_BRUSH));
	Polygon(hdc, rhomb->points, 4);
	system("pause");
}

void Draw::drawFilledRhomb(Rhomb *rhomb)
{
	clearTheScreen(this->hwnd);
	SelectPen(this->hdc, this->hNewPen);
	SelectBrush(this->hdc, this->hNewBrush);
	Polygon(this->hdc, rhomb->points, 4);
	system("pause");
}

void Draw::drawRhombInRhomb(Rhomb* outerRhomb, Rhomb* innerRhomb)
{
	clearTheScreen(this->hwnd);
	outerRhomb->isRhombInside(innerRhomb);
	SelectPen(this->hdc, this->hNewPen);
	SelectBrush(this->hdc, GetStockBrush(NULL_BRUSH));
	Polygon(this->hdc, outerRhomb->points, 4);
	Polygon(this->hdc, innerRhomb->points, 4);
	//Меняем цвет кисти
	SelectBrush(this->hdc, this->hNewBrush);
	//делаем заливку, указываем точку, гарантированно лежащую внутри фигуры
	FloodFill(this->hdc, outerRhomb->points[0].x + 1, outerRhomb->points[0].y, RGB(this->outline.R, this->outline.G, this->outline.B));
	system("pause");
}


void Draw::moveRhomb(Rhomb *rhomb)
{
	clearTheScreen(this->hwnd);
	RECT rt = getWindowSize(this->hwnd);
	//ромб перемещается вправо, пока не достигнет границы окна
	SelectPen(this->hdc, this->hNewPen);
	SelectBrush(this->hdc, this->hNewBrush);
	while(rhomb->points[2].x < rt.right)
	{
		Polygon(this->hdc, rhomb->points, 4);
		Sleep(100); //задержка в милисекундах
		clearTheScreen(this->hwnd);
		rhomb->setPoints(rhomb->points[0].x + 5, rhomb->points[0].y, rhomb->points[1].x + 5, rhomb->points[1].y);
		Polygon(this->hdc, rhomb->points, 4);
	}
	system("pause");
	
}


void Draw::checkColor(short R, short G, short B)
{
	if ((R < 0 || R > 255) || (G < 0 || G > 255) || (B < 0 || B > 255))
		throw exception("Incorrect color");
}

void Draw::saveColorsToFile(string filename)
{
	ofstream out(filename, ios::out);
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
	out.close();
}
void Draw::readColorsFromFile(string filename)
{
	ifstream in(filename, ios::in);
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
		in.close();
	}
	else throw exception("Unable to open file");
}

void Draw::setOutlineColor(short R, short G, short B)
{
	checkColor(R, G, B);
	this->outline = { R, G, B };
	hNewPen = CreatePen(PS_SOLID, 1, RGB(this->outline.R, this->outline.G, this->outline.B));
}
void Draw::setFillerColor(short R, short G, short B)
{
	checkColor(R, G, B);
	filler = { R, G, B };
	hNewBrush = CreateSolidBrush(RGB(this->filler.R, this->filler.G, this->filler.B));
}