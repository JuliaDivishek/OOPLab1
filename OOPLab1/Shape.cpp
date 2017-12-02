#include "Shape.h"

Contour::Contour(color outline) {
	checkColor(outline.R, outline.G, outline.B);
	this->outline = outline;
	this->hPen = CreatePen(PS_SOLID, 1, RGB(outline.R, outline.G, outline.B));
}

HPEN Contour::getHpen() {
	return this->hPen;
}

void Contour::checkColor(short R, short G, short B)
{
	if ((R < 0 || R > 255) || (G < 0 || G > 255) || (B < 0 || B > 255))
		throw std::exception("Incorrect color");
}

color Contour::getOutlineColor() {
	return this->outline;
}



Filled::Filled(color outlineColor, color fillerColor): Contour(outlineColor){
	checkColor(fillerColor.R, fillerColor.G, fillerColor.B);
	this->filler = fillerColor;
	this->hBrush = CreateSolidBrush(RGB(fillerColor.R, fillerColor.G, fillerColor.B));

}

HBRUSH Filled::getHbrush() {
	return this->hBrush;
}

color Filled::getFillerColor() {
	return this->filler;
}



Rhomb::~Rhomb()
{
	delete[]points;
}

Rhomb::Rhomb(int x1, int y1, int x2, int y2, Contour *contour)
{
	checkPoints(x1, y1, x2, y2);
	points = new POINT[4];
	points[0] = { x1, y1 };
	points[1] = { x2, y2 };
	points[2] = { points[1].x + (points[1].x - points[0].x), points[0].y };
	points[3] = { points[1].x, points[0].y * 2 - points[1].y };
	this->contour = contour;
};

void Rhomb::setPoints(int x1, int y1, int x2, int y2)
{
	checkPoints(x1, y1, x2, y2);
	points[0] = { x1, y1 };
	points[1] = { x2, y2 };
	points[2] = { points[1].x + (points[1].x - points[0].x), points[0].y };
	points[3] = { points[1].x, points[0].y * 2 - points[1].y };
};


void Rhomb::checkPoints(int x1, int y1, int x2, int y2)
{
	if ((x1 >= x2) || (y1 <= y2))
		throw std::exception("Incorrect points");
}

POINT* Rhomb::getPoints()
{
	return this->points;
}

void Rhomb::shiftRhomb(int x, int y) {
	setPoints(points[0].x + x, points[0].y + y, points[1].x + x, points[1].y + y);
}

void Rhomb::draw(HWND hwnd, HDC hdc)
{
	checkOutTheWindow(hwnd);
	SelectPen(hdc, this->contour->getHpen());
	SelectBrush(hdc, GetStockBrush(NULL_BRUSH));
	Polygon(hdc, this->points, 4);

}

void Rhomb::checkOutTheWindow(HWND hwnd)
{
	RECT rt = getWindowSize(hwnd);
	if ((this->points[0].x < rt.left) || (this->points[2].x > rt.right) || (this->points[1].y < rt.top) || (this->points[3].y > rt.bottom))
		throw std::exception("Figure is off-screen");
}


FilledRhomb::FilledRhomb(int x1, int y1, int x2, int y2, Filled* filled): Rhomb(x1, y1, x2, y2, filled) {
	this->filled = filled;
}

void FilledRhomb::draw(HWND hwnd, HDC hdc) {
	checkOutTheWindow(hwnd);
	SelectPen(hdc, this->filled->getHpen());
	SelectBrush(hdc, this->filled->getHbrush());
	Polygon(hdc, this->points, 4);
}


void CombinedFilledRhomb::isRhombInside(Rhomb *innerRhomb)
{
	POINT *points1 = this->getPoints();
	POINT *points2 = innerRhomb->getPoints();
	//при проверке используется запас в 5 пикселей, чтобы при отрисовке фигура внутри фигуры смотрелась красиво
	if ((points2[0].x < points1[0].x + 5) || (points2[2].x > points1[2].x - 5) || (points2[1].y < points1[1].y + 5) || (points2[3].y > points1[3].y - 5))
		throw std::exception("Incorrect points of innerRhomb");
}


CombinedFilledRhomb::CombinedFilledRhomb(int x1, int y1, int x2, int y2, Rhomb* innerRhomb, Filled* filled): FilledRhomb(x1, y1, x2, y2, filled){
	this->innerRhomb = innerRhomb;
}


void CombinedFilledRhomb::draw(HWND hwnd, HDC hdc) {
	checkOutTheWindow(hwnd);
	this->innerRhomb->checkOutTheWindow(hwnd);
	this->isRhombInside(innerRhomb);
	SelectPen(hdc, this->filled->getHpen());
	SelectBrush(hdc, GetStockBrush(NULL_BRUSH));
	Polygon(hdc, this->points, 4);
	Polygon(hdc, this->innerRhomb->getPoints(), 4);
	//Меняем цвет кисти
	SelectBrush(hdc, this->filled->getHbrush());
	//делаем заливку, указываем точку, гарантированно лежащую внутри фигуры
	FloodFill(hdc, this->points[0].x + 1, this->points[0].y, RGB(this->filled->getOutlineColor().R, this->filled->getOutlineColor().G, this->filled->getOutlineColor().B));
}